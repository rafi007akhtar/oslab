#! /bin/sh

# PROBLEM STATEMENT
# Write a shell script which receives two filenames as arguments and checks whether the two file's contents are same or not. 
# If they are same then the second file should be deleted.

if [ $# -ne 2 ]
then
    echo "Error; two filenames required in command line"
    exit
fi

cmp $1 $2
# check for exit status of this command via $?
if [ $? -eq 0 ] # i/ps are same if exit status of cmp = 0
then
    echo "Files are the same"
    rm $2 # remove second file
else 
    echo "Files are different"
fi
