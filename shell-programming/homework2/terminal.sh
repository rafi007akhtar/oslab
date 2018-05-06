#! /bin/sh

# Program that receives either the LOGNAME or the UID supplied at the command prompt and finds out at how many terminals this user has logged in

if [ $# -eq 0 ]
then
    echo "Enter login name"
elif [ $1 = $LOGNAME ]
then
    ter=`ls /dev/pts | wc -w`
    echo "Number of terminals = $ter"
else
    echo "Invalid username entered"
fi