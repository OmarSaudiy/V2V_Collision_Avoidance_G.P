#include "C:/Users/007/Desktop/TestBSW/LIB/STD_TYPES.h"
#include "C:/Users/007/Desktop/TestBSW/LIB/Bit_math.h"
#include "C:/Users/007/Desktop/TestBSW/HAL/Ultrasonic_Driver/hcsr04.h"
#include "C:/Users/007/Desktop/TestBSW/HAL/LCD_driver/4_bit_mode/lcd.h"
#include "BSW_test.h"

u16 MyDirection;
u16 SenderDirection;


int main(void)
{
    US_vInit();
	/***** CAlling BSW Algo ***********/
    BSW_vAlgorithm();
	
}
