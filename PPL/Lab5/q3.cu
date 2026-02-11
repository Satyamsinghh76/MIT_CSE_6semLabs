#include<stdio.h>
#include"cuda_runtime.h"
#include"device_launch_parameters.h"
__global__ void computeSine(float *A, float *B, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
        B[i] = sinf(A[i]);
}

int main()
{
    int N;  
    printf("Enter the value of N: \n");
    scanf("%d",&N);
    float *h_A, *h_B;
    float *d_A, *d_B;
    int size = N * sizeof(float);
    h_A = (float*)malloc(size);
    h_B = (float*)malloc(size);
    printf("Enter the values for vector A:\n");
    for(int i = 0;i<N;i++){
        scanf("%f",&h_A[i]);
    }
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    computeSine<<<ceil(N/256.0),256>>>(d_A, d_B, N);
    cudaMemcpy(h_B, d_B, size, cudaMemcpyDeviceToHost);
    printf("angle(radian)        Sine \n");
    for (int i = 0; i < N; i++)
        printf("%f          %f \n", h_A[i],h_B[i]);
    printf("\n");
    free(h_A);
    free(h_B);
    cudaFree(d_A);
    cudaFree(d_B);
    return 0;
}
