#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"

void LCD_vDisplay(char str[])
{
	FILE *fptr;
	fptr=fopen( LCD_PATH , "w" );
	fprintf( fptr , "%s" , str );
	fclose(fptr);
}
