#ifndef LCD_H
#define LCD_H

#define LCD_RS  9  // GPIO 27 for RS pin
#define LCD_E   11  // GPIO 22 for E pin
#define LCD_D4  17  // GPIO 25 for D4 pin
#define LCD_D5  27  // GPIO 24 for D5 pin
#define LCD_D6  22  // GPIO 23 for D6 pin
#define LCD_D7  10  // GPIO 18 for D7 pin

void lcd_init();
void lcd_byte(unsigned char bits, unsigned char mode);
void lcd_toggle_enable();
void lcd_send_command(unsigned char command);
void lcd_send_data(unsigned char data);
void lcd_set_cursor(unsigned char col, unsigned char row);
void lcd_write_string(const char* str);


#endif 