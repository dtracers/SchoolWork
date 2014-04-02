//
// Computes the triangular factorization of a matrix: A = LU
// The matrix A is overwritten by L and U
//
// Warning: Return values of calls are not checked for error to keep 
// the code simple.
//
// Compilation command on EOS:
//   module load intel/compilers
//   icc -o matrix_serial.exe matrix_serial.c -lpthread -lc
//
// Sample execution and output ($ sign is the shell prompt):
//
// $ matrix_serial.exe 1024 1
//   Threads = 1, matrix_size = 1024, LU time (sec) =   1.8609
//   Threads = 1, matrix_size = 1024, Solve L time (sec) =   0.0070
//   Threads = 1, matrix_size = 1024, Solve U time (sec) =   0.0069
//   Threads = 1, matrix_size = 1024, err norm = 6.728074e-13
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MAX_THREADS     1024
#define MAX_N   	16384

// Dense matrix structure
typedef struct _matrix {
    double ** val; 
    int n; 
} MATRIX_t;

// Vector structure
typedef struct _vector {
    double * val; 
    int n;
} VECTOR_t;

// Variable Declarations
MATRIX_t * A;		// Matrix
MATRIX_t * L;		// Lower triangular matrix
MATRIX_t * U;		// Upper triangular matrix
VECTOR_t * xs; 		// Exact solution for A*x = b
VECTOR_t * b; 		// Right hand side (b = A*xs)
VECTOR_t * x; 		// Computed by solving A*x = b
VECTOR_t * y; 		// 

int num_threads;

// -- parallel pthread declaration -- //
pthread_attr_t attr;
pthread_barrier_t sync_LU, sync_U, sync_L;

// -----------------------------------------------------------------------------
// Vector Routines

// -- Create and initialize vector -- //

VECTOR_t * init_vector ( int n, double init_value ) {
    int i;
    VECTOR_t * x = calloc(1, sizeof(VECTOR_t));
    x->n = n; 
    x->val = calloc(x->n, sizeof(double)); 
    for (i = 0; i < x->n; i++) {
	x->val[i] = init_value;
    }
    return x;
}
// -----------------------------------------------------------------------------
// Matrix Routines

// -- Create and initialize matrix with zero value entries -- //

MATRIX_t * init_zero_matrix ( int n ) {
    int i, j;
    MATRIX_t * A = calloc(1, sizeof(MATRIX_t));
    A->n = n;

    // Allocate storage for matrix elements
    A->val = calloc(A->n, sizeof(double *));
    for (i = 0; i < A->n; i++) {
	A->val[i] = calloc(A->n, sizeof(double));
    }

    // Initialize matrix elements
    for (i = 0; i < A->n; i++) {
	for (j = 0; j < A->n; j++) {
	    A->val[i][j] = 0.0;
	}
    }
    return A;
}

// -- Create copy of matrix -- //
 
MATRIX_t * init_copy_matrix ( MATRIX_t * B ) {
    int i, j;
    MATRIX_t * A = calloc(1, sizeof(MATRIX_t));
    A->n = B->n;
    
    // Allocate storage for matrix elements
    A->val = calloc(A->n, sizeof(double *));
    for (i = 0; i < A->n; i++) {
	A->val[i] = calloc(A->n, sizeof(double));
    }
    
    // Initialize matrix elements
    for (i = 0; i < A->n; i++) {
	for (j = 0; j < A->n; j++) {
	    A->val[i][j] = B->val[i][j];
	}
    }
    return A;
}

// -- Create and initialize matrix: A[i][j] = 1.0/(1.0+abs(i-j)); -- //

MATRIX_t * init_matrix ( int n ) {
    int i, j;
    MATRIX_t * A = calloc(1, sizeof(MATRIX_t));
    A->n = n;
    
    // Allocate storage for matrix elements
    A->val = calloc(A->n, sizeof(double *));
    for (i = 0; i < A->n; i++) {
	A->val[i] = calloc(A->n, sizeof(double));
    }
    
    // Initialize matrix elements
    for (i = 0; i < A->n; i++) {
	for (j = 0; j < A->n; j++) {
	    A->val[i][j] = 1.0/(1.0+fabs(i-j)); 
	}
    }
    return A;
}

// -- Matrix vector product -- //

void matrix_vector_product ( MATRIX_t * A, VECTOR_t * x, VECTOR_t * y ) {
    int i, j;
    for (i = 0; i < A->n; i++) {
	y->val[i] = 0.0;
	for (j = 0; j < A->n; j++) {
	    y->val[i] += A->val[i][j] * x->val[j];
	}
    }
}

// ------------------------------------------------------------------------------- //
// -- Parallel code to compute LU factorization -- //

void *compute_LU_factors_in_Parallel (void* ptr) 
{
    int i, j, k;
    double pivot;
    int id = (int) ptr;
    int start_index = 0;
    double * U_row_i;
    double * U_row_k;
    int length = U->n;
    for (k = 0; k < length; k++)
    {
        start_index = k+1;
        pivot = U->val[k][k];
	L->val[k][k] = 1.0;
	
	// -- implement thread barrier -- //
        pthread_barrier_wait(&sync_LU);

        for (i = start_index+id; i < length; i+=num_threads) 
        {
            L->val[i][k] = U->val[i][k]/pivot;
            U->val[i][k] = 0.0;
        }
	

        U_row_k = U->val[k];
        for (i = start_index+id; i < length; i+=num_threads) 
        {
	    U_row_i = U->val[i];
	    double l_value = L->val[i][k];
	    for (j = start_index; j < length; j++) 
            {
                U_row_i[j] -= l_value * U_row_k[j];
            }
        }

	// -- implement thread barrier -- //
	pthread_barrier_wait(&sync_LU);
    }

    // printf("%i is out of LU compute\n", id);
}

// ------------------------------------------------------------------------------- //
// -- Serial code to compute LU factorization of A = LU -- //

void compute_LU_factors ( MATRIX_t * L,  MATRIX_t * U) {
    int i, j, k;
    double pivot;

    for (k = 0; k < U->n; k++) {
	pivot = U->val[k][k];
	L->val[k][k] = 1.0;
	for (i = k+1; i < U->n; i++) {
	    L->val[i][k] = U->val[i][k]/pivot;
	    U->val[i][k] = 0.0;
	}
	for (i = k+1; i < U->n; i++) 
	    for (j = k+1; j < U->n; j++) 
		U->val[i][j] -= L->val[i][k]*U->val[k][j];
    }
}

// ------------------------------------------------------------------------------- //
// -- Parallel code to solve lower triangular system -- //

void* solve_lower_triangular_system_in_Parallel (void* ptr) 
{
    int i, k;
    int id = (int) ptr;
    int length = L->n;
    double value_k;

    for (i = id; i < length; i+=num_threads)
    {
	y->val[i] = b->val[i];
    }
    
    for (k = 0; k < length; k++) 
    {

	// -- implement thread barrier -- //
        pthread_barrier_wait(&sync_L);

	y->val[k] = y->val[k] / L->val[k][k];	
        value_k = y->val[k];
	
	for (i = k+id+1; i < length; i+=num_threads)
	{
	    y->val[i] -= L->val[i][k] * value_k;
	}
    }
}

// ------------------------------------------------------------------------------- //
// -- Serial code to solve lower triangular system -- //

void solve_lower_triangular_system ( MATRIX_t * L, VECTOR_t * b, VECTOR_t * x ) {
    int i, k;
    for (i = 0; i < L->n; i++) 
	x->val[i] = b->val[i]; 
    for (k = 0; k < L->n; k++) {
	x->val[k] = x->val[k]/L->val[k][k];
	for (i = k+1; i < L->n; i++) {
	    x->val[i] -= L->val[i][k]*x->val[k];
	}
    }
}

// ------------------------------------------------------------------------------- //
// -- Parallel code to solve lower triangular system -- //

void* solve_upper_triangular_system_in_Parallel (void* ptr) 
{
    int i, k;
    int id = (int) ptr;
    int length = U->n;
    double value_k;

    for (i = id; i < length; i+=num_threads)
    {
	x->val[i] = y->val[i];
    }

    for (k = U->n-1; k >= 0; k--) 
    {	
	// -- implement thread barrier -- //
        pthread_barrier_wait(&sync_U);
	
	if (id ==0)
	    x->val[k] = x->val[k]/U->val[k][k];

	// -- implement thread barrier -- //
        pthread_barrier_wait(&sync_U);
   	for (i = k-1 - id; i >=0; i-=num_threads)
	{
	    x->val[i] -= U->val[i][k] * x->val[k];
	}
    }
}

// ------------------------------------------------------------------------------- //
// -- Serial code to solve upper triangular system -- //

void solve_upper_triangular_system ( MATRIX_t * U, VECTOR_t * b, VECTOR_t * x ) {
    int i, k;
    for (i = 0; i < U->n; i++) 
	x->val[i] = b->val[i]; 
    for (k = U->n-1; k >= 0; k--) {
	x->val[k] = x->val[k]/U->val[k][k];
	for (i = k-1; i >= 0; i--) {
	    x->val[i] -= U->val[i][k]*x->val[k];
	}
    }
}

/*
// -- Main program -- //
   ** Responsible for initializing a dense matrix A. Computes the triangular factors 
   ** L and U such that A = L * U. Then computes the solution of the system Ax = b as
   ** shown in: { Solve Ly = b for y, Ux = y for x }. And finally checks the solution.
*/

int main (int argc, char *argv[]) 
{
    struct timeval start, stop; 
    double total_time;
    int i, j, matrix_size; 
    float err, sum;

    if (argc != 3) 
    {
	   printf("Need two integers as input \n"); 
	   printf("Use: <executable_name> <matrix_size> <num_threads>\n"); 
	   exit(0);
    }
    if ((matrix_size = atoi(argv[argc-2])) > MAX_N) 
    {
	   printf("Maximum matrix size allowed: %d.\n", MAX_N);
	   exit(0);
    }; 
    if ((num_threads = atoi(argv[argc-1])) > MAX_THREADS) 
    {
	   printf("Maximum number of threads allowed: %d.\n", MAX_THREADS);
	   exit(0);
    }; 
    if (num_threads > matrix_size) 
    {
	   printf("Number of threads (%d) > matrix_size (%d) not allowed.\n", num_threads, matrix_size);
	   exit(0);
    }; 
    
    // -- parallel pthread declaration -- //
    int indices[num_threads];
    pthread_t threads[num_threads];
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
     
    // -- Initialize matrix A -- //
    A = init_matrix(matrix_size);

    // -- Initialize solution xs = 1.0 -- //
    xs = init_vector(matrix_size, 1.0);

    // -- Initialize right hand side vector b = A * xs -- //
    b = init_vector(matrix_size, 0.0);
    matrix_vector_product(A, xs, b);

    // -- Compute LU factorization of A s.t. A = L * U -- //
    L = init_zero_matrix(A->n);
    U = init_copy_matrix(A);
    gettimeofday(&start, NULL); 
    
    // -- LU Barrier creation -- //
    if (pthread_barrier_init(&sync_LU, NULL, num_threads))
	    printf("Couldn't create an LU barrier\n");

    // -- L Barrier creation -- //
    if (pthread_barrier_init(&sync_L, NULL, num_threads))
        printf("Couldn't create an L barrier\n");

    // -- U Barrier creation -- //
    if (pthread_barrier_init(&sync_U, NULL, num_threads))
        printf("Couldn't create a U barrier\n");
   
    // --------------------------------------------------------------------------- //
    // --                       Parallel compute_LU function                    -- //

    // -- pthread initialization -- //
    for (i = 0; i < num_threads; i++) 
    {
    	indices[i] = i;
        j = pthread_create(&threads[i], &attr, compute_LU_factors_in_Parallel, (void*) i);
    }

    // -- computing LU factors -- //
    // compute_LU_factors(L, U);

    // -- parallel pthread decomposition -- //
    for (i = 0; i < num_threads; i++)
    	j = pthread_join(threads[i], NULL);
   
    // --------------------------------------------------------------------------- //

    gettimeofday(&stop, NULL); 
    total_time = (stop.tv_sec-start.tv_sec)+0.000001*(stop.tv_usec-start.tv_usec);
    printf("Threads = %d, matrix_size = %d, LU time (sec) = %8.4f\n", num_threads, matrix_size, total_time);

    // -- Solve Ly = b for y -- //
    y = init_vector(matrix_size, 0.0);
    gettimeofday(&start, NULL); 

    // --------------------------------------------------------------------------- //
    // --                       Parallel solve_lower function                   -- //

    // -- pthread initialization -- //
    for (i = 0; i < num_threads; i++)
    	j = pthread_create(&threads[i], &attr, solve_lower_triangular_system_in_Parallel, (void *) i);
    
    // -- solving lower triangle -- //
    // solve_lower_triangular_system(L, b, y);

    // -- parallel pthread decomposition -- //
    for (i = 0; i < num_threads; i++)
    	j = pthread_join(threads[i], NULL);

    // --------------------------------------------------------------------------- //

    gettimeofday(&stop, NULL); 
    total_time = (stop.tv_sec-start.tv_sec)+0.000001*(stop.tv_usec-start.tv_usec);
    printf("Threads = %d, matrix_size = %d, Solve L time (sec) = %8.4f\n", num_threads, matrix_size, total_time);

    // -- Solve Ux = y for x -- //
    x = init_vector(matrix_size, 0.0);
    gettimeofday(&start, NULL); 

    // --------------------------------------------------------------------------- //
    // --                     Parallel solve_upper function                     -- //
    
    // -- pthread initialization -- //
    for (i = 0; i < num_threads; i++)
    	j = pthread_create(&threads[i], &attr, solve_upper_triangular_system_in_Parallel, (void *) i);
    
    // -- solving upper triangle -- //
    // solve_upper_triangular_system(U, y, x);

    // -- parallel pthread decomposition -- //
    for (i = 0; i < num_threads; i++)
    	j = pthread_join(threads[i], NULL);

    // --------------------------------------------------------------------------- //

    gettimeofday(&stop, NULL); 
    total_time = (stop.tv_sec-start.tv_sec)+0.000001*(stop.tv_usec-start.tv_usec);
    printf("Threads = %d, matrix_size = %d, Solve U time (sec) = %8.4f\n", num_threads, matrix_size, total_time);

    // --------------------------------------------------------------------------- //

    // -- Compute error norm: norm of (xs - x) -- //
    err = 0.0;
    for (j = 0; j < x->n; j++) 
	   err += (xs->val[j]-x->val[j])*(xs->val[j]-x->val[j]);
    
    err = sqrtf(err);
    printf("Threads = %d, matrix_size = %d, err norm = %e\n", num_threads, matrix_size, err);

    // --------------------------------------------------------------------------- //
    // --                      Destroy barrier and pthreads                     -- //
    
    // -- parallel barrier destruction -- //

    pthread_attr_destroy(&attr);
    pthread_barrier_destroy(&sync_LU);
    pthread_barrier_destroy(&sync_L);
    pthread_barrier_destroy(&sync_U);
}

