/*
A CUDA program that reads a string S and produces RS such that
each thread copies decreasing number of characters from S.
*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <string.h>

#define N 1024

__global__ void buildString(char *S, char *RS, int len) {
    int i = threadIdx.x;

    if (i < len) {
        int start = 0;

        // Calculate starting index in RS
        for (int k = 0; k < i; k++) {
            start += (len - k);
        }

        // Copy (len - i) characters
        for (int j = 0; j < (len - i); j++) {
            RS[start + j] = S[j];
        }
    }
}

int main() {
    char S[N];
    char *d_S, *d_RS;

    printf("Enter a string: ");
    fgets(S, N, stdin);
    S[strcspn(S, "\n")] = 0;

    int len = strlen(S);

    // Total size of RS = len + (len-1) + ... + 1
    int totalLen = len * (len + 1) / 2;

    char *RS = (char*) malloc(totalLen + 1);

    cudaMalloc((void**)&d_S, len * sizeof(char));
    cudaMalloc((void**)&d_RS, totalLen * sizeof(char));

    cudaMemcpy(d_S, S, len, cudaMemcpyHostToDevice);

    buildString<<<1, len>>>(d_S, d_RS, len);
    cudaDeviceSynchronize();

    cudaMemcpy(RS, d_RS, totalLen, cudaMemcpyDeviceToHost);

    RS[totalLen] = '\0';

    printf("Output string RS: %s\n", RS);

    cudaFree(d_S);
    cudaFree(d_RS);
    free(RS);

    return 0;
}