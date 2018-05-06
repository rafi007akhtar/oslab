#! /bin/sh

# Display the files created or updated within fourteen days from the current date.

find -atime 14 -mtime 14 
# -atime n -> file was accessed n days ago
# -mtime n -> file was modified n days ago
