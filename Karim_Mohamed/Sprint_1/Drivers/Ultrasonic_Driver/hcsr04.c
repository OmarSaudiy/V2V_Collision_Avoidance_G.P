#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>

#include "hcsr04.h"
US_t US_Data[ULTRASONIC_NUMS]=
{ 
    {.Position="US_FRONT_LEFT" , .Distance=0}, 
    {.Position="US_FRONT_MID"  , .Distance=0}, 
    {.Position="US_FRONT_RIGHT", .Distance=0}, 
    {.Position="US_BACK_LEFT"  , .Distance=0},
    {.Position="US_BACK_MID"   , .Distance=0}, 
    {.Position="US_BACK_RIGHT" , .Distance=0}
};

void US_vInit()
{
    int32_t fd=0;
    uint8_t buf[20];
    fd = open(US_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device file!");
        exit(1);
    }
    snprintf(buf, sizeof(buf), "Set_Ultrasonic_Pins");
    if(write(fd, buf, sizeof(buf)) == -1)
    {
        printf("An error occured\n");
    }
    
    close(fd);
}


/*--------------------------*/
/*----Get distance for all ultrasonic*/
void US_Task(void)
{
    int32_t fd=0;
    int32_t trip=0 ;
    uint8_t buffer[MAX_BUFFER_LENGTH];
    uint8_t iteration;
    float secs  ;

    buffer[0]=ALL_US; //Send to kernel space 
    fd = open(US_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device file!");
        exit(1);
    }
    read(fd, buffer, MAX_BUFFER_LENGTH);
    close(fd);
    printf("back string is %s\n",buffer);
    for( iteration=0 ; iteration < ULTRASONIC_NUMS ; iteration++)
    {
        strncpy(US_Data[iteration].Time_str,buffer+iteration*(TIME_STR_LENGTH-1),TIME_STR_LENGTH-1);
        US_Data[iteration].Time_str[(TIME_STR_LENGTH-1)]='\0';
        trip = atoi( US_Data[iteration].Time_str);
        secs = trip * 1e-6 / 2;
        US_Data[iteration].Distance = 343 * secs *100;
        printf("%s Distance is %.2f cm\n",US_Data[iteration].Position,US_Data[iteration].Distance);
    }

}

float  US_Get_Distance(uint8_t UltrasonicPosition)
{
    float dis;
    if(0 <= UltrasonicPosition && UltrasonicPosition < ULTRASONIC_NUMS)
    {
       dis= US_Data[UltrasonicPosition].Distance;
    }
    else
    {
       dis= -1;
    }
     return dis;
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