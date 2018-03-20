/*
 * Lab 4 - Thread Scheduling
 * Programmer: Jordan Long
 * Instructor: S. Lee
 * Course: SMPE 320
 * Section 1
 */


#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


sem_t timer;
sem_t ready;

pthread_t tid;
pthread_attr_t attr;


/*
 * Main method for the thread scheduling program.
 */
int main(int argc, char **argv)
{


	sem_init(&ready, 0, 0);
	sem_init(&timer, 0, 1);


	/*
	 * If integer is not included when the program is run, throws error
	 * ./a.out 5 5 2
	 */
	if(argc!=3)
	{
		fprintf(stderr,"Arguments for threads and time quantum must be included.\n");
		return -1;
	}

	int threads = atoi(argv[1]);
	int timeQ = atoi(argv[2]);
	int burstTime[threads];

	/*
	 * Prints out requests for burst times of each thread, and stores value in array. Padded +1 to be more readable.
	 */
	for(int i =1; i<threads+1; i++)
	{
		printf("\nBurst time for Thread %d: ", i);
		scanf("%d", &burstTime[0]);
	}



	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);





//policy = SCHED_RR;
//pthread_attr_setschedpolicy(&attr, policy);



}





void runner()
{



	/* acquire the semaphore */
//	sem_wait(&sem);
	sem_wait(&timer);       // wait for the timer signal


	/* critical section */



	/* release the semaphore */
//	sem_post(&sem);
	sem_post(&ready);       // fetch a thread in front of a waiting queue


}

















