#! /bin/sh

# Find the sum of digits of a number given as input

echo "Enter number:"
read num

sum=0
while [ $num -gt 0 ]
do
    rem=`expr $num % 10`
    sum=`expr $sum + $rem`
    num=`expr $num / 10`
done

echo "Sum of digits = $sum"