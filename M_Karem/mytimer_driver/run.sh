#!/bin/bash
#set -x

###############################################
case $1 in
#############
ins)
make
sudo insmod mytimer_leds.ko
make clean
;;
#############
rm)
sudo rmmod mytimer_leds
make clean
;;
#############
test)
sudo rmmod mytimer_leds
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
sudo insmod mytimer_leds.ko
dmesg
;;
#############
esac
#set +x
###############################################
