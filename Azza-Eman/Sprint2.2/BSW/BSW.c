#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "STD_TYPES.h" 
#include "Bit_math.h" 
#include "hcsr04.h"
#include "lcd.h"
#include "BSW.h"

extern uint16_t MyDirection, SenderDirection;

uint8_t Front_rightDis, Front_leftDis, Back_leftDis, Back_rightDis;

/*********** Buffer for Lcd ***********/
char buffer[]="Blind Spot Warning";

void BSW_vAlgorithm(void)
{
	BSW_SendID();
	Back_leftDis   = Get_BackLeftDis(); // Get Back Left Distance
    Back_rightDis  = Get_BackRightDis(); // Get Back Right Distance
	printf("Calling BSW_vAlgorithm\n");
    if( Back_leftDis < SAFE_DISTANCE ||  Back_rightDis < SAFE_DISTANCE )
	{
		
		BSW_Action();
			
    }	
	else
	{
		// Do Nothing
		printf("Nothing BSW_vAlgorithm \n");
	}
	
}

void BSW_SendID(void)
{
	Front_rightDis = Get_FrontRightDis(); // Get Front Right Distance
    Front_leftDis  = Get_FrontLefttDis(); // Get Front Left Distance
	if( Front_rightDis < SAFE_DISTANCE || Front_leftDis < SAFE_DISTANCE )
	{
		pESP32_Send(BSW_id,MyDirection);
		printf("BSW_SendID Calling Function ...\n");
		LCD_State_ID = LCD_BUSY;
	}
	else
	{  
        // Do Nothing
		printf("Nothing BSW_SendID \n");
	}
	
}

void BSW_Action( void )
{
	Back_leftDis   = Get_BackLeftDis();
    Back_rightDis  = Get_BackRightDis();
	if(Back_rightDis < SAFE_DISTANCE)
	{
		buffer="vehicle approaching from back right";
		LCD_vDisplay(buffer);
		LED_On();//Right led
		printf("BSW_Action Calling Function ...\n");
		LCD_State_ID = LCD_BUSY;
		
	}
	else if(Back_leftDis < SAFE_DISTANCE)
	{
		buffer="vehicle approaching from back left";
		LCD_vDisplay(buffer);
		LED_On();//Left led	
		printf("BSW_Action Calling Function ...\n");
		LCD_State_ID = LCD_BUSY;		
	}
   else if(Back_rightDis < SAFE_DISTANCE && Back_leftDis < SAFE_DISTANCE)
   {
		buffer="vehicles approaching from both sides";
		LCD_vDisplay(buffer);
		LED_On();//Left led	
		LED_On();//Right led
		printf("BSW_Action Calling Function ...\n");
		LCD_State_ID = LCD_BUSY;
   }
   else
   {
	   // Do Nothing
	   printf("Nothing_BSW_Action \n");
   }
}


uint8_t Get_FrontRightDis(void)
{
	uint8_t Dis=20;
	Dis = US_Get_Distance( );
	return Dis;
}

uint8_t Get_FrontLefttDis( void)
{
	uint8_t Dis=15;
	Dis = US_Get_Distance( );
	return Dis;
}
uint8_t Get_BackRightDis( void)
{
	uint8_t Dis=15;
	Dis = US_Get_Distance( );
	return Dis;
}

uint8_t Get_BackLefttDis(void)
{
	uint8_t Dis=20;
	Dis = US_Get_Distance( );
	return Dis;
}
