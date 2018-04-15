/** Implement the producer-consumer problem where:
 * One thread ("producer") tries to add values to a list ("produce")
 * Another thread ("consumer") tries to print all the values from the list and then delete them ("consume")
 * making sure they don't cross paths
 */

#include <stdio.h>
#include <pthread.h>

int buffer[10]; // shared buffer queue for all threads

int add = 0; // position in the buffer where next elemenet is to be added (FIFO order)
int rem = 0; // position in the buffer where the next element needs to be removed (FIFO order)
int num = 0; // number of elements present in the buffer

pthread_mutex_t bufferM = PTHREAD_MUTEX_INITIALIZER; // mutex for buffer
pthread_cond_t prodC = PTHREAD_COND_INITIALIZER; // condition variable for producers
pthread_cond_t consC = PTHREAD_COND_INITIALIZER; // condition variable for consumers

void *produce (void *); // producer will perform its actions in this function
void *consume (void *); // consumer will perform its actions in this function

int main()
{
    pthread_t tProducer, tConsumer;
    int result;

	result = pthread_create(&tProducer, NULL, produce, NULL);
	if (result) fprintf(stderr, "Unable to produce\n");

	result = pthread_create(&tConsumer, NULL, consume, NULL);
	if (result) fprintf(stderr, "Unable to consume\n");

	pthread_join(tProducer, NULL);
	pthread_join(tConsumer, NULL);
    
    return 0;
}

void *produce(void *arg)
{
	int i; 

	for (i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&bufferM);
			if (num == 10) 
			{
				// Buffer is full -- time for consumption!
				pthread_cond_signal(&consC);
			}
			else 
			{
				// Add value to buffer and update the next add position
				buffer[add] = i; 
				add = (add + 1) % 10;

				num++; // Update number of elements stored in the buffer
				printf("Producers> Value added: %d\n", i);
			}
		pthread_mutex_unlock(&bufferM);
	}

	return NULL;
}

void *consume(void *arg)
{
	pthread_mutex_lock(&bufferM);
		while (num != 10) pthread_cond_wait(&prodC, &bufferM);
		while (num > 0)
		{
			int temp = buffer[rem];
			buffer[rem] = -1;
			rem = (rem + 1) % 10;
			printf("Consumers> Value removed: %d\n", temp);
			num--;
		}
	pthread_mutex_unlock(&bufferM);

	return NULL;
}
