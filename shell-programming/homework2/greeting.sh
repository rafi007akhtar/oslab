#! /bin/sh

# Display the message “GOOD MORNING” or “GOOD AFTERNOON” or “GOOD EVENING” depending upon the time at which the user logs in

var=`date +%H` # get the hour field from the date

if [ $var -ge 4 -a $var -le 11 ]
then
    echo "GOOD MORNING"
elif [ $var -ge 12 -a $var -le 16 ]
then   
    echo "GOOD AFTERNOON"
else
    echo "GOOD NIGHT"
fi