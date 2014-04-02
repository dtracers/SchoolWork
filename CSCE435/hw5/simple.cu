/*
#include "cuPrintf.cu"
#include <stdio.h>
__global__ void testKernel(int val)
{
  cuPrintf("Value is: %d\n", val);
  printf("output");
}

int main()
{

 // cudaPrintfInit();
  testKernel<<< 2, 3 >>>(10);
  cudaDeviceSynchronize();
  //cudaPrintfDisplay(stdout, true);
  //cudaPrintfEnd();
  return 0;
}
*/
/*
#include "stdio.h"

// printf() is only supported
// for devices of compute capability 2.0 and higher
#if defined(__CUDA_ARCH__) && (__CUDA_ARCH__ < 200)
  # error printf is only supported on devices of compute capability 2.0 and higher, please compile with -arch=sm_20 or higher    
#endif

__global__ void helloCUDA(float f)
{
    printf("Hello thread %d, f=%f\n", threadIdx.x, f);
}

int main()
{
    helloCUDA<<<1, 5>>>(1.2345f);
    cudaDeviceSynchronize();
    return 0;
}

*/

// sample code for the usage of DLog

#include <cuda.h>

#include <iostream>

using namespace std;

#include "DLog.h"

const int numThreads=2;
const int numBlocks=2;

__global__ void foo(){
		DLog<<threadIdx.x;
}

int main(){
		DLog_Init(1024*1024);
		foo<<<numBlocks, numThreads>>>();
		DLog_Dump();
		return 0;
}
