#ifndef UART_H
#define UART_H

#define UART_DEVICE "/dev/serial0"
#define BAUD_RATE 9600

#define EEBL_FCW      'A'
#define BSW_DNPW      'B'
#define IMA_IR_BEFORE 'C'
#define IMA_IR_AFTER  'D'


int UART_init(const char* device, int baudrate);
void UART_close();
void UART_sendData(const char* data);
void UART_receiveData(char* buffer, int bufferSize);

#endif