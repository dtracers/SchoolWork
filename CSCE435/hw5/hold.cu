//
// CUDA code to compute minimu distance between n points
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MAX_POINTS 1048576
#define BLOCK_SIZE 1024

int blocks;     //log2(num_points);
int threads;    //num_points/blocks;
int num_points;

//__device__ float mins[BLOCK_SIZE];

// ---------------------------------------------------------------------------- 
// Kernel Function to compute distance between all pairs of points
// Input: 
//  X: X[i] = x-coordinate of the ith point
//  Y: Y[i] = y-coordinate of the ith point
//  n: number of points
//
// Output: 
//  D: D[0] = minimum distance
//
__global__ void minimum_distance(float * X, float * Y, float * D, int n) {
	//CUDA version of the code
	//D[0] = (float)blockDim.x;
	//return;
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	//int j = blockIdx.x * blockDim.x + threadIdx.x +1;

	//int i = threadIdx.x;
	//int j = threadIdx.x + 1;

	if (i == 0) {
		D[0] = 999;
	}

	extern __shared__ float mins[];
	__threadfence();

	float distance = 999;
	//D[0] = distance;
	//printf((int)distance);

	if (i < n) {
		for (int j = i + 1; j < n; j++) {
			float dx = X[j] - X[i];
			float dy = Y[j] - Y[i];
			float Dij = sqrtf(dx * dx + dy * dy);
			if (distance > Dij) {
				distance = Dij;
			}
		}

		//mins local to the block
		mins[threadIdx.x] = distance;
	}
	//return;

	__syncthreads();

	if (i < blockDim.x) {
		int maxValue = blockDim.x;
		if (maxValue > n) {
			maxValue = n;
		}
		int index = threadIdx.x;
		for (unsigned int s = maxValue / 2; s > 0; s >>= 1) {
			if (index < s) {
				if (mins[index] > mins[index + s - 1]
						&& mins[index + s - 1] != 0)
					mins[index] = mins[index + s - 1];
			}
			__syncthreads();
		}
		if (i == 0) {
			if (D[0] > mins[0] && mins[0] != 0) {
				D[0] = mins[0];
			}
		}

	}
//    return;

	//now update global minimum

}

// ---------------------------------------------------------------------------- 
// Main program - initializes points and computes minimum distance 
// between the points
//
int main(int argc, char* argv[]) {

	// Host Data
	float * hVx;    // host x-coordinate array
	float * hVy;    // host y-coordinate array
	float * hmin_dist;    // minimum value on host

	// Device Data
	float * dVx;    // device x-coordinate array
	float * dVy;    // device x-coordinate array
	float * dmin_dist;    // minimum value on device

	int i, j, size;    //, num_points, blocks, threads; 
	float dx, dy, Dij, distance;
	unsigned int seed = 0;

	cudaEvent_t start, stop;    // GPU timing variables

	struct timeval cpu_start, cpu_stop;    // CPU timing variables

	float time_array[10];

	// Timing initializations
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	// Check input
	if (argc != 2) {
		printf("Use: %s <number of points>\n", argv[0]);
		exit(0);
	}
	if ((num_points = atoi(argv[argc - 1])) > MAX_POINTS) {
		printf("Maximum number of points allowed: %d\n", MAX_POINTS);
		exit(0);
	}

	// Allocate host coordinate arrays 
	size = num_points * sizeof(float);
	hVx = (float *) malloc(size);
	hVy = (float *) malloc(size);
	hmin_dist = (float *) malloc(size);

	// Initialize points
	for (i = 0; i < num_points; i++) {
		hVx[i] = (float) (rand_r(&seed)) / (float) (RAND_MAX);
		hVy[i] = (float) (rand_r(&seed)) / (float) (RAND_MAX);
	}

	// Allocate device coordinate arrays
	cudaMalloc(&dVx, size);
	cudaMalloc(&dVy, size);
	cudaMalloc(&dmin_dist, sizeof(float));

	// Copy coordinate arrays from host memory to device memory 
	cudaEventRecord(start, 0);

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
	threads = 256;	//16;                       //num_points/blocks;
	blocks = (num_points + threads - 1) / threads;//num_points/threads;       //my_log(num_points);
	minimum_distance<<<4, 128>>>(dVx, dVy, dmin_dist, num_points);
	//minimum_distance<<<, BLOCK_SIZE>>>(dVx, dVy, dmin_dist, num_points);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&(time_array[1]), start, stop);

	// Copy result from device memory to host memory 
	cudaEventRecord(start, 0);

	cudaMemcpy(hmin_dist, dmin_dist, size, cudaMemcpyDeviceToHost);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&(time_array[2]), start, stop);

	printf("Number of Points = %d\n", num_points);
	printf("GPU Host-to-device = %f ms \n", time_array[0]);
	printf("GPU execution time = %f ms \n", time_array[1]);
	printf("GPU Device-to-host = %f ms \n", time_array[2]);
	printf("Minimum distance (GPU) = %e\n", hmin_dist[0]);

	// Compute minimum distance on host to check device computation
	gettimeofday(&cpu_start, NULL);
	dx = hVx[1] - hVx[0];
	dy = hVy[1] - hVy[0];
	distance = sqrtf(dx * dx + dy * dy);
	for (i = 0; i < num_points; i++) {
		for (j = i + 1; j < num_points; j++) {
			dx = hVx[j] - hVx[i];
			dy = hVy[j] - hVy[i];
			Dij = sqrtf(dx * dx + dy * dy);
			if (distance > Dij)
				distance = Dij;
		}
	}
	gettimeofday(&cpu_stop, NULL);
	time_array[3] = 1000 * (cpu_stop.tv_sec - cpu_start.tv_sec)
			+ 0.000001 * (cpu_stop.tv_usec - cpu_start.tv_usec);
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
