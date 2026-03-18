/*
A CUDA program which takes a string as input and determines the number of 
occurrences of a word in the string. This program uses atomicAdd() function.
*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

__global__ void CUDACountWord(char* A, char* word, unsigned int *d_count, int strLen, int wordLen){
    int i = threadIdx.x;

    if (i <= strLen - wordLen) {
        int match = 1;

        for (int j = 0; j < wordLen; j++) {
            if (A[i + j] != word[j]) {
                match = 0;
                break;
            }
        }

        if (match) {
            atomicAdd(d_count, 1);
        }
    }
}

int main() {
    char A[N], word[50];
    char *d_A, *d_word;

    unsigned int *count = (unsigned int *) malloc(sizeof(unsigned int));
    unsigned int *d_count;
    unsigned int *result = (unsigned int *) malloc(sizeof(unsigned int));

    printf("Enter a string : ");
    fgets(A, N, stdin);
    A[strcspn(A, "\n")] = 0;

    printf("Enter word to search : ");
    fgets(word, 50, stdin);
    word[strcspn(word, "\n")] = 0;

    int strLen = strlen(A);
    int wordLen = strlen(word);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaMalloc((void**)&d_A, strLen * sizeof(char));
    cudaMalloc((void**)&d_word, wordLen * sizeof(char));
    cudaMalloc((void**)&d_count, sizeof(unsigned int));

    *count = 0;

    cudaMemcpy(d_count, count, sizeof(unsigned int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_A, A, strLen, cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, wordLen, cudaMemcpyHostToDevice);

    cudaEventRecord(start, 0);

    CUDACountWord<<<1, strLen>>>(d_A, d_word, d_count, strLen, wordLen);
    cudaDeviceSynchronize();

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime, start, stop);

    cudaMemcpy(result, d_count, sizeof(unsigned int), cudaMemcpyDeviceToHost);

    printf("Total occurrences of \"%s\" = %u\n", word, *result);
    printf("Time Taken = %f ms\n", elapsedTime);

    cudaFree(d_A);
    cudaFree(d_word);
    cudaFree(d_count);

    printf("\n");
    getchar();
    return 0;
}