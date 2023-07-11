#! /bin/bash

sudo rmmod hcsr04_sensor

make clean

make 
sudo insmod hcsr04_sensor.ko

sudo chmod 777 /dev/hcsr04
