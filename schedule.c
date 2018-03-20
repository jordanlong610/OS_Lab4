/*
 * Lab 4 - Thread Scheduling
 * Programmer: Jordan Long
 * Instructor: S. Lee
 * Course: SMPE 320
 * Section 1
 */


#include <semaphore.h>

sem_init(&ready, 0, 0);
sem_init(&timer, 0, 1);



sem_t timer;
sem_t ready;





sem_wait(&timer);       // wait for the timer signal
sem_post(&ready);       // fetch a thread in front of a waiting queue





pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);





policy = SCHED_RR;
pthread_attr_setschedpolicy(&attr, policy);
