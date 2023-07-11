#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define PATH     "/dev/hcsr04"
/*-------Ultrasonic Placement Macros---------*/
#define US_FRONT_LEFT        0
#define US_FRONT_MID         1
#define US_FRONT_RIGHT       2
#define US_BACK_LEFT         3
#define US_BACK_MID          4
#define US_BACK_RIGHT        5
#define US_ALL               6
int main() {
    int32_t trip;
    int i;
    double secs ;
    double dist ;
    struct timespec start_time, end_time;
    double time_taken;



    
    int fd = open(PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device file!");
        exit(1);
    }
    
    char buf[31];
    char us_data[6][6];
    strcpy(buf,"Set_Ultrasonic_Pins");
    write(fd, buf, sizeof(buf));
    memset(buf,0,sizeof(buf));
    buf[0]=6;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    read(fd, buf, sizeof(buf));
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    time_taken = end_time.tv_nsec - start_time.tv_nsec;
    printf("Time taken by read function: %f ms\n", time_taken/1000000);

    printf("back string is %s\n",buf);

    for(i=0;i<6;i++)
    {
        
        strncpy(us_data[i],buf+i*5,5);
        us_data[i][5]='\0';

        trip= atoi(us_data[i]);  
        printf("trip is %d us_data[%d] is %s \n",trip,i,us_data[i]);
        secs = trip * 1e-6 / 2;
        dist = 343 * secs;    
        if(dist*100>200)
        {
            printf("There is no object within 2 Meters\n");
        }
        else
        {
            printf("Warning there is an object   %.2f cm away\n",dist * 100);
        } 
    }

    close(fd);
    // open(PATH, O_RDWR);
    // buf[0]=US_BACK_LEFT;
    // read(fd, buf, sizeof(buf));
    // trip = atoi(buf);
    // secs = trip * 1e-6 / 2;
    // dist = 343 * secs;
    // if(dist*100>200)
    // {
    //     printf("There is no object within 2 Meters\n");
    // }
    // else
    // {
    //      printf("Warning there is an object   %.2f cm away\n",dist * 100);
    // } 
    // close(fd);
    // while(1)
    // {
    // open("/dev/hcsr04", O_RDWR);   
    // read(fd, buf, sizeof(buf));
    // trip = atoi(buf);
    // secs = trip * 1e-6 / 2;
    // dist = 343 * secs;
    // if(dist*100>200)
    // {
    //     printf("There is no object within 2 Meters\n");
    // }
    // else
    // {
    //      printf("Warning there is an object   %.2f cm away\n",dist * 100);
    // } 
    // close(fd);
    // sleep(1);
    // }
    return 0;
}
