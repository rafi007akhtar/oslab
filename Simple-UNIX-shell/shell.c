/** Emulate a basic Linux terminal, and some features of your own */

#include <stdio.h>
#include <unistd.h> // includes fork(), execvp()
#include <string.h>
#include <ctype.h> // includes atoi
#include <sys/types.h> // include pid_t
#include <sys/wait.h> // includes wait()
#include <malloc.h>
#include <stdlib.h> // contains atoi(), exit()

#define MAX_LINE		80 /* 80 chars per line, per command */

// Instructions that users see while executing the shell
char *hints = "\nWelcome to this session, user. Most terminal commands are supported in this shell. \n\nApart from them, this shell supports a few other commands. Enter 'extras' to know what they are. \nYou can see what user you are by entering 'whoami'. \n\nTo view these instructions anytime, press 'hints'. \n\nTo exit the current process and move to immediate parent process, enter 'quit'. \nNOTE: Entering 'quit' in the parent process will end this shell process. \n\nTo exit anytime, press Ctrl+C or Ctrl+Z. \n\nⓒ  Md Rafi Akhtar, 2018\n";

// A bunch of extra things that this shell can provide to the user
char *extras[] = {{"\n1. <command> & \n Apply '&' at the end of a shell command so that the parent process doesn't wait for the child to terminate and run concurrently with it. \n Eg: ps -ael & \n Warning: This normally results in segmentation fault, hence it is heavily ill-advised to use this command. \n"}, {"\n2. hints \n Shows startup hints on the console. \n"}, {"\n3. !! \n Run the most recent command. \n"}, {"\n4. !<someInt> \n Run the nth command in history \n Eg., !5 will run the 5th command in history (provided there is one). \n"}, {"\n5. history \n Show the most recent commands in history, with most recent at the bottom \n"}, {"\n6. quit \n Quits the shell when in user-mode. \n If you are in root mode, you first need to return back to user mode by entering 'exit', and then enter 'quit'. \n"}};
const int extraItems = 6; // NOTE: Increment this number as you increase items in extras

typedef enum boolean {false, true} bool;

int histItems = 0; // keeps a track of the number of commands executed

void printArray(char **params, int l)
{
	/** Utility function to print elements of the string array, params, of length l */

	int i;
	for (i = 0; i < l; i++) printf("%s", params[i]);
}

void updateHistory(char *temp)
{
	/** Add commands to the history file as user enters them */

	FILE *f = fopen("history.txt", "a+");
	fprintf(f, "%s\n", temp);
	fclose(f);
}

void printHistory()
{
	/** Print history of commands line by line in the format:
	 * <numberOfOccurence> <command entered>
	 */

	/* NOTE: Changing the question statement here: 
	 * Printing all commands printed in the current session (instead of the 10 most recent)
	 * Printing the commands 'most recent at the bottom' wise, instead of the other way round 
	 */

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
	/** Execute the command entered by the user */

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

	//else return 0;
	if (waitFlag == false) return 2;

	return getVal; // success

}

void runMostRecent()
{
	/** Execute the most recent command in history (by invoking !! from the user) */

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
	/** Fetch nth command in the history by invoking !n from the user, where n is the command number */

	int l = strlen(num);
	int i, j = 0, n;
	char temp[l];

	// Eliminate ! from !n to get the command number, n
	for (i = 1; i < l; i++)
		temp[j++] = num[i];
	temp[j] = '\0';
	n = atoi(temp); // atoi(str) converts str from string to int

	return n; 
}

void runNth(char *num)
{
	/** Execute nth command in the history by invoking !n from the user, where n is the command number */

	int n = getNth(num); // isolate the command number from !commandnumber

	// Check for invalid input number
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
	
	// Open history and fetch the nth command. This will contain a '\n' at the end
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
	int lastPos; // will be required for waiting / not-waiting child process to end

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

		// take the string input, and update history (if it's not invoking a previous command through '!')
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
				getVal = execute(temp);
			if (getVal == 1) continue;
			if (getVal == -1)
				printf("Sorry, that command is not supported in this shell. \nIf you believe your requested command works in regular UNIX shells, try getting into the root mode by entering:\n sudo -i \nIf the problem still persists, and you are sure there is a bug with this shell, email the author at: alimdrafi@gmail.com\n");
		}
		else // parent
		{
			// Wait for child to finish execution unless user ends with '&' (reversing the original part of the problem)
			lastPos = strlen(temp) - 1;
			if (temp[lastPos] != '&') wait(NULL);
		}
	}

	return 0;
}
