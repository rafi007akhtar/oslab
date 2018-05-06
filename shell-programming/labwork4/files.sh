#! /bin/sh

# PROBLEM STATEMENT
# Write a shell script, which reports names and sizes of all files in a directory (directory should be supplied as an argument to the shell script) whose size exceeds 100 bytes. 
# The filenames should be printed in decreasing order of their sizes. 
# The total number of such files should also be reported.

if [ $# -ne 1 ]
then
    echo "Enter a directory name"
    exit
fi

cd $1
file_count=0

echo "File name \t \t File size (bytes)"
echo "--------- \t \t -----------------"
for file in *
do
    set -- `ls -l -S $file`
    if [ $5 -gt 100 ]
    then    
        echo "$file \t \t $5"
        file_count=`expr $file_count + 1`
    fi
done
echo "total $file_count"
