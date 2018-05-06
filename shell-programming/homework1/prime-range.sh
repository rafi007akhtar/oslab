#! /bin/sh

# Print all prime numbers in a given range

# Write a user-defined function for prime number
printPrime()
{
	n=$@ # assign n to the parameter called
	half=`expr $n / 2`
	flag=1
	i=2

	while [ $i -le $half ]
	do
		if [ `expr $n % $i` -eq 0 ]
		then
			flag=0
			break
		fi
		i=`expr $i + 1`
	done

	if [ $flag -eq 1 ]
	then
		echo $n
	fi
	flag=1
}

# Use the above function for performing prime number printing
echo "Enter lower limit:"
read low
echo "Enter upper limit:"
read up

echo "Prime numbers between $low and $up:"

j=$low
while [ $j -le $up ]
do
	printPrime $j
	j=`expr $j + 1`
done