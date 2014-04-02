//
// Computes the prefix sum of elements of a list using multiple threads
// Given a list of integers x[0], x[1], x[2], ..., x[n-1], 
// prefix sum of element x[i] // is defined as 
//    s[i] = x[0]+x[1]+...+x[i], for i = 0,..., n-1
//
// Warning: Return values of calls are not checked for error to keep 
// the code simple.
//
// Compilation command on EOS:
//   module load intel/compilers
//   icc -o prefix_sum.exe prefix_sum.c -lpthread -lc
//
// Sample execution and output ($ sign is the shell prompt):
//   $./prefix_sum.exe 1000000 8
//   $Congratulations. Prefix sum computed correctly
//   $Threads = 8, list size = 1000000, time (sec) =   0.0028
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MAX_THREADS     65536
#define MAX_LIST_SIZE   200000000

int num_threads;

pthread_t p_threads[MAX_THREADS];
pthread_attr_t attr;

pthread_mutex_t lock_barrier;
int list[MAX_LIST_SIZE];		// List of values
int list_size;				// List size
int prefix_sum_list[MAX_LIST_SIZE];	// Prefix sum
int mylist_sum[MAX_THREADS];		// Sum of each sublist 
int wait_list[MAX_THREADS];

// Thread routine to compute prefix sum 
void *prefix_sum (void *s) {
    int j, sum, offset;
    int thread_id = (int) s;
    int chunk_size = list_size/num_threads;
    int my_start = thread_id*chunk_size;
    int my_end = (thread_id+1)*chunk_size-1;
    if (thread_id == num_threads-1) my_end = list_size-1;

    // Sublist of this thread: list[my_start ... my_end]
    sum = list[my_start];
    prefix_sum_list[my_start] = sum;
    // Thread computes sum of elements in its sublist
    for (j = my_start + 1; j <= my_end; j++) {
    	sum += list[j];
    	prefix_sum_list[j] = sum;
    }
    // Thread initializes global array element 
    // mylist_sum[thread_id] with the sum
    mylist_sum[thread_id] = sum;
    // Note that sum of elements list[0 ... (my_start-1)] equals
    // sum of elements mylist_sum[0 ... (thread_id-1)]
    if (thread_id > 0) {
    	while(wait_list[thread_id-1] != 1) {
    		// wait..!
    		struct timespec sleeptime;
			sleeptime.tv_sec = 0.0; sleeptime.tv_nsec = 10;
			nanosleep(&sleeptime, NULL);
    	}
		pthread_mutex_lock(&lock_barrier);
		offset = mylist_sum[0];
		// Thread computes offset = sum of elements list[0 ... (my_start-1)],
		// which is equal to sum of elements mylist_sum[0 ... (threadid-1)]
		for (j = 1; j <= thread_id - 1; j++) {
			offset += mylist_sum[j];
		}

		// Thread computes prefix sum of its sublist using offset
		for(j = my_start; j <= my_end; j++) {
			prefix_sum_list[j] += offset;
		}
		pthread_mutex_unlock(&lock_barrier);
    }
	wait_list[thread_id] = 1;

    // Thread exits
    pthread_exit(NULL);
}

// Main program - set up list of randon integers and use threads to compute
// the prefix sum of each element
// 
int main(int argc, char *argv[]) {

    struct timeval start, stop; 
    double total_time;
    int i, j; 
    int error;

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

    pthread_mutex_init(&lock_barrier, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    // Initialize list
    unsigned int seed = 0; 
    srand(seed); 
    for (j = 0; j < list_size; j++) list[j] = rand_r(&seed) % 10; 

    // Create threads; each thread executes prefix_sum
    gettimeofday(&start, NULL); 
    for (i = 0; i < num_threads; i++) {
	pthread_create(&p_threads[i], &attr, prefix_sum, (void * )i); 
    }
    // Join threads
    for (i = 0; i < num_threads; i++) {
	pthread_join(p_threads[i], NULL);
    }
    // Print time taken
    gettimeofday(&stop, NULL); 
    total_time = (stop.tv_sec-start.tv_sec)
	+0.000001*(stop.tv_usec-start.tv_usec);

    // Check answer
    error = 0; 
    if (list[0] != prefix_sum_list[0]) error = 1;
    for (j = 1; j < list_size; j++) {
    	if (list[j] != (prefix_sum_list[j]-prefix_sum_list[j-1])) error = 1;
    	if (prefix_sum_list[j] < 0) {
    		printf("switch over %d at j %d", prefix_sum_list[j], j);
    		break;
    	}
    }
    if (error) {
		printf("Houston, we have a problem!\n");
		exit(0);
    } else {
    	printf("Congratulations. Prefix sum computed correctly\n");
    }

    printf("Threads = %d, list size = %d, time (sec) = %8.4f\n", 
	    num_threads, list_size, total_time);

    // Destroy mutex and attribute structures
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&lock_barrier);
}

