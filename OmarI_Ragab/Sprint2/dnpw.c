#include "dnpw.h"

//Std types
//Lcd Lib
//Led Lib
//ultrasonic driver
//Porotocol  lib

/***************************************/
/*--- These funcs for testing only ---*/
static void LED_ON(void);
static void LCD_vidSendString(void);
/**************************************/

/*--- Protocol calilng it ---*/
void DNPW_vidDnpwAlg_Id(u8 DirctionOfSender)
{
    if(DirctionOfSender == MyDirction)
    {
		
		LED_ON();
		LCD_vidSendString();
    }
    else
    {
        //Do nothing
    }

}

static void LED_ON(void)
{
    printf("Led is on\n");
}
static void LCD_vidSendString(void)
{
    printf("Lcd Warning\n");
}


/***********************************************/
/*----- OS Task ----*/

  
