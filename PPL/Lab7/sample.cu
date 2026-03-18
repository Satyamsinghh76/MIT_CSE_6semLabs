/*
A CUDA program which takes a string as input and determines the number of occurences of a
character ‘a’ in the string. This program uses atomicAdd() function.
*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

__global__ void CUDACount(char* A, unsigned int *d_count){
    int i = threadIdx.x;
    if (A[i] == 'a')
        atomicAdd(d_count,1);
}

int main() {
    char A[N];
    char *d_A;

    unsigned int *count = (unsigned int *) malloc(sizeof(unsigned int));
    unsigned int *d_count;
    unsigned int *result = (unsigned int *) malloc(sizeof( unsigned int));
    
    printf("Enter a string : ");
    
    fgets(A, N, stdin);
    A[strcspn(A, "\n")] = 0;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaError_t error =cudaGetLastError();

    cudaMalloc((void**)&d_A, strlen(A)*sizeof(char));
    cudaMalloc((void**)&d_count, sizeof(unsigned int));

    cudaMemcpy(d_count, count, sizeof(unsigned int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_A, A, strlen(A), cudaMemcpyHostToDevice);

    *count = 0;
    
    if (error != cudaSuccess) 
        printf("CUDA Errorl: %s\n", cudaGetErrorString(error));
    
    cudaEventRecord(start, 0);

    CUDACount<<<1,strlen(A)>>>(d_A,d_count);
    cudaDeviceSynchronize();

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
        
    error = cudaGetLastError();
    if (error != cudaSuccess) 
        printf("CUDA Error2: %s\n", cudaGetErrorString(error));

    float elapsedTime;
    
    cudaEventElapsedTime(&elapsedTime, start, stop);
    cudaMemcpy(result, d_count, sizeof(unsigned int), cudaMemcpyDeviceToHost);
    
    printf("Total occurences of a = %u\n", *result);
    printf("Time Taken = %f\n",elapsedTime);
    
    cudaFree(d_A);
    cudaFree(d_count);
    printf("\n");
    getchar();
    return 0;
}