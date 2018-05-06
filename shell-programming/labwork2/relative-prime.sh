#! /bin/sh

# Find out if two numbers are prime to each other
# Two numbers x and y are said to be relatively prime if gcd(x,y) = 1

echo "Enter two numbers:"
read x
read y

if [ $x -gt $y ]
then
    max=$x
    min=$y
else
    max=$y
    min=$x
fi

rem=`expr $max % $min`
while [ $rem -ne 0 ]
do
    max=$min
    min=$rem
    rem=`expr $max % $min`
done

if [ $min -eq 1 ]
then
    echo "$x, $y are primes to each other"
else
    echo "$x, $y are non-primes to each other"
fi
