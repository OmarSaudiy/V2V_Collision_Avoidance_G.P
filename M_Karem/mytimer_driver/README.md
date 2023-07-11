# Welcome to My Timer device driver with rpi3-b+

 MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mahmoud Karem Zamel");
MODULE_DESCRIPTION("A simple test for Multi-timers");


# 1- About

This is a Multi-Tasking device driver based on kernel Timer ..
This Application has 4 tasks :
1- Toggle led every one second (GPIO 5).
2- Toggle led every two seconds (GPIO 6).
3- Toggle led every three seconds (GPIO 13).
4- Toggle led every four seconds (GPIO 19).



# 2- Running

  
## 1) you can follow steps to insert this Dynamic module ...

1- make 
	
	make

2- Insert The Module
	
	sudo insmod mytimer_leds.ko

## 2) you can follow steps to remove this Dynamic module ...

1- Remove The Module
	
	sudo rmmod mytimer_leds

2- clean all
	
	make clean
	
## 3) also you can see kernel messages from Device Drive

	
	$dmesg

  
# 3- Easily you can use this script

## 1) Insert this Dynamic module ...

	
	./run.sh ins
	
## 2) Remove this Dynamic module ...

	
	./run.sh rm
	
## 3) Test this Dynamic module ...

	
	./run.sh test
