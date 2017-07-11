#!/bin/bash 
echo "" >> salida.dat
NUM=1
while [ $NUM -le 42 ]; do
./hanoi $NUM >> salida.dat
NUM=`expr $NUM + 1`
done
