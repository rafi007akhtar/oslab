#! /bin/sh

if [ $# -ne 3 ] # $# = number of command line arguments
then
    echo "Error: needed exactly 3 inputs from command line; got $#"
    exit
fi
max=$1 # first command line i/p
if [ $2 -gt $max ] # check w/ second i/p
then 
    max=$2
fi
if [ $3 -gt $max ] # check w/ 3rd i/p
then 
    max=$3
fi
echo "max = $max"