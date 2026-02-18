#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>

__global__ void convolution_1D(float *N, float *M, float *P, 
                               int w, int mw) 
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < w) {
        float sum = 0.0;
        int half_mask = mw / 2;

        for (int j = 0; j < mw; j++) {
            int index = i - half_mask + j;
            if (index >= 0 && index < w) {
                sum += N[index] * M[j];
            }
        }
        P[i] = sum;
    }
}
int main() {
    int N, M; 
    printf("Enter the value of width: \n");
    scanf("%d", &N);
    printf("Enter the value of mask_width: \n");
    scanf("%d", &M);
    float *h_N, *h_M, *h_P;
    float *d_N, *d_M, *d_P;
    int sizeN = N * sizeof(float);
    int sizeM = M * sizeof(float);
    h_N = (float*)malloc(sizeN);
    h_M = (float*)malloc(sizeM);
    h_P = (float*)malloc(sizeN);
    printf("Enter the values for array N :\n");
    for(int i = 0; i < N; i++){
        scanf("%f", &h_N[i]);
    }
    printf("Enter the values for mask array M :\n");
    for(int i = 0; i < M; i++){
        scanf("%f", &h_M[i]);
    }
    cudaMalloc((void**)&d_N, sizeN);
    cudaMalloc((void**)&d_M, sizeM);
    cudaMalloc((void**)&d_P, sizeN);
    cudaMemcpy(d_N, h_N, sizeN, cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, h_M, sizeM, cudaMemcpyHostToDevice);
    dim3 dimblock(256, 1, 1);
    dim3 dimgrid(ceil(N / 256.0), 1, 1);
    convolution_1D<<<dimgrid, dimblock>>>(d_N, d_M, d_P, N, M);
    cudaMemcpy(h_P, d_P, sizeN, cudaMemcpyDeviceToHost);

    printf("Resultant Array P:\n");
    for (int i = 0; i < N; i++) {
        printf("%f ", h_P[i]);
    }
    printf("\n");
    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);
    free(h_N);
    free(h_M);
    free(h_P);
    return 0;
}
