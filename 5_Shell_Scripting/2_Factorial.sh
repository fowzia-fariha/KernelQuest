#!/bin/bash 
 
echo -n "Enter the value of A: " 
read a 
echo -n "Enter the value of B: " 
read b 
 
# Swapping using a temporary 
variable 
t=$a 
a=$b 
b=$t 
 
echo "Values after swapping:" 
echo "A value is $a" 
echo "B value is $b" 