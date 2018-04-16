/** What this program does:
 * Create 5 threads;
 * Print all their thread numbers;
 * Join them as they die.
 * The output will show race condition.
 */

#include <stdio.h>
#include <pthread.h>

void *printThreadNumber(void*);

int main()
{
    pthread_t tid[5]; // Assuming normal attr behaviour for each of them

	int i; // globally shared resource with all the threads
    int cache[5]; // Privately store thread number for each thread so it's not visible to other threads

	for (i = 0; i < 5; i++)
    {
        cache[i] = i;
		pthread_create(&tid[i], NULL, printThreadNumber, &cache[i]);
    }
	
	for (i = 0; i < 5; i++)
		pthread_join(tid[i], NULL);
	
	return 0;
}

void *printThreadNumber(void *arg)
{
	int *t = (int *)arg;
	int numberT = *t; // thread number

	printf("Thread number: %d\n", numberT); 

    /* RACE CONDITION RESOLVED: As numberT is referring to cache[i] instead of i, where cache[i] is private to each thread */

	return NULL;
}
