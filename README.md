# OS_Lab4
A scheduler for user-level threads that works on Round Robin (RR) scheduling algorithm.

A controller creates as many threads as required, it employs a timer that interrupts the scheduler at predetermined intervals to switch the currently running 
tread to a thread in front of a waiting queue. Parameters such as time quantum( time interval or time slice) and burst time (execution time) for the scheduled thread h
ave to be passed into a controller that coordinates the scheduler and a time that maintains the intervals.

To compile: gcc schedule.o -pthread
