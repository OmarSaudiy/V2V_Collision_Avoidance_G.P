#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "hcsr04.h"



cdint main() {
    double dis=0;
    US_vInit();
    while(1)
    {
        US_Task();
        dis=US_Get_Distance(FRONT_LEFT);
        if(dis >30 || dis==0)
        {
            printf("There is no object Left you within 30 cm\n");
        }
        else
        {
            printf("Warning there is an object Left you   %.2f cm away\n",dis);
        } 

        dis=US_Get_Distance(FRONT_RIGHT);
        if(dis >30 || dis==0)
        {
            printf("There is no object Right you within 30 cm\n");
        }
        else
        {
            printf("Warning there is an object right you  %.2f cm away\n",dis);
        } 

        dis=US_Get_Distance(FRONT_MID);
        if(dis >30 || dis==0)
        {
            printf("There is no object front of you within 30 cm\n");
        }
        else
        {
            printf("Warning there is an object front of you within %.2f cm away\n",dis);
        } 

        dis=US_Get_Distance(BACK_LEFT);
        if(dis >30 || dis==0)
        {
            printf("There is no object BACK_LEFT within 30 cm\n");
        }
        else
        {
            printf("Warning there is an object BACK_LEFT within  %.2f cm away\n",dis);
        } 

        dis=US_Get_Distance(BACK_RIGHT);
        if(dis >30 || dis==0)
        {
            printf("There is no object BACK_Right  within 30 cm\n");
        }
        else
        {
            printf("Warning there is an object BACK_LEFT within  %.2f cm away\n",dis);
        } 

        dis=US_Get_Distance(BACK_MID);
        if(dis >30 || dis==0)
        {
            printf("There is no object back you within 30 cm\n");
        }
        else
        {
            printf("Warning there is an object back you within  %.2f cm away\n",dis);
        } 
        printf("----------------------------------------------------------------\n\n");
        sleep(1);
    }
    return 0;
}
