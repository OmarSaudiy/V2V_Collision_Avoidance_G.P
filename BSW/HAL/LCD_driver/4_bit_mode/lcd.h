#ifndef LCD_H_
#define LCD_H_

#define LCD_PATH "/dev/lcd"

enum {
	LCD_BUSY = 0,
	LCD_IDLE
}LCD_State_ID;


void LCD_vDisplay(char str[]);

#endif


