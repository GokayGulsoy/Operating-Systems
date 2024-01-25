#include "pthread.h" /*Importing the thread library */
#include "stdio.h"
#include "unistd.h" /*Importing POSIX Operating System API library*/
#include "string.h"

#define MEMBAR __sync_synchronize() /* memory barrier instruction enforcing the order */
#define THREAD_COUNT 12

volatile int tickets[THREAD_COUNT]; /*volatile prevents the compiler from applying any optimizations, read all time from RAM instead of CPU registers*/
volatile int selecting[THREAD_COUNT];

volatile int resource;

void lock_init()
{
    memset((void *)tickets, 0, sizeof(tickets));
    memset((void *)selecting, 0, sizeof(selecting));
    resource = 0;
}

void lock_thread(int thread)
{
    // Give ticket
    // Before getting the ticket number
    //"selecting" variable is set  true
    selecting[thread] = 1;
    MEMBAR;
    // give ticket
    int max_num = 0;
    // Finding Maximum ticket value among current threads
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        int ticket = tickets[i];
        max_num = ticket > max_num ? ticket : max_num;
    }
    // Allotting new ticket value as maximum+ 1
    tickets[thread] = max_num + 1;
    MEMBAR;

    selecting[thread] = 0;
    MEMBAR;
    //ENTRY Section starts
    for (int other = 0; other < THREAD_COUNT; ++other)
    {
        // Applying conditions
        while (selecting[other]) // has the thread given a ticket number?
        {
        }
        MEMBAR;
        while (tickets[other] != 0 && (tickets[other] < tickets[thread] || (tickets[other] == tickets[thread] && other < thread)))
        {
        }
    }
}
// EXIT Section
void unlock_thread(int thread)
{
    MEMBAR;
    tickets[thread] = 0;
}
// CRITICAL Section
void use_resource(int thread)
{
    if (resource != 0)
    {
        printf("The Resource was acquired by %d, but is still in-use by %d!\n", thread, resource);
    }

    resource = thread;
    printf("%d is using resource...\n", thread);
    printf("Ticket number %d!\n", tickets[thread]);

    MEMBAR;
        
    sleep(2);
    resource = 0;
}

//Simplified function to show the implementation
void *thread_body(void *arg)
{
    long thread = (long)arg;
    lock_thread(thread);
    use_resource(thread);
    unlock_thread(thread);
    return NULL;
}

int main(int argc, char **argv)
{

    lock_init();

    // Declaring the thread variables
    pthread_t threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        // Creating a new thread with the function
        //"thread_body" as its thread routine
        pthread_create(&threads[i], NULL, &thread_body, (void *)((long)i));
    }
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        // Reaping the resources used by
        // all threads once their task is completed.
        pthread_join(threads[i], NULL);
    }
    return 0;
}