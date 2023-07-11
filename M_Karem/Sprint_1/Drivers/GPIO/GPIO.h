#ifndef GPIO_H_
#define GPIO_H_


#define SYSFS_GPIO_PATH             "/sys/class/gpio"
#define SYSFS_GPIO_EXPORT_FN        "/export"
#define SYSFS_GPIO_UNEXPORT_FN      "/unexport"
#define SYSFS_GPIO_VALUE            "/value"
#define SYSFS_GPIO_DIRECTION        "/direction"
#define SYSFS_GPIO_EDGE             "/edge"

#define DIR_IN                      "in"
#define DIR_OUT                     "out"

#define VALUE_HIGH                  "1"
#define VALUE_LOW                   "0"

#define EDGE_RISING                 "rising"
#define EDGE_FALLING                "falling"

#define POLL_TIMEOUT        10*1000



/**************************************************************************************/


// GPIO EXPORT
int gpio_export(int gpio_num);

// GPIO UNEXPORT
int gpio_unexport(int gpio_num);

// GPIO DIRECTION
int gpio_set_direction(int gpio_num,const char* dir);

// GPIO SET VALUE
int gpio_set_value(int gpio_num, const char *value);

// GPIO SET EDGE
int gpio_set_edge(int gpio_num, const char* edge);

int gpio_get_fd_to_value(int gpio_num) ;

/**************************************************************************************/



#endif