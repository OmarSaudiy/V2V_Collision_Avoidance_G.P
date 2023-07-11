#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#include "STD_TYPES.h"


#include "hcsr04.h"


void US_vidInit()
{
    s8 fd=0;
    u8 buf[8];
    fd = open(US_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device file!");
        exit(1);
    }
    snprintf(buf, sizeof(buf), "ECHO %02d", ECHO_PIN);
    write(fd, buf, sizeof(buf));
    snprintf(buf, sizeof(buf), "TRIG %02d", TRIG_PIN);
    write(fd, buf, sizeof(buf));
    close(fd);
}


/*--------------------------*/
/*----return distance in cm*/
u8 US_u8GetDistance()
{
    s8 fd=0;
    u8 data[6];
    u8 dist ;
    s32 trip=0 ;
    f32 secs ;
    fd = open(US_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device file!");
        exit(1);
    }
    read(fd, data, sizeof(data));
    trip = atoi(data);
    secs = trip * 1e-6 / 2;
    dist = 343 * secs *100;
    close(fd);
    return dist;

}

/*------------Random Distance Used for Testing-----------------*/
int HCSR04_Get_Distance_Random (int l , int r , int count)
{
	/* Generate one(count) random number in the range [l:r] */
	int i,rand_num;
	for (i=0 ; i<count ; i++)
	{
		rand_num = (rand() % (r - l + 1 )) + l ;
	}
	return rand_num;
}
