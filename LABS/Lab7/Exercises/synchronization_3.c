// Mutex example

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter;
// pthread_mutex_t lock;

void* increase_counter(void* arg)
{
	// pthread_mutex_lock(&lock);

	printf("\n Job %d has started\n", counter);

  counter += 1;

	sleep(10);

	printf("\n Job %d has finished\n", counter);

	// pthread_mutex_unlock(&lock);

  pthread_exit(NULL);
}

int main(void)
{
	int i = 0;
	int create_result;

  pthread_t tid[2];

  /*
	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("\n mutex init has failed\n");
		return 1;
	}*/

  counter = 0;

	while (i < 2) {

    create_result = pthread_create(&(tid[i]), NULL, increase_counter, NULL);

    if (create_result != 0)
			printf("\nThread can't be created !");

		i++;
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	// pthread_mutex_destroy(&lock);

	pthread_exit(NULL);
}
