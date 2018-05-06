#! /bin/sh

# Accept a string from the terminal and echo a suitable message if it doesn't have at least ten characters

if [ $# -ne 1 ]
then
    echo "Error; needed exactly 1 string from the command line."
    exit
fi

# SYNTAX: ${#var}
# returns number of characters in var

var=$1
len=${#var} # length of var
if [ $len -lt 10 ]
then
    echo "String $var should contain atleast 10 character; it contains $len"
else
    echo "Correct input"
fi
