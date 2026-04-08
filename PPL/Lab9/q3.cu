/*Q3. Write a CUDA program that reads a matrix A of size MxN and produce an output matrix B of same size such that it replaces all non-border elements of A with its equivalent 1's complement and remaining elements same as matrix A.
*/
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
__device__ unsigned int get_mask(int n) {
    if (n == 0) return 1;

    unsigned int mask = n;
    mask |= mask >> 1;
    mask |= mask >> 2;
    mask |= mask >> 4;
    mask |= mask >> 8;
    mask |= mask >> 16;

    return mask;
}
__global__ void complementKernel(int *A, int *B, int M, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < M && col < N) {
        int idx = row * N + col;

        if (row == 0 || row == M-1 || col == 0 || col == N-1) {
            B[idx] = A[idx];
        } else {
            int val = A[idx];

            if (val == 0)
                B[idx] = 1;
            else {
                unsigned int mask = get_mask(val);
                B[idx] = val ^ mask;
            }
        }
    }
}

void printBinary(int n) {
    int started = 0;

    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;
        if (bit) started = 1;
        if (started) printf("%d", bit);
    }
    if (!started) printf("0");
}

int main() {
    int M, N;

    printf("Enter M and N: ");
    scanf("%d %d", &M, &N);

    int *A = (int*)malloc(M*N*sizeof(int));
    int *B = (int*)malloc(M*N*sizeof(int));

    printf("Enter matrix elements:\n");
    for (int i = 0; i < M*N; i++)
        scanf("%d", &A[i]);

    int *d_A, *d_B;
    cudaMalloc(&d_A, M*N*sizeof(int));
    cudaMalloc(&d_B, M*N*sizeof(int));

    cudaMemcpy(d_A, A, M*N*sizeof(int), cudaMemcpyHostToDevice);

    dim3 threads(16,16);
    dim3 blocks((N+15)/16, (M+15)/16);

    complementKernel<<<blocks, threads>>>(d_A, d_B, M, N);

    cudaMemcpy(B, d_B, M*N*sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nResult Matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int val = B[i*N+j];

            if (i==0 || i==M-1 || j==0 || j==N-1)
                printf("%d ", val);
            else {
                printf("'");
                printBinary(val);
                printf("' ");
            }
        }
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);
    free(A);
    free(B);

    return 0;
}