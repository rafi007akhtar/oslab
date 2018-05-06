#! /bin/sh

# Program that shows the names of all the non-directory files in the current directory and calculates the sum of the size of them.

size=0

echo "The non-directory files are:"
for file in *
do
    set -- `ls -l $file`
    if [ ! -d $file ]
    then
        echo $file
        size=`expr $size + $5`
    fi
done

echo "Total size of these files: $size bytes"
