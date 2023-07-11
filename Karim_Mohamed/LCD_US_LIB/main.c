#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include "LCD/lcd.h"
#include "Ultrasonic_Driver/hcsr04.h"


int main()
{
    int dis=0;
    char x[4]="";
    US_vInit();
    if (wiringPiSetupGpio() == -1) {
        printf("Failed to initialize WiringPi\n");
        return 1;
    }

    pinMode(LCD_RS, 1);
    pinMode(LCD_E,  1);
    pinMode(LCD_D4, 1);
    pinMode(LCD_D5, 1);
    pinMode(LCD_D6, 1);
    pinMode(LCD_D7, 1);

    lcd_init();

    lcd_set_cursor(0, 0);
    while(1)
    {
        lcd_send_command(0x01);
        usleep(2000);
        lcd_set_cursor(0,0);
        US_Task();
        dis=US_Get_Distance(FRONT_MID);
        if(dis >30 || dis==0)
        {
            lcd_write_string("No object");
            printf("There is no object Left you within 30 cm\n");
        }
        else
        {
            printf("Warning there is an object Left you   %.2f cm away\n",dis);
            sprintf(x,"%4d",dis);
            lcd_write_string("Warning!! DIS=");
            lcd_set_cursor(0,1);
            lcd_write_string(x);

        } 
        printf("----------------------------------------------------------------\n\n");
        usleep(1000000);
    }

}