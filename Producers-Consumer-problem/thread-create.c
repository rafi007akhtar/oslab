/** Simple program that creates a single thread, then joins it with parent */

#include <stdio.h>
#include <pthread.h> // Contains all pthread-related resources

void *my_threadF(void*); // Function to be called when a new thread is created

int main()
{
    int val;

    pthread_t tid; // unique id of the pthread to be created

    // Declare the attribute required for this pthread
    pthread_attr_t attr;
    // Initialize this attribute with all default values
    pthread_attr_init(&attr);

    // Set the scope of this attribute to system scope (optional)
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    /* Parameters required for creating a pthread, in order:
     * address of unique thread id;
     * address of attributes of this thread (NULL if none);
     * function to be called on thread creation (return type of it should be a void pointer);
     * argument passed to the above function (NULL if none)
     */
    val = pthread_create(&tid, &attr, my_threadF, NULL);
    pthread_join(tid, NULL);
    
    return 0;
}

void *my_threadF(void *arg)
{
    /** This function will be called when the pthread is created */
    printf("This is my thread.\n");

    // Now exit this thread with status NULL
    pthread_exit(NULL); // terminates the calling thread;

}
