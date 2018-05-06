#! /bin/sh

# PROBLEM STATEMENT
# Write a shell script that lists files by modification time when called with lm and by access time when called with la. 
# By default, the script should show the listing of all files in the current directory.

case $1 in
    lm) ls -lt;; # display files as per last modification time
    la) ls -lut;; # display files as per last access time
    *) ls -a;; # show all files by default
esac
