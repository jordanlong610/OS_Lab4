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
int* burstTime;

int updateThreadTime(int, int, int);

void *threadTime(void *input)
{
  int time = 0;
  int threadNumber = atoi(input);
  while(time < burstTime[threadNumber])
  {
    sem_wait(&timer);
    time = updateThreadTime(time, burstTime[threadNumber], threadNumber);
  }
  printf("Thread %d is finished!\n", threadNumber);
  pthread_exit(0);
}

int updateThreadTime(int timer, int burstTime, int threadNumber)
{
  printf("Thread %d now being executed.\n", threadNumber);
  int i = 0;
  while(i < timeQ && timer < burstTime)
  {
    sleep(1);
    timer++;
    fflush(stdout);
    i++;
  }
  return timer;
}

/*
 * Timer will call sem post every time the time reaches the timeQuantum
 * When all threads finish, timer thread will exit.
 */
void *timerTime()
{
	int time = 0;
	int interval = timeQ;
	while(1)
	{
		printf("%d\n", time);
		sleep(1);
		time++;

		if(time == interval)
		{
			interval += timeQ;
			sem_post(&timer);
		}
    }
	printf("All threads finished.");
	pthread_exit(0);
}



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

	/*
	 * If threads to be created is greater than 10, reject and quit.
	 */
	if(atoi(argv[1]) > 10)
	{
		fprintf(stderr,"Cannot create more than 10 threads!\n");
		return -1;
	}


	int threadsCreated = atoi(argv[1]);
	timeQ = atoi(argv[2]);
	int BT[threadsCreated]; //Point local burst times at global array
	burstTime = BT;

	/*
	 * Prints out requests for burst times of each thread, and stores value in array burstTime.
	 */
	for(int i =0; i<threadsCreated; i++)
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
	pthread_create(&timer_thread, &timer_attr, timerTime, NULL);

	/*
	 * Loop and create requested threads.
	 */
	pthread_t threads[threadsCreated];
	pthread_attr_t attr[threadsCreated];
	for(int i=0; i<threadsCreated; i++)
	{
	  pthread_attr_init(&attr[i]);
	  pthread_attr_setscope(&attr[i], PTHREAD_SCOPE_SYSTEM);
	  pthread_attr_setschedpolicy(&attr[i], SCHED_RR);
	  pthread_create(&threads[i], &attr[i], threadTime, &i);
	}
	pthread_join(timer_thread, NULL);
}














