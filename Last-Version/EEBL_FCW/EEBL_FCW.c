#include <stdio.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Bit_math.h"
#include "../../HAL/Ultrasonic_Driver/hcsr04.h"
#include "../../HAL/LCD_driver/lcd.h"
#include "../../MCAL/UART.h"
#include "EEBL_FCW.h"

#define SENDER_OPPOSITE_DIRECTION  (SenderDirection-180)
//Max return Distance is 60 cm even if there is no object front of US
#define CRITICAL_DISTANCE          (30) //20 cm
#define VERY_SMALL_DISTANCE        (10) //10 cm
#define EEBL_FC_ID                 'A'

static void EEBL_vidAction(void);
static void FCW_vidAction(void);

extern u16 MyDirection;
/****----OS Task For EEBL and FC----****/
void EEBL_FCW_vidTask()
{
    char msg[5];
    sprintf(msg,"%3d",MyDirection);
    strcat(msg,"A");
    if( (US_Get_Distance(FRONT_MID) < CRITICAL_DISTANCE) && (US_Get_Distance(FRONT_MID)>0) )
     {
        
         send_string(msg);
        // lcd_send_command(0x01);
        // lcd_set_cursor(0,0);
        // lcd_write_string("Object Infront!");
        /*For SW testing*/
        printf("EEBL_FCW_vidTask Called!\n");
    }
    else
    {
        // lcd_send_command(0x01);
        // lcd_set_cursor(0,0);
        // lcd_write_string("NO Object Infront!");
    }
}

/*-------Case From ID Task--------*/
void  EEBL_FCW_vidAlgId(int SenderDirection)
{
    int Diff_Dir=MyDirection-SenderDirection;
    if(Diff_Dir <0)
    {
        Diff_Dir*=-1;
    }

    printf("Diff Dir = %d",Diff_Dir);
    switch(Diff_Dir)
    {
        //EEBL System Action
        case 0 :
        case 360 :                                
                    printf("Calling EEBL_vidAction !\n");
                    EEBL_vidAction();
                    break;
         //FCW System Action
        case 180 :                          
                    printf("Calling FCW_vidAction !\n");
                    FCW_vidAction();
                    break;
        default :
                    //Do nothing
                    break;
    }

}

static void EEBL_vidAction(void)
{
    u8 Distance;
    Distance = US_Get_Distance(BACK_MID) ;

    if( Distance <= CRITICAL_DISTANCE && Distance >0)
    {
        /*** display warning message on LCD ***/
        lcd_send_command(0x01);
        lcd_set_cursor(0,0);
        lcd_write_string("Becarful !!!");
        lcd_set_cursor(0,1);
        lcd_write_string("Car Behind you!");
        /*For SW testing*/
        printf("Car Behind you!\n");
    }
    else
    {
        /*---NO CARS BEHIND ME---*/
        /*---Do nothing---*/
         /*For SW testing*/
        printf("Do nothing!\n");
    }
}

static void FCW_vidAction(void)
{
    u8 Distance;
    Distance=US_Get_Distance(FRONT_MID) ;

    /***   if the distance back to normal     ***/
    if(Distance > CRITICAL_DISTANCE)
    {
    	/*** clear LCD ***/
        lcd_send_command(0x01);
        lcd_set_cursor(0,0);
        /*** switch off LED ****/
        //LED_Off();

        /*For SW testing*/
    	printf("Distance > CRITICAL_DISTANCE!\n");
    }
    /***   if the distance is small     ***/
    else if( (Distance <= CRITICAL_DISTANCE ) && (Distance > VERY_SMALL_DISTANCE) )
    {
        /*** display warning message on LCD ***/
        lcd_send_command(0x01);
        lcd_set_cursor(0,0);
        lcd_write_string("Object Infront!");
        /*** switch on LED ****/
        //LED_On();

        /*For SW testing*/
    	printf(" (Distance<=CRITICAL_DISTANCE ) && (Distance>VERY_SMALL_DISTANCE) \n");
    }
    else if( (Distance <= VERY_SMALL_DISTANCE && Distance>0) )
    {
        /*** stop the car using DC motor ****/
        //Stop_DC_Motor();
        lcd_send_command(0x01);
        lcd_set_cursor(0,0);
        lcd_write_string("Object Infront!");
        /*For SW testing*/
    	printf(" Distance <= VERY_SMALL_DISTANCE \n");
    }
    else
    {
        /*** do nothing ****/
    }
}
