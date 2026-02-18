#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>

__global__ void selesort(int *A, int *O, int n)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < n)
    {
        int pos = 0;
        int data = A[tid];
        for (int i = 0; i < n; i++)
        {
            if (A[i] < data || (A[i] == data && i < tid))
            {
                pos++;
            }
        }
        O[pos] = data;
    }
}
int main()
{
    int N;
    printf("Enter the value of size:\n");
    scanf("%d", &N);
    int *h_N, *h_M;
    int *d_N, *d_M;
    int sizeN = N * sizeof(int);

    h_N = (int *)malloc(sizeN);
    h_M = (int *)malloc(sizeN);
    printf("Enter the values for array N:\n");
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &h_N[i]);
    }
    cudaMalloc((void **)&d_N, sizeN);
    cudaMalloc((void **)&d_M, sizeN);
    cudaMemcpy(d_N, h_N, sizeN, cudaMemcpyHostToDevice);
    dim3 dimblock(256, 1, 1);
    dim3 dimgrid((int)ceil((float)N / 256), 1, 1);
    selesort<<<dimgrid, dimblock>>>(d_N, d_M, N);
    cudaMemcpy(h_M, d_M, sizeN, cudaMemcpyDeviceToHost);
    printf("Sorted Array:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", h_M[i]);
    }
    printf("\n");
    cudaFree(d_N);
    cudaFree(d_M);
    free(h_N);
    free(h_M);
    return 0;
}
