#! /bin/sh

echo "Enter number:"
read num
half=`expr $num / 2`
count=2
while [ $count -le $half ]
do
    if [ `expr $num % $count` -eq 0 ]
    then
        echo "$num is not prime"
        exit
    fi
    count=`expr $count + 1`
done
echo "$num is prime"
