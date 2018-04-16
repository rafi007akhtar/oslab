/** Using two threads, this program prints the string "ping" and "pong" to the console, at random distances, at the interval of 1 s */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *printWord(void *);
void printRandomLines();

int main()
{
    pthread_t pingT, pongT;
    int outcome;
	void *word1 = (void *)("ping");
	void *word2 = (void *)("pong");

    while (1)
    {
		// DO PING
        outcome = pthread_create(&pingT, NULL, printWord, word1);
		if (outcome) fprintf(stderr, "Error: Unable to ping \n"); // perform error checking
		else pthread_join(pingT, NULL);
		sleep(1);

		printRandomLines();

		// DO PONG
		outcome = pthread_create(&pongT, NULL, printWord, word2);
		if (outcome) fprintf(stderr, "Error: Unable to pong \n"); // perform error checking
		else pthread_join(pongT, NULL);
		sleep(1);

		printRandomLines();
    }

    return 0;
}

void *printWord(void *arg)
{
    char *word = (char *)arg;
    printf("%s\n", word);
    return NULL;
}

void printRandomLines()
{
	/** Generate a random number between 1 and 5, and print those many lines */
	int r = (rand() % 4) + 1;
	int i;
	for (i = 0; i < r; i++) printf("\n");
}
