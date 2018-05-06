#! /bin/sh

# Display all files with all attributes those have been created or modified in the month of November.

for file in *
do 
    set -- `ls -l $file`
    if [ $6 = "Nov" ]
    then
        ls -l $file
    fi
done

