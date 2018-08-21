#!/usr/bin/bash


####
## Param $1 = Process name that will be watched
####

####
## get the pid of the process to watch
####
# pid=$(ps | grep $1 | grep 001 | cut -d ' ' -f1)
# echo "pid $pid"
pid=$1
####
# while the process is runing,
# print leaks report
####
while true
do
leaks $pid

if [ $? != "0" ]
then
exit
fi
sleep 2
clear
done
