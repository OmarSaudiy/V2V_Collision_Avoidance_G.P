/*  
*   Auther : Mahmoud Karem Zamel 
*   About  : Interfacing GPIO Device Driver For RPI3
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>



#include "GPIO.h"

/**************************************************************************************/
/*      HELPER FUNCTION       */

// FILE OPERATION
static int File_Open_Write_Close(const char *fname, const char *wdata)
{
    int fd;

    fd = open(fname, O_WRONLY | O_NONBLOCK);
    if(fd < 0) {
        printf("Could not open file %s...%d\r\n",fname,fd);
    }
    write(fd,wdata,strlen(wdata));
    close(fd);

    return 0;
}
/**************************************************************************************/


// GPIO EXPORT
int gpio_export(int gpio_num) 
{
    char gpio_str[4];
    sprintf(gpio_str,"%d",gpio_num);
    return File_Open_Write_Close(SYSFS_GPIO_PATH SYSFS_GPIO_EXPORT_FN,gpio_str);
}

// GPIO UNEXPORT
int gpio_unexport(int gpio_num) 
{
    char gpio_str[4];
    sprintf(gpio_str,"%d",gpio_num);
    return File_Open_Write_Close(SYSFS_GPIO_PATH SYSFS_GPIO_UNEXPORT_FN,gpio_str);
}

// GPIO DIRECTION
int gpio_set_direction(int gpio_num,const char* dir) 
{
    char path_str[40];
    sprintf(path_str,"%s/gpio%d%s",SYSFS_GPIO_PATH,gpio_num,SYSFS_GPIO_DIRECTION);
    return File_Open_Write_Close(path_str,dir);
}

// GPIO SET VALUE
int gpio_set_value(int gpio_num, const char *value) 
{
    char path_str[40];
    sprintf(path_str,"%s/gpio%d%s",SYSFS_GPIO_PATH,gpio_num,SYSFS_GPIO_VALUE);
    return File_Open_Write_Close(path_str,value);
}

// GPIO SET EDGE
int gpio_set_edge(int gpio_num, const char* edge) 
{
    char path_str[40];
    sprintf(path_str,"%s/gpio%d%s",SYSFS_GPIO_PATH,gpio_num,SYSFS_GPIO_EDGE);
    return File_Open_Write_Close(path_str,edge);
}

int gpio_get_fd_to_value(int gpio_num) 
{
    int fd;
    char fname[40];
    sprintf(fname,"%s/gpio%d%s",SYSFS_GPIO_PATH,gpio_num,SYSFS_GPIO_VALUE);
    fd = open(fname, O_RDONLY | O_NONBLOCK);
    if(fd < 0) {
        printf("Could not open file %s...%d\r\n",fname,fd);
    }
    return fd;
}

/**************************************************************************************/

