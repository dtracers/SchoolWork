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

pthread_mutex_t lock_stat;	// Protects minimum, count
double sum;			// Minimum value in the list
double sum_square;
int count;			// Count of threads that have updated mean

// Thread routine to compute minimum of sublist assigned to thread,
// and update global value of minimum if necessary
void *compute_sum (void *s) {
    int j;
    int thread_id = (int) s;
    int chunk_size = list_size/num_threads;
    int my_start = thread_id*chunk_size;
    int my_end = (thread_id+1)*chunk_size-1;
    if (thread_id == num_threads-1) my_end = list_size-1;

    // Thread computes summation of list[my_start ... my_end]
    double my_sum = list[my_start];
    double my_sum_square = ((double)list[my_start]) * ((double)list[my_start]);
    for (j = my_start+1; j <= my_end; j++) {
    	my_sum += list[j];
    	my_sum_square += ((double)list[j]) * ((double)list[j]);
    }
    pthread_mutex_lock(&lock_stat);
    sum += my_sum;
    sum_square += my_sum_square;
	count++;
	pthread_mutex_unlock(&lock_stat);

    // Thread exits
    pthread_exit(NULL);
}

// Main program - set up list of randon integers and use threads to find
// the minimum value; assign minimum value to global variable called minimum
int main(int argc, char *argv[]) {

	struct timeval start, stop; 
	double total_time;
	int i, j; 
	double true_mean;

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
	pthread_mutex_init(&lock_stat, NULL);
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
		pthread_create(&p_threads[i], &attr, compute_sum, (void * )i);
	}
	// Join threads
	for (i = 0; i < num_threads; i++) {
		pthread_join(p_threads[i], NULL);
	}

	// Entire list summed up.
	double mean = sum / ((double)list_size);
	double sum_square_mean = sum_square / ((double)list_size);
	double std = sqrt(sum_square_mean - mean * mean);

	// Print time taken
	gettimeofday(&stop, NULL); 
	total_time = (stop.tv_sec-start.tv_sec)
		+0.000001*(stop.tv_usec-start.tv_usec);

	// Check answer
	true_mean = 0;
	for (j = 0; j < list_size; j++)
		true_mean += (list[j]) / ((double)list_size);
	if (true_mean != mean)
		printf("Houston, we have a problem!\n");

	printf("Threads = %d, Mean: %lf, Standard Deviation: %lf, time (sec) = %8.4f\n",
			num_threads, mean, std, total_time);

	// Destroy mutex and attribute structures
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&lock_stat);
}

