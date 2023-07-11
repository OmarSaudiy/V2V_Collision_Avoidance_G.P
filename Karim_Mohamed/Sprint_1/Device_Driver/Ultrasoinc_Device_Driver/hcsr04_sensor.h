/*
__init signals to the compiler that this function is only run once on
initialisation.

__exit signals that is is only run once when the module is removed.

static means that the function is not visible ouside of this file.
*/
/* MODIFICATION LOG :                                                         */
/*********************************************************************************************************/
/* Created by        : Karim Mohamed ,Omar Hassan ,Omar Ibrahim   !Date : FEBRUARY 1, 2023 !Version :1.0 */
/* Modified by       : Karim Mohamed                              !Date : MARCH    1, 2023 !Version :1.1 */
/* Modified by       : Karim Mohamed                              !Date : MAY      8, 2023 !Version :2.0 */
/*********************************************************************************************************/

#define MAX_BUFFER_LENGTH           31
#define MAX_US_NAME_LENGTH          15
#define TRIGGER_HIGH_TIME_uS        5
#define SPEED_OF_SOUND_M_S          343
#define MAX_DISTANCE_CM_GO_AWAY     60

/*-------Ultrasonic Placement Macros---------*/
#define FRONT_LEFT        0
#define FRONT_MID         1
#define FRONT_RIGHT       2
#define BACK_LEFT         3
#define BACK_MID          4
#define BACK_RIGHT        5
#define ALL_US            6
/*-------------------------------------------*/

/*-------Ultrasonic Pins Macro---------*/
#define FRONT_LEFT_ECHO_PIN   7
#define FRONT_LEFT_TRIG_PIN   0

#define FRONT_MID_ECHO_PIN    1 
#define FRONT_MID_TRIG_PIN    5

#define FRONT_RIGHT_ECHO_PIN  12
#define FRONT_RIGHT_TRIG_PIN  6

#define BACK_RIGHT_ECHO_PIN   16
#define BACK_RIGHT_TRIG_PIN   13

#define BACK_MID_ECHO_PIN     20
#define BACK_MID_TRIG_PIN     19

#define BACK_LEFT_ECHO_PIN    21
#define BACK_LEFT_TRIG_PIN    26
/*-------------------------------------*/

#define ULTRASONIC_NUMS       6
/*-------------------------------------*/

typedef struct US
{
    uint8_t position[MAX_US_NAME_LENGTH];
    uint8_t Trig_Pin;
    uint8_t Echo_Pin;
    uint8_t Echo_Flag;
    ktime_t Start_Time;
    ktime_t Finish_Time;
    uint32_t Elapsed_Time;
    uint8_t  Elapsed_Time_str[6];

}US_t;


dev_t dev = 0;                  // Holds dev ice numbers
static struct class *dev_class;
static struct cdev hcsr04_cdev; // Character device

static int __init hcsr04_init(void);
static void __exit hcsr04_exit(void);

static int hcsr04_open(struct inode *inode, struct file *file);
static int hcsr04_release(struct inode *inode, struct file *file);
static ssize_t hcsr04_read(
    struct file *filp, char __user *buffer,
    size_t length, loff_t *offset);
static ssize_t hcsr04_write(
    struct file *filp, const char *buffer,
    size_t length, loff_t *offset);
/*
See https://tldp.org/LDP/lkmpg/2.4/html/c577.htm#:~:text=The%20file_operations%20Structure,to%20handle%20a%20requested%20operation.

As we do not need to do anything when the file is opened, we can ommit it.
We also do not care what happends when the release the device.
*/

static struct file_operations fops =
{
    .owner      = THIS_MODULE,
    .read       = hcsr04_read,
    .write      = hcsr04_write,
    .open       = hcsr04_open,
    .release    = hcsr04_release,
};
