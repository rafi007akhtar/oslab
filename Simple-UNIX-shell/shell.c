#include <stdio.h>
#include <unistd.h> // includes fork(), execvp()
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h> // includes wait()
#include <malloc.h>
#include <stdlib.h> // contains atoi(), exit()

#define MAX_LINE		80 /* 80 chars per line, per command */

char *hints = "\nWelcome to this session, user. Most terminal commands are supported in this shell. \n\nApart from them, this shell supports a few other commands. Enter 'extras' to know what they are. \nYou can see what user you are by entering 'whoami'. \n\nTo view these instructions anytime, press 'hints'. \n\nTo exit anytime, enter 'quit'. \n\nⓒ  Md Rafi Akhtar, 2018\n";

char *extras[] = {{"\n1. <command> & \n Apply '&' at the end of a shell command so that the parent process doesn't wait for the child to terminate and run concurrently with it. \n Eg: ps -ael & \n Warning: This normally results in segmentation fault, hence it is heavily ill-advised to use this command. \n"}, {"\n2. hints \n Shows startup hints on the console. \n"}, {"\n3. quit \n Quits the shell when in user-mode. \n If you are in root mode, you first need to return back to user mode by entering 'exit', and then enter 'quit'. \n"}};
const int extraItems = 3;

typedef enum boolean {false, true} bool;

int histItems = 0; // keeps a track of the number of commands executed

void printArray(char **params, int l)
{
	int i;
	for (i = 0; i < l; i++) printf("%s", params[i]);
}

void updateHistory(char *temp)
{
	FILE *f = fopen("history.txt", "a+");
	fprintf(f, "%s\n", temp);
	fclose(f);
}

void printHistory()
{
	char *line = NULL;
    size_t len = 0;
	FILE *f = fopen("history.txt", "a+");
	int i = 0;

	for (i = 0; i < histItems; i++)
	{
		getline(&line, &len, f);
		printf("%d %s", i+1, line);
	}
}

int execute(char *command)
{
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
	char *words;
	bool waitFlag = true;
	int i, getVal;

	// split the read input in words for the sake of args
	words = strtok(command, " ");
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
	if (command[0] == 'c' && command[1] == 'd')
	{
		getVal = chdir(args[1]);
		if (getVal == -1)
			printf("Error: No such directory exists.\n");
		return 1;
	}

	if (!strcmp(command, "hints"))	{ printf("%s", hints); return 1; }
	if (!strcmp(command, "extras")) { printArray(extras, extraItems); return 1; }
	if (!strcmp(command, "history")) { printHistory(); return 1; }
	
	// invoke execvp()
	getVal = execvp(args[0], args);

	if (getVal == -1)
	{
		printf("Sorry, that command is not supported in this shell. \nIf you believe your requested command works in regular UNIX shells, try getting into the root mode by entering:\n sudo -i \nIf the problem still persists, and you are sure there is a bug with this shell, email the author at: alimdrafi@gmail.com\n");
		// TODO: Make sure to NOT add this in your history variable when you create it
	}

	else return 0;

}

void runMostRecent()
{
	char *mostRecentCommand = "";
	char *line = NULL;
    size_t len = 0, count = 0;
	FILE *f = fopen("history.txt", "a+");
	int i = 0, getVal;
	char trimmedCommand[80]; // containts the command devoid of '\n' at the end
	
	for (i = 0; i < histItems; i++)
	{
		getline(&line, &len, f);
		mostRecentCommand = line;
	}
	fclose(f);

	count = strlen(mostRecentCommand) - 1; // to eliminate the '\n' just before the '\0'
	strncpy(trimmedCommand, mostRecentCommand, count);
	getVal = execute(trimmedCommand);
}

int getNth(char *num)
{
	int l = strlen(num);
	int i, j = 0, n;
	char temp[l];
	for (i = 1; i < l; i++)
		temp[j++] = num[i];
	temp[j] = '\0';
	n = atoi(temp); // atoi(str) converts str from string to int
	return n; 
}

void runNth(char *num)
{
	int n = getNth(num);

	if (n > histItems || n < 1)
	{
		printf("Error: Command number %d does not exist\n", n);
		return;
	}
	char *nthCommand = "";
	char *line = NULL;
    size_t len = 0, count = 0;
	int i = 0, getVal;
	char trimmedCommand[80]; // containts the command devoid of '\n' at the end
	
	FILE *f = fopen("history.txt", "a+");
	for (i = 0; i < n; i++)
	{
		getline(&line, &len, f);
		nthCommand = line;
	}
	fclose(f);

	count = strlen(nthCommand) - 1; // to eliminate the '\n' just before the '\0'
	strncpy(trimmedCommand, nthCommand, count);
	getVal = execute(trimmedCommand);
}


int main()
{
	FILE *f; // this file will save history

	bool should_run = true;
	int i, getVal, n;
	bool waitFlag = true;

	pid_t pid;
	char temp[80];
	char *number = "";

	printf("%s", hints);

	// open and close the history file to clear it
	f = fopen("history.txt", "w+");
	fclose(f);

	while (should_run)
	{
		printf("\nuser> ");
		fflush(stdout);

		// take the string input, and perform some user-defined actions
		gets(temp);

		if (!strcmp(temp, "quit"))  { should_run = false; exit(0); }
		if (temp[0] != '!') { updateHistory(temp); histItems++; }
		
		// fork a child process
		pid = fork();

		if (pid < 0) // error
		{
			fprintf(stderr, "System error\n");
			return 1;
		}
		else if (pid == 0) // child process
		{
			if (!strcmp(temp, "!!")) { runMostRecent(); continue; }
			else if (temp[0] == '!' && isdigit(temp[1])) 
			{ 
				runNth(temp);
				continue; 
			}
			else 
			{
				getVal = execute(temp);
			}
			if (getVal == 1) continue;
		}
		else // parent
		{
			// Wait for child to finish execution unless user ends with '&' (reversing the original part of the problem)
			if (waitFlag == true)
				wait (NULL);
			else waitFlag = true;
		}
	}

	return 0;
}
