#include <stdio.h>
#include <unistd.h> // includes fork(), execvp()
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> // includes wait()

#define MAX_LINE		80 /* 80 chars per line, per command */

char *hints = "\nWelcome to this session, user. Most terminal commands are supported in this shell. \n\nApart from them, this shell supports a few other commands. Enter 'extras' to know what they are. \nYou can see what user you are by entering 'whoami'. \n\nTo view these instructions anytime, press 'hints'. \n\nTo exit anytime, enter 'quit'. \n";

char *extras[] = {{"\n1. <command> & \n Apply '&' at the end of a shell command so that the parent process doesn't wait for the child to terminate and run concurrently with it. \n Eg: ps -ael & \n Warning: This normally results in segmentation fault, hence it is heavily ill-advised to use this command. \n"}, {"\n2. hints \n Shows startup hints on the console. \n"}, {"\n3. quit \n Quits the shell when in user-mode. \n If you are in root mode, you first need to return back to user mode by entering 'exit', and then enter 'quit'. \n"}};

const int extraItems = 3;

//int hCount = 0;
//char *history[10];

typedef enum boolean {false, true} bool;

void printArray(char **params, int l)
{
	int i;
	for (i = 0; i < l; i++) printf("%s", params[i]);
}

int main(void)
{
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */

  bool should_run = true;
  bool waitFlag;
	int i, getVal;

	pid_t pid;
	char temp[80];
	char *words;

	printf("%s", hints);

    while (should_run)
    {
        printf("\nuser> ");
        fflush(stdout);

        waitFlag = true; // By default, wait for a process to finish execution of its child

        // take the string input, and perform some user-defined actions
        gets(temp);
        //history[hCount++] = temp;
        if (!strcmp(temp, "hints")) { printf("%s", hints); continue; }
        if (!strcmp(temp, "quit")) { should_run = false; continue; }
				if (!strcmp(temp, "extras")) { printArray(extras, extraItems); continue; }
        //if (!strcmp(temp, "history")) printf("%s", history[hCount-1]);

				// split the read input in words for the sake of args
        words = strtok(temp, " ");
        i = 0;
        while(words != NULL)
        {
        	if (strcmp(words, "&"))
        		args[i] = words;
        	else { waitFlag = false; break; }
        	i++;
        	words = strtok(NULL, " ");
        }
        args[i] = NULL;

				// 'cd' is not an executable, and hence doesn't work with the exec() family -- so implement it yourself
				if (!strcmp(args[0], "cd"))
				{

					getVal = chdir(args[1]);
					if (getVal == -1)
					{
						printf("Error: No such directory exists.\n");
						continue;
					}
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
        	//printArray(params, j);
        	execvp(args[0], args);
        	return 0;
        }
        else // parent
        {
        	// Wait for child to finish execution unless user ends with '&' (reversing the original part of the problem)
        	if (waitFlag == true)	wait (NULL);
        	else { waitFlag = true; continue; }
        }
    }

	return 0;
}
