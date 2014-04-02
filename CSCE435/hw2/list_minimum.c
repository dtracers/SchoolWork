//
// Computes the minimum of a list using multiple threads
//
// Warning: Return values of calls are not checked for error to keep 
// the code simple.
//
// Compilation command on EOS:
//   module load intel/compilers
//   icc -o list_minimum.exe list_minimum.c -lpthread -lc
//
// Sample execution and output ($ sign is the shell prompt):
//   $ list_minimum.exe 1000 10
//   Threads = 10, minimum = 657315, time (sec) =   0.0005
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MAX_THREADS     65536
#define MAX_LIST_SIZE   268435456

int num_threads;

pthread_t p_threads[MAX_THREADS];
pthread_attr_t attr;

int list[MAX_LIST_SIZE];	// List of values
int list_size;			// List size

pthread_mutex_t lock_minimum;	// Protects minimum, count
int minimum;			// Minimum value in the list
int count;			// Count of threads that have updated minimum

// Thread routine to compute minimum of sublist assigned to thread, 
// and update global value of minimum if necessary
void *find_minimum (void *s) {
    int j;
    int thread_id = (int) s;
    int chunk_size = list_size/num_threads;
    int my_start = thread_id*chunk_size;
    int my_end = (thread_id+1)*chunk_size-1;
    if (thread_id == num_threads-1) my_end = list_size-1;

    // Thread computes minimum of list[my_start ... my_end]
    int my_minimum = list[my_start]; 
    for (j = my_start+1; j <= my_end; j++) {
	if (my_minimum > list[j]) my_minimum = list[j]; 
    }

    pthread_mutex_lock(&lock_minimum);
	// If this is the first thread to finish we set minimum to initialize it.
	if(minimum > my_minimum || count == 0) {
		minimum = my_minimum;
	}
	count++;
	pthread_mutex_unlock(&lock_minimum);

    // Thread exits
    pthread_exit(NULL);
}

// Main program - set up list of randon integers and use threads to find
// the minimum value; assign minimum value to global variable called minimum
int main(int argc, char *argv[]) {

	struct timeval start, stop; 
	double total_time;
	int i, j; 
	int true_minimum;

	if (argc != 3) {
		printf("Need two integers as input \n"); 
		printf("Use: <executable_name> <list_size> <num_threads>\n"); 
		exit(0);
	}
	if ((list_size = atoi(argv[argc-2])) > MAX_LIST_SIZE) {
		printf("Maximum list size allowed: %d.\n", MAX_LIST_SIZE);
		exit(0);
	}; 
	if ((num_threads = atoi(argv[argc-1])) > MAX_THREADS) {
		printf("Maximum number of threads allowed: %d.\n", MAX_THREADS);
		exit(0);
	}; 
	if (num_threads > list_size) {
		printf("Number of threads (%d) < list_size (%d) not allowed.\n", num_threads, list_size);
		exit(0);
	}; 

	// Initialize mutex and attribute structures
	pthread_mutex_init(&lock_minimum, NULL); 
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	// Initialize list
	unsigned int seed = 0; 
	srand(seed); 
	for (j = 0; j < list_size; j++) list[j] = rand_r(&seed); 

	// Initialize count
	count = 0;

	// Create threads; each thread executes find_minimum
	gettimeofday(&start, NULL); 
	for (i = 0; i < num_threads; i++) {
		pthread_create(&p_threads[i], &attr, find_minimum, (void * )i); 
	}
	// Join threads
	for (i = 0; i < num_threads; i++) {
		pthread_join(p_threads[i], NULL);
	}
	// Check answer
	true_minimum = list[0];
	for (j = 1; j < list_size; j++) 
		if (true_minimum > list[j]) true_minimum = list[j]; 
	if (true_minimum != minimum) 
		printf("Houston, we have a problem!\n"); 

	// Print time taken
	gettimeofday(&stop, NULL); 
	total_time = (stop.tv_sec-start.tv_sec)
		+0.000001*(stop.tv_usec-start.tv_usec);

	printf("Threads = %d, minimum = %d, time (sec) = %8.4f\n", 
			num_threads, minimum, total_time);

	// Destroy mutex and attribute structures
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&lock_minimum);
}

