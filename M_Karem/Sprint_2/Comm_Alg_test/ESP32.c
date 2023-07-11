/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ESP32.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 * Author     : Mahmoud Karem Zamel
 * Created on : Mar 22, 2023
 */


#include "ESP32.h"
#include "Comm_Algorithm.h"

int ESP32_Get_MSG_Random (int l , int r , int count);


/* 1.Variables */
static int ID_Val=0 ;

/* 2.STATE Pointer to func */
void (*pESP32_state)();

/* 3.Definition of states/func */

STATE_define(ESP32_busy)
{
	// State Name
	ESP32_State_ID = ESP32_BUSY;

	//State_Action
	ID_Val = ESP32_Get_MSG_Random (0,5,1);
	//ID_Val = ESP32_Get_MSG(); //Using UART read

	printf ("ESP_busy state : Message (ID) =%d \n" ,ID_Val);


	// Check event and update state
	Set_MSG_ID_Comm_ALG_ID(ID_Val);
	pESP32_state = STATE(ESP32_busy);
}


void ESP32_Init()
{
	//Init ESP32 Driver
	printf ("ESP32_Init\n");

}

/***************************************************************/

int ESP32_Get_MSG_Random (int l , int r , int count)
{
	/* Generate one(count) random number in the range [l:r] */
	int i,rand_num;
	for (i=0 ; i<count ; i++)
	{
		rand_num = (rand() % (r - l + 1 )) + l ;
	}
	return rand_num;
}



