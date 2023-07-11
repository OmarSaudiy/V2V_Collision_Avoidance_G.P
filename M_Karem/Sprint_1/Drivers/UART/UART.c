/*  
*   Auther : Mahmoud Karem Zamel 
*   About  : Interfacing UART Device Driver For RPI3
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "UART.h"

struct termios options; /* Serial ports setting */

int fd_UART, len;

void UART_Open_Init ()
{
    fd_UART = open("/dev/serial0", O_RDWR | O_NDELAY | O_NOCTTY);
	if (fd_UART < 0) {
		perror("Error opening serial port");
	}
	
	/* Set up serial port */
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;

	/* Apply the settings */
	tcflush(fd_UART, TCIFLUSH);
	tcsetattr(fd_UART, TCSANOW, &options);
}

void UART_Read (char Buffer[] , int Size_Buf)
{
    /* Read from serial port */
	memset(Buffer, 0, Size_Buf);  //Buffer=0
	len = read(fd_UART, Buffer, Size_Buf);
	printf("UART Received %d bytes\n", len);
	printf("Received string: %s\n", Buffer);

}

void UART_Write (char arr[])
{
    /* Write to serial port */
	len = strlen(arr);
	len = write(fd_UART, arr, len);
	printf("%d bytes has been sent over UART\n", len);

}

void UART_Close ()
{
    close(fd_UART);
}