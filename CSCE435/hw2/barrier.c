//
// Implement a barrier for the threads; threads must wait at the barrier
// for all threads to reach it before going beyond
//
// Warning: Return values of calls are not checked for error to keep 
// the code simple.
//
// Compilation command on EOS:
//   module load intel/compilers
//   icc -o barrier.exe barrier.c -lpthread
//
// Sample execution and output ($ sign is the shell prompt):
//   $ barrier.exe 16
//   Threads = 16, barrier time (sec) =   1.0030
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "csce435.h"

#define MAX_THREADS     65536

int num_threads;

pthread_t p_threads[MAX_THREADS];
pthread_attr_t attr;

pthread_mutex_t lock_barrier;	// Protects count
pthread_cond_t cond_barrier;	// Monitors count
int count;			// Count of threads that have reached barrier

// Simple barrier routine
void barrier_simple () {
	pthread_mutex_lock(&lock_barrier);
	count++;
	while(count < num_threads) {
		pthread_cond_wait(&cond_barrier,&lock_barrier);
	}

	// Last thread should broadcast.
	if (count == num_threads) {
		pthread_cond_broadcast(&cond_barrier);
	}
	pthread_mutex_unlock(&lock_barrier);
}

void *start_func(void *s) {
    int thread_id = (int) s;
    work(thread_id, num_threads); 	// defined in csce435.h
    barrier_simple();
    pthread_exit(NULL);
}

// Main program - creates threads, each thread excutes barrier routine
int main(int argc, char *argv[]) {

    struct timeval start, stop; 
    double total_time;
    int i, j; 
    int true_minimum;

    if (argc != 2) {
	printf("Need one integers as input \n"); 
	printf("Use: <executable_name> <num_threads>\n"); 
	exit(0);
    }
    if ((num_threads = atoi(argv[argc-1])) > MAX_THREADS) {
	printf("Maximum number of threads allowed: %d.\n", MAX_THREADS);
	exit(0);
    }; 

    // Initialize mutex, condition variable, and attribute structures
    pthread_mutex_init(&lock_barrier, NULL); 
    pthread_cond_init(&cond_barrier, NULL); 
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Initialize count
    count = 0;

    // Create threads; each thread executes find_minimum
    gettimeofday(&start, NULL); 
    for (i = 0; i < num_threads; i++) {
	pthread_create(&p_threads[i], &attr, start_func, (void * )i); 
    }
    // Join threads
    for (i = 0; i < num_threads; i++) {
	pthread_join(p_threads[i], NULL);
    }
    // Print time taken
    gettimeofday(&stop, NULL); 
    total_time = (stop.tv_sec-start.tv_sec)
	+0.000001*(stop.tv_usec-start.tv_usec);

    printf("Threads = %d, barrier time (sec) = %8.4f\n", 
	    num_threads, total_time);

    // Destroy mutex and attribute structures
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&lock_barrier);
    pthread_cond_destroy(&cond_barrier);
}

