#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "../LIB/Bit_math.h"
#include "../LIB/STD_TYPES.h"
#include "../HAL/Ultrasonic_Driver/hcsr04.h"
#include "../HAL/LCD_driver/lcd.h"
#include "../MCAL/UART.h"
#include "EEBL_FCW/EEBL_FCW.h"



u16 MyDirection=0;
u16 SenderDirection=70+180;



int main(void)
{
    if (!UART_init("/dev/serial0", 9600)) {
        fprintf(stderr, "Unable to initialize UART\n");
        return 1;
    }

    UART_sendData("Hello, UART!");

    char receivedData[100];
    UART_receiveData(receivedData, sizeof(receivedData));
    printf("Received: %s\n", receivedData);

    UART_close();
    
    /*gcc ./APP/main.c ./HAL/LCD_driver/lcd.c ./HAL/Ultrasonic_Driver/hcsr04.c ./APP/EEBL_FCW/EEBL_FCW.c ./MCAL/UART.c -o tst.exe -lwiringPi*/
    //US_vidInit();
    /*Act like os Call it*/
    // US_vInit();
    //  if (!UART_init("/dev/serial0", 9600)) {
    //     fprintf(stderr, "Unable to initialize UART\n");
    // }
    // UART_sendData("Hello, UART!");
    // char receivedData[100];



    // lcd_init();
    // while(1)
    // {
    // UART_receiveData(receivedData, sizeof(receivedData));
    // printf("Received: %s\n", receivedData);
    // US_Task();
    // // Get_Dir Func
    // EEBL_FCW_vidTask();
    // usleep(1000000);
    // }


}
