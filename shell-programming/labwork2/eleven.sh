#! /bin/sh

# Check if a number is divisible by 11

echo "Enter number:"
read n
if [ `expr $n % 11` -eq 0 ]
then
    echo "$n divisible by 11"
else
    echo "$n not divisible by 11"
fi
