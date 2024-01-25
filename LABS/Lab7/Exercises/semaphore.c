#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define SEAT_SIZE 4
#define STUDENT_COUNT 100

#define EMPTY 0
#define FULL 1

sem_t update;
sem_t isfull;

int seats[SEAT_SIZE];
int emptyCount = SEAT_SIZE;
int entered;
int exited;


//finds an empty place to sit among all available seats
int findSeat()
{
	int i;
	for (i = 0; i<SEAT_SIZE; i++)
	{
		if (seats[i] == EMPTY)
		{
			seats[i] = FULL;			
			return i;
		}
	}

	//it is full
	return -1;
}


//empties the seat
void leave(int seatno)
{
	seats[seatno]=EMPTY;

	return;
}



void* student(void* arg)
{
	int sleeping_time,seat_no;

	int studentID = *((int *)arg);
	sleeping_time = rand() % 3 + 2;


	//class
	sem_wait(&isfull);

		//variable update
		sem_wait(&update);
		seat_no = findSeat();
		printf("Student-%d is sitting at Seat-%d\n", studentID, seat_no);
		entered++;
		sem_post(&update);
		
		sleep(sleeping_time);


		//variable update
		sem_wait(&update);
		leave(seat_no);
		printf("Student-%d has left the Seat-%d\n", studentID, seat_no);
		exited++;
		sem_post(&update);

	sem_post(&isfull);

	return NULL;
}



int main()
{
	int i;
	pthread_t tid[STUDENT_COUNT];
	
	srand(time(NULL));

	entered = 0;
	exited = 0;

	//build the class
	for (i = 0; i<SEAT_SIZE; i++)
	{
		seats[i] = EMPTY;
	}


	//initialize the semaphores
	if(sem_init(&isfull, 0, SEAT_SIZE) != 0)
	{
		printf("ERROR: cannot create semaphore\n");
		return -1;
	}
	if(sem_init(&update, 0, 1) != 0)
	{
		printf("ERROR: cannot create semaphore\n");
		return -1;
	}




	//create students
	for (i = 0; i<STUDENT_COUNT; i++)
	{
		void *memory = malloc(sizeof(int));
		int* p = (int *)memory;
		*p = i+1;
		pthread_create(&tid[i], NULL, student, p);
	}


	//wait for all studetns to leave
	for (i = 0; i<STUDENT_COUNT; i++)
	{
		pthread_join(tid[i], NULL);
	}


	printf("*******\n%d\tstudents entered the class\n", entered);
	printf("*******\n%d\tstudents left\n", exited);

	
	//destroy the semaphores
	sem_destroy(&isfull);
	sem_destroy(&update);

	
	return 0;
}



