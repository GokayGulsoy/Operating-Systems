#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <time.h>

#define NUM_PROD 5
#define NUM_CONS 5

int arr[10];
int index_consumer=0;
int index_producer=0;
int count=0;

// Initialize conditional variables and mutex
pthread_mutex_t mutex;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;


// Thread Job for filling array 
void *fill() 
{
	int value=0;


	pthread_mutex_lock(&mutex);
	while(count==10)
	{
		printf("waiting for consumers\n");
		pthread_cond_wait(&empty, &mutex);
	}

	value = rand()%100;
	printf("producer created the number: %d\n", value);
	arr[index_producer] = value;
	index_producer++;
	index_producer %= 10;
	count++;

	pthread_cond_signal(&full);
	pthread_mutex_unlock(&mutex);


	pthread_exit(NULL);
}

// Thread job for reading array
void *read() 
{

	pthread_mutex_lock(&mutex);
	while(count==0)
	{
		printf("waiting for producers\n");
		pthread_cond_wait(&full, &mutex);
	}


	printf("Value read: %d\n",arr[index_consumer]);
	arr[index_consumer]=0;
	index_consumer++;
	index_consumer %= 10;
	count--;
	
	pthread_cond_signal(&empty);
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}



int main() {
	int i;
	pthread_t thread_id_cons[NUM_CONS],thread_id_prod[NUM_PROD];


	// Create 2 threads for filling and reading array
	for(i=0;i<NUM_CONS;i++)
		pthread_create(&thread_id_cons[i],NULL,&read,NULL);

	for(i=0;i<NUM_PROD;i++)
		pthread_create(&thread_id_prod[i],NULL,&fill,NULL);


	// Join threads
	for(i=0;i<NUM_PROD;i++)
		pthread_join(thread_id_prod[i],NULL);
	for(i=0;i<NUM_CONS;i++)
		pthread_join(thread_id_cons[i],NULL);
	
	return 0;
}




