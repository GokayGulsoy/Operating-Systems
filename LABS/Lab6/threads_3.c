#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *worker(void *data) { 
    printf("Current Thread ID: %lu\n", pthread_self());
    //sleep(1);

    pthread_exit(NULL);   
}

int main(void) {
    pthread_t th1, th2;
    pthread_create(&th1, NULL, worker, NULL);
    //sleep(1);
    pthread_create(&th2, NULL, worker, NULL);

    //sleep(3);
    printf("Thread 1 ID: %lu\n", th1);
    printf("Thread 2 ID: %lu\n", th2);

    printf("Exiting from main program\n");

    // return 0;
    pthread_exit(NULL);
}
