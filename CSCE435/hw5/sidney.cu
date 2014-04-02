//
// CUDA code to compute minimum distance between n points
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MAX_POINTS 1048576
#define BLOCK_SIZE 1024
#define M_LOG2E 1.44269504088896340736 //log2(e)

inline long double my_log(const long double x){
    return  log(x) * M_LOG2E;
}

int blocks;     //log2(num_points);
int threads;    //num_points/blocks;
int num_points;

// ---------------------------------------------------------------------------- 
// Kernel Function to compute distance between all pairs of points
// Input: 
//  X: X[i] = x-coordinate of the ith point
//  Y: Y[i] = y-coordinate of the ith point
//  n: number of points
//
// Output: 
//  D: D[0] = minimum distance
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Compute minimum distance on host to check device computation
// Need to:  modify the kernel functino to compute the minimum distance.
// You are allowed to make other changes to the code that facilitate
// parallelization on the GPU
//
// 1. You need to develop CUDA-based parallel code to compute the
// distance between the closest pair of points on a GPU
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// References
// ----------------------------------------------------------------------------
/* 
__global__ void VecAdd(float* A, float* B, float* C, int N) 
{ 
 int i = blockDim.x * blockIdx.x + threadIdx.x; 
 if (i < N) 
 C[i] = A[i] + B[i]; 
} 
*/

/*
__global__ void MatMult(float* A, float* B, float* C, int N) 
{ 
int i = blockIdx.x * blockDim.x + threadIdx.x; 
 int j = blockIdx.y * blockDim.y + threadIdx.y; 
 if (i < N && j < N) 
 C[i][j] = A[i][j] + B[i][j];
 }
 */
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Kernel function code goes here
// ---------------------------------------------------------------------------- 
__global__ void minimum_distance(float * X, float * Y, float * D, int n) 
{
    //CUDA version of the code
    int i = blockIdx.y * blockDim.y + threadIdx.y;
    //int j = blockIdx.x * blockDim.x + threadIdx.x + 1;

    if(threadIdx.y == 0)
    {
        D[0] = 10;
    }

    extern __shared__ float mins[]; 
    __threadfence();

    //if (i < n && j < n) 
    if(i<n)
    {
        for (int j = i+1; j < n; j++) 
        {
            float dx = X[j]-X[i];
            float dy = Y[j]-Y[i];
            float Dij = sqrtf(dx*dx+dy*dy);
            
            //__threadfence();

            //mins local to the block
            mins[threadIdx.x] = Dij;

            __syncthreads();
        }
    }

    //let the last block handle finding the actual minimum
    if(i >= n)
    {
        //sort mins to 
        for(unsigned int s = blockDim.y/2; s > 0; s >>= 1) 
        {

            if(threadIdx.y < s)
            {
                if (mins[threadIdx.y] > mins[threadIdx.y + s]) 
                {
                    mins[threadIdx.y] = mins[threadIdx.y + s];
                }
            }
            __syncthreads();
        }

        //now update global minimum
        if(threadIdx.y == 0)
        {
            if(D[0] > mins[0])
            {
                D[0] = mins[0];
            }
        }
    }
    //D[0] = -15;
} 
// ---------------------------------------------------------------------------- 

// ---------------------------------------------------------------------------- 
// Main program - initializes points and computes minimum distance 
// between the points
// ---------------------------------------------------------------------------- 
int main(int argc, char* argv[]) {

    // Host Data
    float * hVx;            // host x-coordinate array
    float * hVy;            // host y-coordinate array
    float * hmin_dist;      // minimum value on host

    // Device Data
    float * dVx;            // device x-coordinate array
    float * dVy;            // device x-coordinate array
    float * dmin_dist;      // minimum value on device

    int i, j, size;// num_points, blocks, threads; 
    float dx, dy, Dij, distance;
    unsigned int seed = 0;

    cudaEvent_t start, stop;        // GPU timing variables

    struct timeval cpu_start, cpu_stop; // CPU timing variables

    float time_array[10]; 

    // Timing initializations
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Check input
    if (argc != 2) {
    printf("Use: %s <number of points>\n", argv[0]);  
    exit(0);
    }
    if ((num_points = atoi(argv[argc-1])) > MAX_POINTS) {
    printf("Maximum number of points allowed: %d\n", MAX_POINTS);
    exit(0);
    } 

    // Allocate host coordinate arrays 
    size = num_points * sizeof(float); 
    hVx = (float *) malloc(size); 
    hVy = (float *) malloc(size);
    hmin_dist = (float *) malloc(sizeof(float));

    // Initialize points
    for (i = 0; i < num_points; i++) {
        hVx[i] = (float)(rand_r(&seed))/(float)(RAND_MAX);
        hVy[i] = (float)(rand_r(&seed))/(float)(RAND_MAX);
    }

    // Allocate device coordinate arrays
    cudaMalloc(&dVx, size);
    cudaMalloc(&dVy, size);
    cudaMalloc(&dmin_dist, sizeof(float));

    // Copy coordinate arrays from host memory to device memory 
    cudaEventRecord( start, 0 ); 

    cudaMemcpy(dVx, hVx, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dVy, hVy, size, cudaMemcpyHostToDevice);

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&(time_array[0]), start, stop);

    // Invoke kernel
    cudaEventRecord(start, 0); 

    // ------------------------------------------------------------
    //
    // Invoke kernel function here
    //
    // ------------------------------------------------------------
    //choose the number of blocks and points
    threads = 16;                      //num_points/blocks;
    blocks = num_points/threads;       //my_log(num_points);
    minimum_distance<<<(blocks), threads>>>(dVx, dVy, dmin_dist, num_points);

    //alternative declaration
    //dim3 block(16,16);
    //dim3 grid((num_points + 15)/16, (num_points + 15)/16);
    //minimum_distance<<<grid, block>>>(dVx, dVy, dmin_dist, num_points);

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&(time_array[1]), start, stop);

    // Copy result from device memory to host memory 
    cudaEventRecord(start, 0); 

    //this was wrong! converting size to sizeof(float)
    cudaMemcpy(hmin_dist, dmin_dist, sizeof(float), cudaMemcpyDeviceToHost);

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&(time_array[2]), start, stop);

    printf("Number of Points = %d\n", num_points); 
    printf("GPU Host-to-device = %f ms \n", time_array[0]);
    printf("GPU execution time = %f ms \n", time_array[1]);
    printf("GPU Device-to-host = %f ms \n", time_array[2]);
    printf("Minimum distance (GPU) = %e\n", hmin_dist[0]);

    gettimeofday(&cpu_start, NULL);

    dx = hVx[1]-hVx[0];
    dy = hVy[1]-hVy[0];
    distance = sqrtf(dx*dx+dy*dy);
    
    for (i = 0; i < num_points; i++) {
       for (j = i+1; j < num_points; j++) {
           dx = hVx[j]-hVx[i];
           dy = hVy[j]-hVy[i];
           Dij = sqrtf(dx*dx+dy*dy);
           if (distance > Dij) distance = Dij;
       }
    }

    gettimeofday(&cpu_stop, NULL); 
    time_array[3] = 1000*(cpu_stop.tv_sec-cpu_start.tv_sec)
    +0.000001*(cpu_stop.tv_usec-cpu_start.tv_usec);
    printf("CPU execution time = %f ms\n", time_array[3]);
    printf("Minimum distance (CPU) = %e\n", distance);

    // Free device memory 
    cudaFree(dVx);
    cudaFree(dVy);
    cudaFree(dmin_dist);

    // Free host memory 
    free(hVx);
    free(hVy);
    free(hmin_dist);

    return 0;
}  
// ---------------------------------------------------------------------------- 
