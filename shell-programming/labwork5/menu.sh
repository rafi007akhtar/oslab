#! /bin/sh

# PROBLEM STATEMENT
# Devise a menu-driven shell program that accepts values from 1 to 4 and performs action depending upon
# the number keyed in:
    # 1. List of users currently logged in
    # 2. Present date
    # 3. Present working directory
    # 4. Quit

loop=1
while [ $loop -eq 1 ]
do
    echo "Enter a number from 1 to 4:"
    read num

    case $num in
        1) who;;
        2) date;;
        3) pwd;;
        4) exit;;
        *) echo "Wrong choice"
    esac
done
