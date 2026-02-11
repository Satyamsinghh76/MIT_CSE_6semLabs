#include<stdio.h>
#include"cuda_runtime.h"
#include"device_launch_parameters.h"
// Kernel
__global__ void vectorAdd(float *A, float *B, float *C, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
        C[i] = A[i] + B[i];
}
int main()
{
    int N; 
    printf("Enter the value of N: \n");
    scanf("%d",&N);
    float *h_A, *h_B, *h_C;
    float *d_A, *d_B, *d_C;
    int size = N * sizeof(float);
    h_A = (float*)malloc(size);
    h_B = (float*)malloc(size);
    h_C = (float*)malloc(size);
    printf("Enter the values for vector A:\n");
    for(int i = 0;i<N;i++){
        scanf("%f",&h_A[i]);
    }
    printf("Enter the values for vector B:\n");
    for(int i = 0;i<N;i++){
        scanf("%f",&h_B[i]);
    }
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);
    vectorAdd<<<ceil(N/256.0), 256>>>(d_A, d_B, d_C, N);
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
    printf("Results:\n");
    for (int i = 0; i < N; i++)
        printf("%f ", h_C[i]);
    printf("\n");
    free(h_A);
    free(h_B);
    free(h_C);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
