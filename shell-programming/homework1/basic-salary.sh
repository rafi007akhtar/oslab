#! /bin/sh

# PROBLEM STATEMENT
# Rajesh's basic salary (BASIC) is input through the keyboard. 
# His dearness allowance (DA) is 52% of BASIC. 
# House rent allowance (HRA) is 15% of BASIC. 
# Contributory provident fund is 12% of (BASIC + DA). 
# Write a shell script to calculate his gross salary and take home salary using the following formulae:
# Gross salary = BASIC + DA + HRA
# Take home salary = Gross salary - (BASIC + DA) * 0.12

echo "Enter basic salary:"
read basic

da=`expr $basic \* 52 / 100`
hra=`expr $basic \* 15 / 100`
fund=`expr $basic + $da \* 12 / 100`

gross=`expr $basic + $da + $hra`
net=`expr $gross - $fund`

echo "Gross salary: $gross"
echo "Take-home salary: $net"
