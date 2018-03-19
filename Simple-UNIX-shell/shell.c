#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LINE		80 /* 80 chars per line, per command */

char *hints = "\nWelcome to Guest session. Non-paramter commands are suppported in this basic shell (eg., ls, ps, pwd, whoami, gedit, vi, and so on). \nNote that commands that require one or more parameters are unsupported for now (like cd, mkdir, and so on). \nTo view these instructions anytime, press 'hints'. \nTo exit anytime, press 'quit'. \n";

int hCount = 0;
char *history[10];

void printArray(char **params, int l)
{
	int i;
	for (i = 0; i < l; i++) printf("%s\n", params[i]);
}

int main(void)
{
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
	char *params[39]; // parameters
	
    int should_run = 1;
	int i, j;
	
	pid_t pid;
	char temp[80];
	char *words;
	
	printf(hints);
		
    while (should_run){   
        printf("\nguest> ");
        fflush(stdout);
        
        // take the string input, and split the arguments into words
        gets(temp);
        history[hCount++] = temp;
        if (!strcmp(temp, "hints")) printf(hints);
        if (!strcmp(temp, "quit")) should_run = 0;
        if (!strcmp(temp, "history")) printf("%s", history[hCount-1]);

        words = strtok(temp, " ");
        i = j = 0;
        while(words != NULL)
        {
        	args[i] = words;
        	if (i != 0) { params[j] = args[i]; j++; }
        	i++;
        	words = strtok(NULL, " ");
        }
        
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
        	execvp(args[0], params);
        }
        else // parent
        {
        	/* REVERSNG THE QUESTION
        	 * Default behaviour: Parent waits for child to end before continuing
        	 * When user enters '&': Parent and child run concurrently 
        	 */
        	if (strcmp(params[j-1], "&"))
        	wait(NULL); 
        }
    }
    
	return 0;
}
