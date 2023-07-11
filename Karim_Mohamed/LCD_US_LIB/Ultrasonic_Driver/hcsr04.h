/***********************************************************************************************/
/*                                                                                             */
/* !Layer           : Hardware Abstraction Layer (HAL)                                         */
/*                                                                                             */
/* !Component       : US                                                                       */
/* !Description     : Ultrasonic driver module                                                 */
/*                                                                                             */
/* !Module          : US                                                                       */
/* !Description     : US Module interface                                                      */
/*                                                                                             */
/* !File            : hcsr04.h                                                                 */
/*                                                                                             */
/* !Scope           : Public                                                                   */
/*                                                                                             */
/* !Coding language : C                                                                        */
/*                                                                                             */
/* !Project         : V2V Collision avoidance                                                  */
/*                                                                                             */
/* !Target          : Raspberry Pi 3 model B                                                   */
/*                                                                                             */
/*                                                                                             */
/***********************************************************************************************/
/*                               MODIFICATION LOG                                              */
/***********************************************************************************************/
/* Created by        : Karim Mohamed                    !Date : MARCH  1, 2023  !Version : 1.0 */
/* Modified by       : Karim Mohamed                    !Date : MARCH 24, 2023  !Version : 1.1 */
/* Modified by       : Karim Mohamed                    !Date : MAY   12, 2023  !Version : 2.0 */
/***********************************************************************************************/

#ifndef HCSR04_H
#define HCSR04_H

/*------------Lentgh of strings--------------*/
#define MAX_BUFFER_LENGTH           31
#define MAX_US_NAME_LENGTH          15
#define TIME_STR_LENGTH             6
/*-------Ultrasonic Placement Macros---------*/
#define FRONT_LEFT         0
#define FRONT_MID          1
#define FRONT_RIGHT        2
#define BACK_LEFT          3
#define BACK_MID           4
#define BACK_RIGHT         5
#define ALL_US             6
/*---------------------------------------------*/
#define ULTRASONIC_NUMS    6
#define SPEED_OF_SOUND_M_S 343
/*-----------------File Path-------------------*/
#define US_PATH  "/dev/hcsr04"

typedef struct US
{
    uint8_t Position[MAX_US_NAME_LENGTH];
    uint8_t Time_str[TIME_STR_LENGTH];
    float Distance;

}US_t;

void  US_vInit(void);
void  US_Task(void);
float US_Get_Distance(uint8_t UltrasonicPosition);

/*------------Random Distance Used for Testing-----------------*/
extern int HCSR04_Get_Distance_Random (int l , int r , int count);



#endif
