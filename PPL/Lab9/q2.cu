/*Q2. Write a program in CUDA to read MxN matrix A and replace 1st row of this matrix by same elements, 2nd row elements by square of each element, 3rd row elements by cube of each element and so on.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>

// Kernel
__global__ void transformMatrix(int *A, int M, int N) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    if (row < M && col < N) {
        int idx = row * N + col;
        A[idx] = pow(A[idx], row + 1);
    }
}

int main() {
    int M, N;

    printf("Enter M and N: ");
    scanf("%d %d", &M, &N);

    int *A = (int*)malloc(M * N * sizeof(int));

    printf("Enter matrix elements:\n");
    for (int i = 0; i < M*N; i++)
        scanf("%d", &A[i]);

    int *d_A;
    cudaMalloc(&d_A, M*N*sizeof(int));
    cudaMemcpy(d_A, A, M*N*sizeof(int), cudaMemcpyHostToDevice);

    dim3 threads(16,16);
    dim3 blocks((N+15)/16, (M+15)/16);

    transformMatrix<<<blocks, threads>>>(d_A, M, N);

    cudaMemcpy(A, d_A, M*N*sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nTransformed Matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", A[i*N+j]);
        printf("\n");
    }

    cudaFree(d_A);
    free(A);

    return 0;
}
/*
Enter number of rows (M): 4
Enter number of columns (N): 3
Enter the elements of the 4x3 matrix:
Element [0][0]: 1
Element [0][1]: 2
Element [0][2]: 3
Element [1][0]: 4
Element [1][1]: 5
Element [1][2]: 6
Element [2][0]: 7
Element [2][1]: 8
Element [2][2]: 9
Element [3][0]: 1
Element [3][1]: 2
Element [3][2]: 3

Transformed Matrix:
1 2 3 
16 24 36 
343 512 729 
1 16 81 
*/
