#include "Bit_math.h"
#include "STD_TYPES.h"
#include "BSW.h"
#include "hcsr04.h"

u16 MyDirection=70;
u16 SenderDirection=70;


int main(void)
{
    US_vidInit();
	/***** CAlling BSW Algo ***********/
    BSW_vAlgorithm();
	
}
