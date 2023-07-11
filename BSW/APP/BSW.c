#include <stdio.h>
#include "C:/Users/007/Desktop/TestBSW/LIB/STD_TYPES.h"
#include "C:/Users/007/Desktop/TestBSW/LIB/Bit_math.h"
#include "C:/Users/007/Desktop/TestBSW/HAL/Ultrasonic_Driver/hcsr04.h"
#include "C:/Users/007/Desktop/TestBSW/HAL/LCD_driver/4_bit_mode/lcd.h"
#include "BSW.h"



/* 
********************* This file include actually two phases:    *********************
********************* 1- Implementation of BSW Algorithm        *********************
********************* 2- Implementation for a sample test		*********************			  
*************************************************************************************
*************************************************************************************
*/


/************** After Arrive The BSW_ID ,OS will Call The Algorithm of BSW ***************/

extern u16 MyDirection, SenderDirection;

u8 Front_rightDis, Front_leftDis, Back_leftDis, Back_rightDis;

/*********** Buffer for Lcd ***********/
u8 buffer[]="Blind Spot Warning";

void BSW_vAlgorithm(void)
{
	/* for check that is BSW actually */
	  Back_leftDis   = Get_BackLeftDis(); // Get Back Left Distance
      Back_rightDis  = Get_BackRightDis(); // Get Back Right Distance
	/* for Sample test */
	/*
      Back_leftDis=HCSR04_Get_Distance_Random (1, 19, 0);
      Back_rightDis=HCSR04_Get_Distance_Random (1, 19, 0);*/
	  
    if( Back_leftDis < SAFE_DISTANCE ||  Back_rightDis < SAFE_DISTANCE )
	{

		BSW_Action();
		/*
		for Sample test
		*/
		/* 
		printf("Calling BSW_vAlgorithm\n"); */

    }
	else
	{
		// Do Nothing
		/* for Sample test */
		/*
		printf("Nothing BSW_vAlgorithm \n"); */
	}

}

void BSW_SendID(void)
{
	Front_rightDis = Get_FrontRightDis(); // Get Front Right Distance
    Front_leftDis  = Get_FrontLeftDis(); // Get Front Left Distance
	/* for Sample test */
	/*
	Front_rightDis = HCSR04_Get_Distance_Random (1, 19, 0);
    Front_leftDis  = HCSR04_Get_Distance_Random (1, 19, 0);	*/
	if( Front_rightDis < SAFE_DISTANCE || Front_leftDis < SAFE_DISTANCE )
	{
		//pESP32_Send(BSW_id,MyDirection);
		/*
		For Sample test 
		*/
		/*
		printf("BSW_SendID Calling Function ...\n");*/
		LCD_State_ID = LCD_BUSY;
	}
	else
	{
        // Do Nothing
		/* for sample test */
		/*
		printf("Nothing BSW_SendID \n");*/
	}

}

void BSW_Action( void )
{

	Back_leftDis   = Get_BackLeftDis();
    Back_rightDis  = Get_BackRightDis();
	/* for Sample test */
	/*
	Back_leftDis   = HCSR04_Get_Distance_Random (15, 20, 0);
    Back_rightDis  = HCSR04_Get_Distance_Random (1, 26, 0);	*/
	if(Back_rightDis < SAFE_DISTANCE)
	{
		LCD_vDisplay("vehicle approaching from back right");
		//LED_ON();//Right led
		/* for sample test */
		/*
		printf("dis=%d\n",Back_rightDis);
		printf("BSW_Action Calling Function ...\n");*/
		LCD_State_ID = LCD_BUSY;

	}
	else if(Back_leftDis < SAFE_DISTANCE)
	{
		LCD_vDisplay("vehicle approaching from back left");
		//LED_On();//Left led
		/* for sample test */
		/*
		printf("dis=%d\n",Back_leftDis);
		printf("BSW_Action Calling Function ...\n");*/
		LCD_State_ID = LCD_BUSY;
	}
   else if(Back_rightDis < SAFE_DISTANCE && Back_leftDis < SAFE_DISTANCE)
   {
		LCD_vDisplay("vehicles approaching from both sides");
		//LED_On();//Left led
		//LED_On();//Right led
		/* for sample test */
		/* printf("DIS1=%d   DIS2=%d \n",Back_rightDis,Back_leftDis);
		   printf("BSW_Action_else Calling Function ...\n");*/
		LCD_State_ID = LCD_BUSY;
   }
   else
   {
	   // Do Nothing
	   
	   
	   /* for Sample test */
	  /* printf("DIS1=%d   DIS2=%d \n",Back_rightDis,Back_leftDis);
	   printf("Nothing_BSW_Action \n");*/
   }
}



u8 Get_FrontRightDis(void)
{
	u8 Dis;
	Dis = US_u8GetDistance();
	return Dis;
}

u8 Get_FrontLefttDis( void)
{
	u8 Dis;
	Dis = US_u8GetDistance();
	return Dis;
}
u8 Get_BackRightDis( void)
{
	u8 Dis;
	Dis = US_u8GetDistance();
	return Dis;
}

u8 Get_BackLefttDis(void)
{
	u8 Dis;
	Dis = US_u8GetDistance();
	return Dis;
}



