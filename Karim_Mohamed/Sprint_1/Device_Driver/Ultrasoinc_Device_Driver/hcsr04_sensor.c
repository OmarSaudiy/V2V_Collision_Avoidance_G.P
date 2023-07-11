#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/timer.h>

#include "hcsr04_sensor.h"

#define DRIVER_AUTHOR "Karim, Omar.H and Omar.I"
#define DRIVER_DECSRIPTION "A driver to read the HC-SR04 sensor.\nWriting to the device file using the format <Set_Ultrasonic_Pins> to set echo and triger oins for 6 ultrasonic.\nReading from the device file returns the bytes of an unsigned long containg the time in microseconds for a single roundtrip."
#define DRIVER_VERSION "2.1"

//Timeout for hardware to set echo pin
#define ECHO_TIMEOUT          (2600)// in microsecond

//Timeout for max distance after that close the file 
#define DIS_TIMEOUT        ( (MAX_DISTANCE_CM_GO_AWAY*1e4)/(SPEED_OF_SOUND_M_S))


uint8_t US_unum;
US_t US_Data[ULTRASONIC_NUMS]=
{ 
    {.position="US_FRONT_LEFT" , .Echo_Pin=FRONT_LEFT_ECHO_PIN , .Echo_Flag=1 , .Trig_Pin=FRONT_LEFT_TRIG_PIN }, 
    {.position="US_FRONT_MID"  , .Echo_Pin=FRONT_MID_ECHO_PIN  , .Echo_Flag=1 , .Trig_Pin=FRONT_MID_TRIG_PIN  }, 
    {.position="US_FRONT_RIGHT", .Echo_Pin=FRONT_RIGHT_ECHO_PIN, .Echo_Flag=1 , .Trig_Pin=FRONT_RIGHT_TRIG_PIN}, 
    {.position="US_BACK_LEFT"  , .Echo_Pin=BACK_LEFT_ECHO_PIN  , .Echo_Flag=1 , .Trig_Pin=BACK_LEFT_TRIG_PIN  },
    {.position="US_BACK_MID"   , .Echo_Pin=BACK_MID_ECHO_PIN   , .Echo_Flag=1 , .Trig_Pin=BACK_MID_TRIG_PIN   }, 
    {.position="US_BACK_RIGHT" , .Echo_Pin=BACK_RIGHT_ECHO_PIN , .Echo_Flag=1 , .Trig_Pin=BACK_RIGHT_TRIG_PIN }
};




/*-------------------------------------------------------------------*/
/*  HEALPER FUNCTIONS   */

static void RST_US_Data(void)
{
    uint8_t iteration;
    for(iteration=0 ; iteration<ULTRASONIC_NUMS ; iteration++)
    {
        US_Data[iteration].Echo_Flag=1;
        US_Data[iteration].Start_Time=0;
        US_Data[iteration].Finish_Time=0;
        US_Data[iteration].Elapsed_Time=USHRT_MAX;
        strcpy( US_Data[iteration].Elapsed_Time_str," ERR!");
    }

}

static void Send_Trigger_Pulse(void)
{
    uint8_t iteration;
    
    
    if(US_unum== ULTRASONIC_NUMS)
    {
        
        for( iteration= 0 ; iteration < ULTRASONIC_NUMS ; iteration++)
        {
            gpio_set_value(US_Data[iteration].Trig_Pin, 1);
        }
        for( iteration= 0 ; iteration < ULTRASONIC_NUMS ; iteration++)
        {
            gpio_set_value(US_Data[iteration].Trig_Pin, 0);
        }
    }
    else
    {
        gpio_set_value(US_Data[US_unum].Trig_Pin, 1);
        udelay(TRIGGER_HIGH_TIME_uS);
        gpio_set_value(US_Data[US_unum].Trig_Pin, 0);
    }
}

static void Set_Echo_Flag(void)
{
    uint8_t iteration;
    for(iteration=0 ; iteration<ULTRASONIC_NUMS ; iteration++)
    {
        US_Data[iteration].Echo_Flag=1;
    }

}

static void Set_Time_Out_ns(ktime_t* relative_timeout_ns , ktime_t timeout)
{
    *relative_timeout_ns = ktime_add_us(ktime_get(),timeout);
}

static int Wait_Echo_Go_High(ktime_t timeout_ns)
{
    /*------  Hardware takes about 2.4ms to set echo pin  ------*/
    uint8_t US_Echo=1;
    uint8_t iteration;
    if(US_unum == ALL_US)
    {
       while(US_Echo)
       {
            US_Echo=0;
            if(ktime_compare(ktime_get(), timeout_ns) < 0) //Still in Time
            {
                for(iteration=0 ; iteration<ULTRASONIC_NUMS ; iteration++)// get echo pins status
                {
                    if( gpio_get_value(US_Data[iteration].Echo_Pin) ==0 ) //Hardware not set yet!
                    {
                        US_Echo=1;
                    }
                    else if (gpio_get_value(US_Data[iteration].Echo_Pin)==1  && US_Data[iteration].Echo_Flag==1 )
                    {
                        US_Data[iteration].Start_Time= ktime_get();
                        US_Data[iteration].Echo_Flag=0;
                        printk("%s started\n",US_Data[iteration].position);
                      
                    }
                    if(gpio_get_value(US_Data[iteration].Echo_Pin)==0 && US_Data[iteration].Start_Time!=0  )// Wave of ultrasonic is reflected && there is at least one ultrasonic its echo not set yet
                    {
                        US_Data[iteration].Finish_Time = ktime_get();
                        US_Data[iteration].Elapsed_Time = (uint16_t)ktime_us_delta(US_Data[iteration].Finish_Time, US_Data[iteration].Start_Time);
                        //Convert number to string
                        sprintf( US_Data[iteration].Elapsed_Time_str,"%5d", US_Data[iteration].Elapsed_Time);
                        printk("Only Finish=%u\n",(uint32_t)US_Data[iteration].Finish_Time);
                        US_Data[iteration].Start_Time=0;
                        /*Reset Echo flag for this ultrasonic to be not reentered  */
                        US_Data[iteration].Echo_Flag=0;
                    }
                }
            }
            else if (ktime_compare(ktime_get(), timeout_ns) >= 0) //TimeOut : a Hardware Problem 
            {

                pr_err("Timeout: Echo pin error\n");
                //Set echos flag ,it will be used again
                Set_Echo_Flag();
                return -1;   
            }
            else
            {
                // Do nothing
            }
        }
        Set_Echo_Flag();
    }
    else
    {
        while (!gpio_get_value(US_Data[US_unum].Echo_Pin))
        {
            if (ktime_compare(ktime_get(), timeout_ns) >= 0)
            {
                pr_err("Timeout: Echo pin error\n");
                return -1;   
            }
        }
         US_Data[US_unum].Start_Time = ktime_get();
    }

    return 0;
}
static int Get_Travlling_Time(void)
{
    /*--Max time around 1.8 ms FOR 60cm--*/
    ktime_t dis_timeout_ns;
    uint8_t iteration;
    uint8_t All_US_Echo=1;

    // set time out for max distance 
    Set_Time_Out_ns(&dis_timeout_ns,DIS_TIMEOUT);
    
    if(US_unum== ULTRASONIC_NUMS)
    {
        while(All_US_Echo) //is One of echo pins still high ?
        {
            All_US_Echo=0;

            for(iteration=0 ; iteration<ULTRASONIC_NUMS ; iteration++)
            {
                if( gpio_get_value(US_Data[iteration].Echo_Pin) ==1 )
                {
                    // ther is at least One of echo pins still high
                    All_US_Echo=1;
                }
                else if(gpio_get_value(US_Data[iteration].Echo_Pin)==0  && US_Data[iteration].Echo_Flag==1 && US_Data[iteration].Start_Time!=0  )// Wave is reflected and there is an object detected//Third condition means that there is hardware issue if time not started
                {
                    US_Data[iteration].Finish_Time = ktime_get();
                    US_Data[iteration].Elapsed_Time = (uint16_t)ktime_us_delta(US_Data[iteration].Finish_Time, US_Data[iteration].Start_Time);
                    //Convert number to string
                    sprintf( US_Data[iteration].Elapsed_Time_str,"%5d", US_Data[iteration].Elapsed_Time);
                    printk("Finish=%u\nstart=%u\nelapsed=%u\n",(uint32_t)US_Data[iteration].Finish_Time,(uint32_t) US_Data[iteration].Start_Time,(uint32_t)US_Data[iteration].Elapsed_Time);
                    /*Reset Echo flag for this ultrasonic to be not reentered  */
                    US_Data[iteration].Echo_Flag=0;
                }
            }
            if (ktime_compare(ktime_get(), dis_timeout_ns) >= 0)
            {

                printk("Timeout reading the sensor, no object detected\n");
                Set_Echo_Flag();
                return -1;
            }
            else
            {
                
            }
        }
        // Set_Echo_Flag();   
    }
    else
    {
        while (gpio_get_value(US_Data[US_unum].Echo_Pin))
        {
            if (ktime_compare(ktime_get(), dis_timeout_ns) >= 0)
            {
                pr_err("Timeout reading the sensor, no object detected \n");
                return -1;
            }
            else
            {
                //Do nothing
            }
            
        }
        US_Data[US_unum].Finish_Time = ktime_get();
        US_Data[US_unum].Elapsed_Time = (uint16_t)ktime_us_delta(US_Data[US_unum].Finish_Time, US_Data[US_unum].Start_Time);
        sprintf(US_Data[US_unum].Elapsed_Time_str,"%5d", US_Data[US_unum].Elapsed_Time);
        printk("Finish=%u\nstart=%u\nelapsed=%u\nelapsedstr=%s\n",(uint32_t)US_Data[US_unum].Finish_Time,(uint32_t) US_Data[US_unum].Start_Time,(uint32_t)US_Data[US_unum].Elapsed_Time,US_Data[US_unum].Elapsed_Time_str);
    }
    return 0;
}
/*-----------------------------------------------------------------*/





/*
The open and release functions are not currently needed but are there to
make the code more readable. May be used in future.
*/

int hcsr04_open(struct inode *inode, struct file *file)
{
    pr_info("Opened device file\n");
    return 0;
}

int hcsr04_release(struct inode *inode, struct file *file)
{
    pr_info("Closed device file\n");
    return 0;
}

/*
The read function is used to read the distance from the sensor.
*/

ssize_t hcsr04_read(
    struct file *filp, char __user *buffer,
    size_t length, loff_t *offset)
{
    uint8_t internal_buffer[MAX_BUFFER_LENGTH];
    uint8_t iteration;
    ktime_t echo_timeout_ns;


    
    if (*offset) 
    {
        return 0;
    }
    if(copy_from_user(internal_buffer,buffer,length))
    {
        pr_err("No all bytes were copied from user\n");
    }

    RST_US_Data();

    US_unum=internal_buffer[0];

    if( (US_unum >=0) && (US_unum < ULTRASONIC_NUMS) )
    {
        pr_info("Attempting to read sensor: %s \n",US_Data[US_unum].position);
    }
    else if(US_unum == ULTRASONIC_NUMS)
    {
        pr_info("Attempting to read All sensor\n");
    }
    else
    {
        pr_err("Invalid Ultrasonic Number\n");
        goto timeout;
    }   
    // Send trugger pulse
    Send_Trigger_Pulse();
    // set time out for hardware
    Set_Time_Out_ns(&echo_timeout_ns,ECHO_TIMEOUT);
    if(Wait_Echo_Go_High(echo_timeout_ns) )
    {
        // goto timeout;
    }

    if (Get_Travlling_Time())
    {
        goto timeout;
    }
 
timeout:
 
    length = sizeof(unsigned long);
    memset(internal_buffer,0,MAX_BUFFER_LENGTH-1);
    memset(buffer,0,MAX_BUFFER_LENGTH-1);
    // Convert time to string
    for(iteration =0 ; iteration < ULTRASONIC_NUMS ; iteration ++)
    {
        strcat(internal_buffer, US_Data[iteration].Elapsed_Time_str);
    }
    if (copy_to_user(buffer,internal_buffer, MAX_BUFFER_LENGTH))
    {
        pr_err("Error copying elapsed time to user\n");
    }
    pr_info("buffer %s us\n", buffer);
    *offset += length;
    return length;
}

/*
The write function is used to set the GPIO pins for the sensor.
*/
ssize_t hcsr04_write(
    struct file *filp, const char *ubuffer,
    size_t length, loff_t *offset)
{
    uint8_t internal_buffer[MAX_BUFFER_LENGTH];
    uint8_t iteration;
    size_t written;
    pr_info("Attempting to Set GPIO pins\n");
    if (length < MAX_BUFFER_LENGTH) {
        written = length;
    } else {
        written = MAX_BUFFER_LENGTH;
    }
    if(copy_from_user(internal_buffer,ubuffer,length))
    {
        pr_err("No all bytes were copied from user\n");
    }

    if(!strcasecmp(internal_buffer,"Set_Ultrasonic_Pins"))
    {
        //Check validity of ultrasoinc pins
        for(iteration=0 ; iteration<ULTRASONIC_NUMS ; iteration++)
        {
            if (!gpio_is_valid(US_Data[iteration].Echo_Pin) || !gpio_is_valid(US_Data[iteration].Trig_Pin)  )
            {
                pr_err("Error whist parsing input, GPIO pin is invalid'\n");
                return -1;
            }
        }
        //Request ultrasonic pins
        
        for(iteration=0 ; iteration<ULTRASONIC_NUMS ; iteration++)
        {
            if (gpio_request(US_Data[iteration].Echo_Pin , US_Data[iteration].position) || gpio_request(US_Data[iteration].Trig_Pin , US_Data[iteration].position)  )
            {
                pr_err("Error when requesting %s pins",US_Data[iteration].position);
                return -1;
            }
        }
        //Set ultrasoinc pins
        for(iteration=0 ; iteration<ULTRASONIC_NUMS ; iteration++)
        {
            if (gpio_direction_input(US_Data[iteration].Echo_Pin)  )
            {
                printk("Failed to set GPIO pin %d as input\n", US_Data[iteration].Echo_Pin);
                return -1;
            }
            else
            {
                pr_info("Echo    of %s has been set to GPIO pin %d\n",US_Data[iteration].position, US_Data[iteration].Echo_Pin);
            }
            if(gpio_direction_output(US_Data[iteration].Trig_Pin,0))
            {
                printk("Failed to set GPIO pin %d as output\n", US_Data[iteration].Trig_Pin);
                return -1;
            }
            else
            {
                pr_info("Trigger of %s has been set to GPIO pin %d\n",US_Data[iteration].position,US_Data[iteration].Trig_Pin);
            }
        }
    }
    else
    {
        pr_err("You wrote %s\nCan't set Any GPIO PIN",internal_buffer);
    }
    return written;
} 


int __init hcsr04_init(void)
{
    // Get major number
    if ((alloc_chrdev_region(&dev, 0, 6, "hcsr04_dev")) < 0)
    {
        pr_err("Failed to allocate device numbers\n");
        goto failed_allocate_dev_numbers;
    }

    // Create character device structure
    cdev_init(&hcsr04_cdev, &fops);

    // Add the character device to the kernel
    if ((cdev_add(&hcsr04_cdev, dev, 1)) < 0)
    {
        pr_err("Falied to add the device\n");
        goto failed_add_device;
    }

    dev_class = class_create(THIS_MODULE, "hcsr04_class");

    if (!dev_class)
    {
        pr_err("Failed to create the device class\n");
        goto failed_create_class;
    }

    if (!device_create(dev_class, NULL, dev, NULL, "hcsr04"))
    {
        pr_err("Failed to create the device\n");
        goto failed_create_device;
    }

    return 0;

failed_create_device:
    device_destroy(dev_class, dev);

failed_create_class:
    class_destroy(dev_class);

failed_add_device:
    cdev_del(&hcsr04_cdev);

failed_allocate_dev_numbers:
    unregister_chrdev_region(dev, 1);

    return 1;
}

void __exit hcsr04_exit(void)
{
    uint8_t iteration;
    for(iteration=0 ; iteration<ULTRASONIC_NUMS ; iteration++)
    {
         gpio_free(US_Data[iteration].Echo_Pin);
         gpio_free(US_Data[iteration].Trig_Pin);
    }
    device_destroy(dev_class, dev);
    class_destroy(dev_class);
    cdev_del(&hcsr04_cdev);
    unregister_chrdev_region(dev, 1);
    return;
}

module_init(hcsr04_init);
module_exit(hcsr04_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DECSRIPTION);
MODULE_VERSION(DRIVER_VERSION);
