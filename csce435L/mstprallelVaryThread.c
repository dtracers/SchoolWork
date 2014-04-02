//
// Computes the minimum spanning tree (MST) of a weighted graph
// The graph is provided as an adjacency matrix A
//
// Warning: Return values of calls are not checked for error to keep 
// the code simple.
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MAX_THREADS     1024
pthread_t p_threads[MAX_THREADS];
pthread_attr_t attr;
pthread_mutex_t lock_barrier = PTHREAD_MUTEX_INITIALIZER;	// Protects count
pthread_cond_t cond_barrier = PTHREAD_COND_INITIALIZER;	// Monitors count
pthread_barrier_t barr;

unsigned int num_nodes, root, seed, utotal;
double globalweight;
enum { FALSE, TRUE };
int num_threads;
double * d;
short int * inserted_in_mst;
#define MAX_N   	65536

#define INFINITY   	1.0e300

// MST
typedef struct _mst {
    unsigned int n;		// number of nodess in the tree
    unsigned int * node; 	// edge (i,node[i]) is in the MST
    double * weight; 		// weight of edge (i,node[i])
    double mst_weight; 		// weight of MST (sum of weights of all edges
} MST_t; 
// Adjacency matrix structure
typedef struct _adj_matrix {
    double ** weight; 
    int n; 
} ADJ_MATRIX_t;

// Variable Declarations
ADJ_MATRIX_t * A;		// Adjacency Matrix
MST_t * mst;

// -----------------------------------------------------------------------------
// MST Routines
//
// Create and initialize MST
//
MST_t * init_mst ( ADJ_MATRIX_t * A ) {
    unsigned i;
    MST_t * mst = calloc(1, sizeof(MST_t));
    mst->n = A->n;
    mst->node = calloc(mst->n, sizeof(unsigned int)); 
    mst->weight = calloc(mst->n, sizeof(double)); 
    for (i = 0; i < mst->n; i++) {
	mst->node[i] = i;
	mst->weight[i] = 0.0;
    }
    mst->mst_weight = 0.0; 
    return mst;
}
// -----------------------------------------------------------------------------
// Adjacency Matrix Routines
//
// Create and initialize adjacency matrix A with edge weights of the graph
//
ADJ_MATRIX_t * init_adj_matrix ( unsigned int num_nodes, unsigned int seed ) {
    unsigned int i, j;
    ADJ_MATRIX_t * A = calloc(1, sizeof(ADJ_MATRIX_t));
    A->n = num_nodes;
    // Allocate storage for matrix elements
    A->weight = calloc(A->n, sizeof(double *));
    for (i = 0; i < A->n; i++) {
	A->weight[i] = calloc(A->n, sizeof(double));
    }
    // Initialize matrix elements
    srand(seed); 
    double randwt;
    for (i = 0; i < A->n; i++) {
	for (j = i; j < A->n; j++) {
	    if (i == j) {
		A->weight[i][j] = 0.0;
	    } else {
		// Insert random edge weights
		randwt = (double)(rand_r(&seed))/(double)(RAND_MAX);
		A->weight[i][j] = randwt;
		A->weight[j][i] = randwt;
	    }
	}
    }
    return A;
}
// Compute minimum spanning tree of graph A
void *  minimum_spanning_tree(void *s) {
    unsigned int i, j, u, nodes;
	int thread_id = (int) s;
    double minwt; 

    // Initialize MST
	if(thread_id == 0)
	{
		mst = init_mst(A);
		d = calloc(A->n, sizeof(double)); 
		inserted_in_mst = calloc(A->n, sizeof(short int)); 
	}
	pthread_barrier_wait(&barr);
    // Initialize weight vector d with weight of edges connecting node i to root
   
    for (i = thread_id; i < A->n; i+= num_threads) 
	{
		d[i] = A->weight[root][i];	// d[i]= min wt. edge from node i to MST
		mst->node[i] = root;		// closest MST node to node i 
    }
	pthread_barrier_wait(&barr);
    // Initialize flag that indicates nodes in the tree
    
    for (i = thread_id; i < A->n; i+=num_threads) 
		inserted_in_mst[i] = FALSE;
	pthread_barrier_wait(&barr);
    // Prim's MST algorithm
	
    // Insert root into MST
	if(thread_id == 0)
	{
		inserted_in_mst[root] = TRUE;
		mst->node[root] = root;
		mst->weight[root] = 0.0;
		mst->mst_weight = 0.0;
	}
    nodes = 1; 
	 while (nodes < A->n) 
	{
		minwt = INFINITY;
		globalweight = INFINITY;
		// Find node u not belonging to MST with minimum weight edge in d
		pthread_barrier_wait(&barr);
		for (i = thread_id; i < A->n; i+=num_threads)  
		{
			if ((!inserted_in_mst[i]) && (d[i] < minwt)) 
			{
				u = i; 
				minwt = d[i];
			}
			
		}
		pthread_mutex_lock(&lock_barrier);
		
				if (globalweight > minwt) 
				{
					utotal = u; 
					globalweight = minwt;
				}
		pthread_mutex_unlock(&lock_barrier);
		pthread_barrier_wait(&barr);
		nodes++;
			// Add u to MST
			if(thread_id == 0)
			{
				mst->mst_weight += d[utotal];
				mst->weight[utotal] = d[utotal];
				inserted_in_mst[utotal] = TRUE;
			}
			
			//pthread_barrier_wait(&barr);
			// Update d vector
			pthread_barrier_wait(&barr);
			for (i = thread_id; i < A->n; i+=num_threads) 
			{
				if ((!inserted_in_mst[i]) && (d[i] > A->weight[utotal][i])) 
				{
					d[i] = A->weight[utotal][i];
					mst->node[i] = utotal;	// set u as closest MST node of i
				}
			}
	
    }
}
// Compute single source shortest path in graph A with root node r

// Main program 
// - Initialize adjacency matrix A of a graph
// - Computes single source shortest path with a given starting node r
int main(int argc, char *argv[]) 
{

	struct timeval start, stop; 
    double total_time;
	int i;
	
    if (argc != 5) {
	printf("Use: <executable_name> <num_nodes> <root_node> <seed> <num threads>\n");
	exit(0);
    }
    if ((num_nodes = atoi(argv[argc-4])) > MAX_N) {
	printf("Maximum number of nodes allowed: %d\n", MAX_N);
	exit(0);
    }; 
    if ((root = atoi(argv[argc-3])) > num_nodes) {
	printf("Root node (%d) cannot exceed number of nodes (%d)\n", root, num_nodes);
	exit(0);
    };
    if ((num_threads = atoi(argv[argc-1])) > MAX_THREADS) {
        printf("(%d) cannot exceed number of threads (%d)\n", root, MAX_THREADS);
        exit(0);
    };
    seed = atoi(argv[argc-2]);
	//num_threads = 8;
	pthread_mutex_init(&lock_barrier, NULL); 
    pthread_cond_init(&cond_barrier, NULL); 
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_barrier_init(&barr, NULL, num_threads);
	
    // Initialize adjacency matrix of graph
    A = init_adj_matrix(num_nodes, seed);

    // Compute single source shortest path with root node r
	
	
	
	
	gettimeofday(&start, NULL);
	for (i = 0; i < num_threads; i++) 
	{
		pthread_create(&p_threads[i], &attr, minimum_spanning_tree, (void * )i); 
    }
    // Join threads
    for (i = 0; i < num_threads; i++) 
	{
		pthread_join(p_threads[i], NULL);
    }
    //compute_LU_factors(L, U);
    gettimeofday(&stop, NULL); 
    total_time = (stop.tv_sec-start.tv_sec)
	+0.000001*(stop.tv_usec-start.tv_usec);
    // Print results
	printf("accomplished total");
    printf("MST: Nodes=%d, MST Weight = %e, minimum_spamming time (sec) = %8.4f\n", A->n, mst->mst_weight,total_time); 
 

/*

    unsigned int i, j;
    for (i = 0; i < mst->n; i++) 
	printf("(%d,%d,%4.1f)\n", i, mst->node[i], mst->weight[i]);

    // Print adjacency matrix
    printf("Graphs: nodes = %d\n", A->n); 
    for (i = 0; i < A->n; i++) {
	printf("%d: ", i); 
	for (j = 0; j < A->n; j++) {
	    if (A->weight[i][j] < INFINITY) 
		printf("(%d,%4.1f)", j, A->weight[i][j]); 
	}
	printf("\n"); 
    }
*/
	pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&lock_barrier);
    pthread_cond_destroy(&cond_barrier);
}

