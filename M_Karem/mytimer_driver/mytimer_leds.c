#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/jiffies.h>
#include <linux/timer.h>


/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mahmoud Karem Zamel");
MODULE_DESCRIPTION("A simple test for Multi-timers");

/** variables for timers */
static struct timer_list timer1;
static struct timer_list timer2;
static struct timer_list timer3;
static struct timer_list timer4;

static int x=6 ;
char a=0 , b=0 , c=0 , d=0 ; /* Leds Status*/

/********************************************************************/
/****************** Time Out Functions ******************************/
/********************************************************************/

// Led1 ---> GPIO5
static void timeout_led_on_gpio5(struct timer_list * data)
{
	mod_timer(&timer1, jiffies + msecs_to_jiffies(1000));
	// timer1.expires = jiffies + 1*HZ;
	// add_timer (&timer1);
	
	a=!a; /* Toggle */

	/* Toggle GPIO 5 direction */
	if(gpio_direction_output(5, a)) {
		printk("Can not set GPIO 5 to output!\n");
		gpio_free(5);
	}

	return;
}

// Led2 ---> GPIO6
static void timeout_led_on_gpio6(struct timer_list * data)
{
	mod_timer(&timer2, jiffies + msecs_to_jiffies(2000));
	// timer2.expires = jiffies + 2*HZ;
	// add_timer (&timer2);

	b=!b;

	/* Toggle GPIO 5 direction */
	if(gpio_direction_output(6, b)) {
		printk("Can not set GPIO 6 to output!\n");
		gpio_free(6);
	}

	return;
}

// Led3 ---> GPIO13
static void timeout_led_on_gpio13(struct timer_list * data)
{
	mod_timer(&timer3, jiffies + msecs_to_jiffies(3000));
	// timer3.expires = jiffies + 3*HZ;
	// add_timer (&timer3);

	c=!c;

	/* Toggle GPIO 5 direction */
	if(gpio_direction_output(13, c)) {
		printk("Can not set GPIO 13 to output!\n");
		gpio_free(13);
	}

	return;
}

// Led4 ---> GPIO19
static void timeout_led_on_gpio19(struct timer_list * data)
{
	mod_timer(&timer4, jiffies + msecs_to_jiffies(4000));
	// timer4.expires = jiffies + 4*HZ;
	// add_timer (&timer4);

	d=!d;

	/* Toggle GPIO 5 direction */
	if(gpio_direction_output(19, d)) {
		printk("Can not set GPIO 19 to output!\n");
		gpio_free(19);
	}

	return;
}

/********************************************************************/

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) 
{
	
    printk("Hello, Kernel!\n");

	/********************** Init GPIO Pins ***************/
	/* GPIO 5 init */
	if(gpio_request(5, "rpi-gpio-5")) {
		printk("Can not allocate GPIO 5\n");
		return -1;
	}
	/* GPIO 6 init */
	if(gpio_request(6, "rpi-gpio-6")) {
		printk("Can not allocate GPIO 6\n");
		return -1;
	}
	/* GPIO 13 init */
	if(gpio_request(13, "rpi-gpio-13")) {
		printk("Can not allocate GPIO 13\n");
		return -1;
	}
	/* GPIO 19 init */
	if(gpio_request(19, "rpi-gpio-19")) {
		printk("Can not allocate GPIO 19\n");
		return -1;
	}

	/********************************** Init Timers ********************************/
	timer_setup(&timer1, timeout_led_on_gpio5 ,  (unsigned long)&x);
	timer_setup(&timer2, timeout_led_on_gpio6 ,  (unsigned long)&x);
	timer_setup(&timer3, timeout_led_on_gpio13,  (unsigned long)&x);
	timer_setup(&timer4, timeout_led_on_gpio19,  (unsigned long)&x);

	mod_timer(&timer1, jiffies + msecs_to_jiffies(1000));
	mod_timer(&timer2, jiffies + msecs_to_jiffies(2000));
	mod_timer(&timer3, jiffies + msecs_to_jiffies(3000));
	mod_timer(&timer4, jiffies + msecs_to_jiffies(4000));

	// init_timer(&timer1);
	// init_timer(&timer2);
	// init_timer(&timer3);
	// init_timer(&timer4);

	// timer1.function = timeout_led_on_gpio5 ;
	// timer2.function = timeout_led_on_gpio6 ;
	// timer3.function = timeout_led_on_gpio13 ;
	// timer4.function = timeout_led_on_gpio19 ;
	
	// timer1.data = (unsigned long)&x ;
	// timer2.data = (unsigned long)&x ;
	// timer3.data = (unsigned long)&x ;
	// timer4.data = (unsigned long)&x ;

	// timer1.expires = jiffies + 1*HZ;
	// add_timer (&timer1);
	// timer2.expires = jiffies + 2*HZ;
	// add_timer (&timer2);
	// timer3.expires = jiffies + 3*HZ;
	// add_timer (&timer3);
	// timer4.expires = jiffies + 4*HZ;
	// add_timer (&timer4);


	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) 
{

	printk("Goodbye, Kernel\n");
	
	/* Leds off */
	gpio_direction_output(5,0);
	gpio_direction_output(6,0);
	gpio_direction_output(13,0);
	gpio_direction_output(19,0);

	/* Free gpio pins*/
	gpio_free(5);
	gpio_free(6);
	gpio_free(13);
	gpio_free(19);
	
	/* Delete all timers */
	del_timer(&timer1);
	del_timer(&timer2);
	del_timer(&timer3);
	del_timer(&timer4);

}

module_init(ModuleInit);
module_exit(ModuleExit);


