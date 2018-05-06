#! /bin/sh

# Display list of files in current directory to which owner have read, write and execute permission

echo "The files with read, write, execute permissions are:"
for file in *
do
    if [ -r $file -a -w $file -a -x $file ]
    then
        ls $file
    fi
done

