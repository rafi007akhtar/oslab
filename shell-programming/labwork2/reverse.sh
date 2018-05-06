#! /bin/sh

# Print the reverse of a number from the user

echo "Enter number:"
read num

rev=0
while [ $num -gt 0 ]
do
    rem=`expr $num % 10`
    rev=`expr $rev \* 10 + $rem`
    num=`expr $num / 10`
done

echo "Reverse: $rev"
