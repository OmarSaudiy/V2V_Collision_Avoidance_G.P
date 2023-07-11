#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"

char buffer[]="Karem and Karim";

int main()
{
	LCD_vDisplay(buffer);
	return 0;
}