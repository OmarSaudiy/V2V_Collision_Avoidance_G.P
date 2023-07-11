#ifndef UART_H_
#define UART_H_



void UART_Open_Init ();

void UART_Read (char Buffer[] , int Size_Buf);

void UART_Write (char arr[]);

void UART_Close();


/*  Needed #include */
//#include <stdio.h>
//#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <termios.h>


#endif