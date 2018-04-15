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
	for (i = 0; i < 5; i++)
		pthread_create(&tid[i], NULL, printThreadNumber, &i);
	
	for (i = 0; i < 5; i++)
		pthread_join(tid[i], NULL);
	
	return 0;
}

void *printThreadNumber(void *arg)
{
	int *t = (int *)arg;
	int numberT = *t; // thread number

	printf("Thread number: %d\n", numberT); 

	/* Output might print the same value of i more than once because a thread may view the value of i after i has been incremented since its creation.
	 * RACE CONDITION: When one thread tries to read a resource while another is modifying it
	 */

	return NULL;
}
