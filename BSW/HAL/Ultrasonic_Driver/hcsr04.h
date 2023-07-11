/******************************************************************************/
/*                                                                            */
/* !Layer           : Hardware Abstraction Layer (HAL)                        */
/*                                                                            */
/* !Component       : US                                                      */
/* !Description     : Ultrasonic driver module                                */
/*                                                                            */
/* !Module          : US                                                      */
/* !Description     : US Module interface                                     */
/*                                                                            */
/* !File            : hcsr04.h                                                */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : V2V Collision avoidance                                 */
/*                                                                            */
/* !Target          : Raspberry Pi 3 model B                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/* Created by        : Karim Mohamed                    !Date : MARCH  1, 2023*/
/* Modified by       : Karim Mohamed                    !Date : MARCH 24, 2023*/
/******************************************************************************/


#ifndef HCSR04_H
#define HCSR04_H


#define ECHO_PIN 3
#define TRIG_PIN 2
#define US_PATH  "/dev/hcsr04"

void US_vidInit(void);
u8  US_u8GetDistance(void);


/*------------Random Distance Used for Testing-----------------*/
extern int HCSR04_Get_Distance_Random (int l , int r , int count);


#endif
