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
int timeQ;
int threadsCreated;
int threadsFinished = 0;
int* burstTime;
int globalTime = 0;

/*
 * Runner for each spawned thread. Will wait for its turn, then run for allotted burst time until finished.
 */
void *threadRunner(void *number)
{
  int threadTime = 0;
  int threadNumber = *((int *) number);
  while(threadTime < burstTime[threadNumber])
  {
	  sem_wait(&timer);
	  printf("Thread %d now being executed.\n", threadNumber);
	  	int i = 0;
	  	while(i < timeQ && threadTime < burstTime[threadNumber]+1)
	  	{
	  	  sleep(1);
	  	  threadTime++;
	  	  i++;
	  	}
  }
  printf("Thread %d finished in %d seconds! It will now be terminated.\n", threadNumber, globalTime);
  threadsFinished++;
  pthread_exit(0);
}

/*
 * Timer will call sem post every time the time reaches the timeQuantum
 * When all threads finish, timer thread will exit.
 */
void *timerFunction()
{
	globalTime = 0;
	int interval = timeQ;
	while(threadsFinished != threadsCreated)
	{

		if(globalTime == interval)
		{
			interval += timeQ;
			sem_post(&timer);
		}
		else
		{
			printf("%d\n", globalTime);
			sleep(1);
			globalTime++;
		}
    }
	printf("All threads finished. Scheduler thread will now exit.");
	pthread_exit(0);
}


/*
 * Main method for the thread scheduling program.
 * Will check inputs, request burst times for each thread, and then spawn the threads.
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

	/*
	 * If threads to be created is greater than 10, reject and quit.
	 */
	if(atoi(argv[1]) > 10)
	{
		fprintf(stderr,"Cannot create more than 10 threads!\n");
		return -1;
	}

	threadsCreated = atoi(argv[1]);
	timeQ = atoi(argv[2]);
	int BT[threadsCreated]; //Point local burst times at global array
	burstTime = BT;

	/*
	 * Prints out requests for burst times of each thread, and stores value in  burstTime array.
	 */
	for(int i=0; i<threadsCreated; i++)
	{
		printf("\nBurst time for Thread %d: ", i);
		scanf("%d", &burstTime[i]);
	}

	/*
	 * Create Timer thread
	 */
	pthread_t timer_thread;
	pthread_attr_t timer_attr;
	pthread_attr_init(&timer_attr);
	pthread_create(&timer_thread, &timer_attr, timerFunction, NULL);

	/*
	 * Loop and create requested threads.
	 */
	pthread_t threads[threadsCreated];
	pthread_attr_t attr[threadsCreated];
	for(int i=0; i<threadsCreated; i++)
	{
		int *arg = malloc(sizeof(*arg)); //Convert int to a pointer
		*arg = i;
		pthread_attr_init(&attr[i]);
		pthread_attr_setscope(&attr[i], PTHREAD_SCOPE_SYSTEM);
		pthread_attr_setschedpolicy(&attr[i], SCHED_RR);
		pthread_create(&threads[i], &attr[i], threadRunner, arg);
	}
	pthread_join(timer_thread, NULL);
}














