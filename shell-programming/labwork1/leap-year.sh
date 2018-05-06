#! /bin/sh

if [ $# -eq 0 ] # no i/ps from command line
then
    set `date` # set the date string as command line arguments
    year=$6 # use the current year (which is the 6th string of `date`)
else
    year=$1 # use the year given from command line
fi
if [ `expr $year % 4` -eq 0 -a `expr $year % 100` -ne 0 -o `expr $year % 400` -eq 0 ]
then
    echo "$year is a leap year"
else
    echo "$year is not a leap year"
fi