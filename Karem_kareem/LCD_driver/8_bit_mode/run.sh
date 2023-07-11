#!/bin/bash

###############################################
case $1 in
#############
ins)
make
sudo insmod lcd_driver.ko
sudo chmod 777 /dev/lcd
make clean
;;
#############
rm)
sudo rmmod lcd_driver
make clean
;;
#############
t_w)
sudo rmmod lcd_driver
if [ $? -ne 0 ]
then
 echo "module not inserted yet"
 read -p "press y to continue" yes
fi
make clean
make
if [ $? -ne 0 ]
then
 exit -1
fi
sudo insmod lcd_driver.ko
sudo chmod 777 /dev/lcd
echo -n "Hello My LCD " > /dev/lcd
dmesg
;;
#############
esac
#set +x
###############################################
