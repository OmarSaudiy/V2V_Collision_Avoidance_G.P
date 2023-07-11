/*
 *  LCD_main.c
 *  Created: 1/3/2023 6:20:45 PM
 *  Author: Azza Saeed
 */ 


#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"
void LCD_vDisplay();
int main()
{
	void LCD_vDisplay();
	return 0;
}

void LCD_vDisplay()
{
	char str[100]={};
	FILE *fptr;
	fptr=fopen( PATH , "w" );
	if(fptr==NULL)
	{
		printf("Pointer fptr equal Null...!");
		return;
	}
	
	scanf("%100[a-zA-Z ]",&str);
	
	fprintf( fptr , "%s" , str );
	fclose(fptr);
}