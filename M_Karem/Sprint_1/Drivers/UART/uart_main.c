/* main.c */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "UART.h"

#define RX_BUF_SIZE 255
char Buffer[RX_BUF_SIZE];


int main() {
	

	UART_Open_Init();


	printf("You have 10s to send me some input data...\n");
	sleep(10);

	UART_Read(Buffer,RX_BUF_SIZE);

	UART_Write("Hello from my RPi\n\r");

	UART_Close();

	return 0;
}
