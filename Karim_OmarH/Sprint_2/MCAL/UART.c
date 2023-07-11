#include <wiringSerial.h>
#include <wiringPi.h>
#include "UART.h"

int uart_fd;

int UART_init(const char* device, int baudrate) {
    uart_fd = serialOpen(device, baudrate);
    if (uart_fd < 0) {
        return 0;
    }

    if (wiringPiSetup() == -1) {
        return 0;
    }

    return 1;
}

void UART_close() {
    serialClose(uart_fd);
}

void UART_sendData(const char* data) {
    serialPrintf(uart_fd, "%s\n", data);
}

void UART_receiveData(char* buffer, int bufferSize) {
    int index = 0;
    char c;

    do {
        c = serialGetchar(uart_fd);
        if (c == '\n') {
            buffer[index] = '\0';
            break;
        }
        buffer[index++] = c;
    } while (index < bufferSize - 1);
}