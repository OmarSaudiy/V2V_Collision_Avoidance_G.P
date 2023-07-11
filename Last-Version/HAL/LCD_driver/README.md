# Welcome to LCD device driver and interface with rpi3
Follow the following steps for both 8 bit mode or 4 bit mode ...

# 1- LCD Module 
you can run the bash script to :

1- Insert LCD Module
	
	$ ./run.sh ins
2- Remove LCD Module
	
	$ ./run.sh rm
3- Test writing with LCD Module
	
	$ ./run.sh t_w
	
Hint : 
it will display "Hello World!" on LCD 
also you can see kernel messages from Device Driver ---> t_w will display it
	
	$dmesg 
	

# 2- Write on LCD

you can use LCD_vDisplay Function to write on LCD
then compile your code ...

In our simple project for testing ...
$ gcc lcd.c lcd_main.c -o lcd_main.out
$ ./lcd_main.out


