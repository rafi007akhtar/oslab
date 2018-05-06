#! /bin/sh

# Print last twenty commands issued by the user. The user name is supplied as a command line argument to the script (use bash-history file).

if [ $# -ne 1 ]
then
    echo "Enter your login name in the command line"
    exit
elif [ $1 = $LOGNAME ]
then
    # navigate to the root directory, open the .bash_history file, and print the last 20 commands
    $HOME/.bash_history | tail -20
else
    echo "Invalid login name entered"
fi