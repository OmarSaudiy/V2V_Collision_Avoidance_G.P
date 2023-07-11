/**** main.c ******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>


#include "GPIO.h"


int main () 
{
    unsigned int gpio_out;
    struct pollfd fdpoll;
    int num_fdpoll = 1;
    int gpio_in, gpio_in_fd;
    int res;
    int looper = 0;
    char *buf[64];

    /* to make sure */
    gpio_unexport(gpio_out);
    gpio_unexport(gpio_in);

    gpio_export(gpio_out);
    gpio_export(gpio_in);

    gpio_set_direction(gpio_out,DIR_OUT);
    gpio_set_direction(gpio_in,DIR_IN);

    gpio_set_value(gpio_out,VALUE_HIGH);
    gpio_set_edge(gpio_in,EDGE_FALLING);

    gpio_in_fd = gpio_get_fd_to_value(gpio_in);

    // We will wait for button press here for 10s or exit anyway
    while(looper<10) {
        memset((void *)&fdpoll,0,sizeof(fdpoll));
        fdpoll.fd = gpio_in_fd;
        fdpoll.events = POLLPRI;

        res = poll(&fdpoll,num_fdpoll,POLL_TIMEOUT);

        if(res < 0) {
            printf("Poll failed...%d\r\n",res);            
        }
        if(res == 0) {
            printf("Poll success...timed out or received button press...\r\n");
        }
        if(fdpoll.revents & POLLPRI) {
			lseek(fdpoll.fd, 0, SEEK_SET);
			read(fdpoll.fd, buf, 64);
            printf("Received a button press...%d\r\n",looper);
        }
        ++looper;
        fflush(stdout);
    }

    close(gpio_in_fd);
    gpio_set_value(gpio_out,VALUE_LOW);
    gpio_unexport(gpio_out);
    gpio_unexport(gpio_in);

    return 0;
}