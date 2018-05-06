#! /bin/sh

echo "Enter number:"
read num

i=1
p=1
while [ $i -le $num ]
do
    p=`expr $p \* $i`
    i=`expr $i + 1`
done

echo "$num! = $p"
