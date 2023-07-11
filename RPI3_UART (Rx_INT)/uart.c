#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define UART_DEVICE "/dev/ttyS0"
#define BAUD_RATE B9600

int uart_fd;

// Signal handler for SIGIO
void handle_sigio(int sig) {
    char buffer[256];
    int bytes_read = read(uart_fd, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate the received string
        printf("Received: %s\n", buffer);
    }
}

// Function to send a string over UART
void send_string(const char* data) {
    write(uart_fd, data, strlen(data));
    usleep(100);  // Wait for transmission to complete
}

int main() {
    struct termios options;
    struct sigaction saio;

    // Open the UART device
    uart_fd = open(UART_DEVICE, O_RDWR | O_NOCTTY);
    if (uart_fd == -1) {
        perror("Error opening UART device");
        return -1;
    }

    // Get the current UART configuration
    tcgetattr(uart_fd, &options);

    // Set the baud rate
    cfsetispeed(&options, BAUD_RATE);
    cfsetospeed(&options, BAUD_RATE);

    // Set the UART to raw mode
    cfmakeraw(&options);

    // Apply the UART configuration
    tcsetattr(uart_fd, TCSANOW, &options);

    // Set the UART file descriptor to enable asynchronous I/O
    fcntl(uart_fd, F_SETFL, FASYNC);

    // Register signal handler for SIGIO
    saio.sa_handler = handle_sigio;
    sigemptyset(&saio.sa_mask);
    saio.sa_flags = 0;
    saio.sa_restorer = NULL;
    sigaction(SIGIO, &saio, NULL);

    // Enable generation of SIGIO signals
    fcntl(uart_fd, F_SETOWN, getpid());
    fcntl(uart_fd, F_SETFL, FASYNC | O_ASYNC);

    // Example usage
    char send_data[] = "Hello, Arduino!";
    send_string(send_data);

    // Keep the program running
    while (1) {
        sleep(1);
    }

    // Close the UART device
    close(uart_fd);

    return 0;
}

