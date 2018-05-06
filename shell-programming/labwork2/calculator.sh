#! /bin/sh

if [ $# -ne 3 ]
then
    echo "Error: 3 inputs required from the command line -- two integers, and one operator (+, -, /, x)"
    exit
fi

num1=$1 # operand 1
num2=$2 # operand 2
op=$3 # operator

case $op in
    +) result=`expr $num1 + $num2`;;
    -) result=`expr $num1 - $num2`;;
    x) result=`expr $num1 \* $num2`;;
    /) result=`expr $num1 / $num2`;;
esac

echo "$num1 $op $num2 = $result"
