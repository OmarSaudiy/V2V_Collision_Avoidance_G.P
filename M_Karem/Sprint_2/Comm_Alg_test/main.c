/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    main.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 * Author     : Mahmoud Karem Zamel
 * Created on : Mar 22, 2023
 */  

/*************************************************************/
#include "Platform_Types.h"

#include "ESP32.h"
#include "Comm_Algorithm.h"

/***********************************/
void setup ()
{
	//init all the drivers ...
	//init Block
	ESP32_Init();

	//Set states pointers for each block (init States for each one)
	pESP32_state = STATE(ESP32_busy);

}

int main ()
{
	volatile int Delay ;

	setup();

	while (1)
	{
		//call sate for each block
		pESP32_state();

		for (Delay=0 ; Delay<=10000 ; Delay++);

	}
	return 0;
}

/***********************************/
