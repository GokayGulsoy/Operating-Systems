#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void* print_hello_world(void* arg) {
	printf("\nHello world!\n");
	printf("My thread id: %lu\n", pthread_self());

	int arg0 = *((int*)arg);
	int* retval = (int*) malloc(sizeof(int));
	*retval = arg0 * arg0;
	return (void*) retval; // pthread_exit((void*) retval);
}

int main() {
	int pthread_retcode;

	int arg0 = 15;
	pthread_t id;
	if((pthread_retcode = pthread_create(&id, NULL, print_hello_world, &arg0)) != 0) {
		fprintf(stderr, "Error while creating a thread:	%s\n", strerror(pthread_retcode));
		exit(EXIT_FAILURE);
	}
	printf("This is the newly created thread's id: %lu\n", id);

	int* thread_retval;
	if((pthread_retcode = pthread_join(id, (void**)&thread_retval)) != 0) {
		fprintf(stderr, "Error while joining the thread	with id %lu: %s\n", id, strerror(pthread_retcode));
		exit(EXIT_FAILURE);
	}

	printf("\nReturn val: %d\n", *thread_retval);
	free(thread_retval);

	return 0;
}
