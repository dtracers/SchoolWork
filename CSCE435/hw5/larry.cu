//
// CUDA code to compute minimu distance between n points
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MAX_POINTS 1048576
#define BLOCK_SIZE 1024

// ---------------------------------------------------------------------------- 
// Kernel Function to compute distance between all pairs of points
// Input: 
//	X: X[i] = x-coordinate of the ith point
//	Y: Y[i] = y-coordinate of the ith point
//	n: number of points
//
// Output: 
//	D: D[0] = minimum distance
//
__global__ void minimum_distance(float * X, float * Y, float * D, float * M,
		int n) {
	unsigned int i = ((blockIdx.x * blockDim.x) + threadIdx.x);
	int j = 0;
	if (i < n) {
		float x_main = X[i], y_main = Y[i];
		float x_comparison = X[i + 1], y_comparison = Y[i + 1];
		float squaredx = (x_comparison - x_main);
		float squaredy = (y_comparison - y_main);
		D[i] = sqrtf(squaredx * squaredx + squaredy * squaredy);

		for (j = i + 1; j < n; j++) {
			x_comparison = X[j];
			y_comparison = Y[j];
			float squaredx = (x_comparison - x_main);
			float squaredy = (y_comparison - y_main);
			float distance = sqrtf(squaredx * squaredx + squaredy * squaredy);
			if (distance < D[i])
				D[i] = distance;
		}
	}
	__syncthreads();
	if (i < blockDim.x) {
		int tid = threadIdx.x;
		int change = n / blockDim.x;
		float sdata = D[tid * change];
		for (j = 1; j < change; j++) {
			if (sdata > D[(tid * change) + j])
				sdata = D[(tid * change) + j];
		}
		__syncthreads();
		D[tid] = sdata;
		// do reduction in shared mem
		for (unsigned int s = 1; s < blockDim.x; s *= 2) {
			__syncthreads();
			if (tid % (2 * s) == 0) {
				if (D[tid] > D[tid + s])
					D[tid] = D[tid + s];
			}
			__syncthreads();
		}

		// write result for this block to global mem
		if (i == 0)
			*M = X[0];
	}

}
// ---------------------------------------------------------------------------- 
// Main program - initializes points and computes minimum distance 
// between the points
//
int main(int argc, char* argv[]) {

	// Host Data
	float * hVx;                // host x-coordinate array
	float * hVy;                // host y-coordinate array
	float * hmin_dist;          // minimum value on host

	// Device Data
	float * dVx;                // device x-coordinate array
	float * dVy;                // device x-coordinate array
	float * dmin_dist;          // minimum value on device
	float * dVd;

	int i, j, size, num_points;
	float dx, dy, Dij, distance;
	unsigned int seed = 0;

	cudaEvent_t start, stop;            // GPU timing variables

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
	if ((num_points = atoi(argv[argc - 1])) > MAX_POINTS) {
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
		hVx[i] = (float) (rand_r(&seed)) / (float) (RAND_MAX);
		hVy[i] = (float) (rand_r(&seed)) / (float) (RAND_MAX);
	}

	// Allocate device coordinate arrays
	cudaMalloc(&dVx, size);
	cudaMalloc(&dVy, size);
	cudaMalloc(&dmin_dist, sizeof(float));
	//cudaMalloc(&dVd,size);
	// Copy coordinate arrays from host memory to device memory
	cudaEventRecord(start, 0);

	cudaMemcpy(dVx, hVx, size, cudaMemcpyHostToDevice);
	cudaMemcpy(dVy, hVy, size, cudaMemcpyHostToDevice);

	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&(time_array[0]), start, stop);

	// Invoke kernel
	cudaEventRecord(start, 0);

	minimum_distance<<<1, 16>>>(dVx, dVy, dVd, dmin_dist, num_points);

	// ------------------------------------------------------------
	/* Define block size */
	//threads = 16;
	//blocks = (num_points/threads);
	/* Invoke kernel */

	// ------------------------------------------------------------
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&(time_array[1]), start, stop);

	// Copy result from device memory to host memory
	cudaEventRecord(start, 0);

	cudaMemcpy(hmin_dist, dmin_dist, sizeof(float), cudaMemcpyDeviceToHost);

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
