#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "lcd.h"

#define LCD_WIDTH 16
#define LCD_ROWS 2

void lcd_init() {
    lcd_send_command(0x33);
    lcd_send_command(0x32);
    lcd_send_command(0x28);
    lcd_send_command(0x0C);
    lcd_send_command(0x01);
    delayMicroseconds(2000);
}

void lcd_byte(unsigned char bits, unsigned char mode) {
    digitalWrite(LCD_RS, mode);

    digitalWrite(LCD_D4, (bits >> 4) & 1);
    digitalWrite(LCD_D5, (bits >> 5) & 1);
    digitalWrite(LCD_D6, (bits >> 6) & 1);
    digitalWrite(LCD_D7, (bits >> 7) & 1);

    lcd_toggle_enable();

    digitalWrite(LCD_D4, bits & 1);
    digitalWrite(LCD_D5, (bits >> 1) & 1);
    digitalWrite(LCD_D6, (bits >> 2) & 1);
    digitalWrite(LCD_D7, (bits >> 3) & 1);

    lcd_toggle_enable();
}

void lcd_toggle_enable() {
    delayMicroseconds(500);
    digitalWrite(LCD_E, HIGH);
    delayMicroseconds(500);
    digitalWrite(LCD_E, LOW);
    delayMicroseconds(500);
}

void lcd_send_command(unsigned char command) {
    lcd_byte(command, 0);
}

void lcd_send_data(unsigned char data) {
    lcd_byte(data, 1);
}

void lcd_set_cursor(unsigned char col, unsigned char row) {
    unsigned char row_offsets[] = { 0x00, 0x40 };
    lcd_send_command(0x80 | (col + row_offsets[row]));
}

void lcd_write_string(const char* str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}