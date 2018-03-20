#include <stdio.h>
#include <unistd.h> // includes fork(), execvp()
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE		80 /* 80 chars per line, per command */

char *hints = "\nWelcome to Guest session. Most terminal commands are supported in this shell. \n\nNote that you cannot change directories with the guest session in this shell, meaning the command 'cd <dest>' is not supported so long as you are a guest user. \nIn order to be able to change directories and much more, change into root user by entering 'sudo -i'. \nYou can shift back to guest session by typing 'exit' when root. \nYou can see what user you are by entering 'whoami'. \n\nTo view these instructions anytime, press 'hints'. \n\nTo exit anytime, press 'quit'. \n";

//int hCount = 0;
//char *history[10];

typedef enum boolean {false, true} bool;

void printArray(char **params, int l)
{
	int i;
	for (i = 0; i < l; i++) printf("%s\n", params[i]);
}

int main(void)
{
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
	char *params[39]; // parameters
	
    bool should_run = true;
    bool waitFlag;
	int i, j;
	
	pid_t pid;
	char temp[80];
	char *words;
	
	printf("%s", hints);
		
    while (should_run)
    {   
        printf("\nguest> ");
        fflush(stdout);
        
        waitFlag = true; // By default, wait for a process to finish execution of its child
        
        // take the string input, and split the arguments into words
        gets(temp);
        //history[hCount++] = temp;
        if (!strcmp(temp, "hints")) printf("%s", hints);
        if (!strcmp(temp, "quit")) should_run = false;
        //if (!strcmp(temp, "history")) printf("%s", history[hCount-1]);

        words = strtok(temp, " ");
        i = j = 0;
        while(words != NULL)
        {
        	if (strcmp(words, "&"))
        		args[i] = words;
        	else { waitFlag = false; break; }
        	i++;
        	words = strtok(NULL, " ");
        }
        args[i] = NULL;
        
        //printArray(params, j); // Testing for the printing of correct paramters
        
        //printf("%s %s", args[0], args[1]); // Testing for valid outputs
        
        // fork a child process
        pid = fork();
        
        if (pid < 0) // error
        {
        	fprintf(stderr, "System error\n");
        	return 1;
        }
        else if (pid == 0) // child process
        {
        	// invoke execvp()
        	//printArray(params, j);
        	execvp(args[0], args);
        	return 0;
        }
        else // parent
        {
        	// Wait for child to finish execution unless user ends with '&' (reversing the original part of the problem)
        	if (waitFlag == true)	wait (NULL);
        	else waitFlag = true;
        }
    }
    
	return 0;
}

