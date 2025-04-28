#!/bin/bash

#    Author: Michele Grisafi
#    Email: michele.grisafi@unitn.it
#    License: MIT 

INPUT=executionTimes.csv
OLDIFS=$IFS
IFS=','

#Create directory for results
mkdir -p results results/figures

[ ! -f $INPUT ] && echo "$INPUT file not found. It must contain execution times for each app to be tested (app,pistisTime,nativeTime)" && exit 99; 
echo "Start processing..."

#Cycle through the entries in the csv file
while read app pistis native flash nativeMod
do
    printf "%s\n" $app
    #Create results for both PISTIS and native execution times
    java Battery results/${app}.PisMod.csv $pistis
    java Battery results/${app}.PisNat.csv $native 
    java Battery results/${app}.FlaMod.csv $flash 
    java Battery results/${app}.FlaNat.csv $nativeMod 
done < $INPUT
IFS=$OLDIFS

