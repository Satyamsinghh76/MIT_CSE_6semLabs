#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
__global__ void csrSpmvKernel(int numRows, int *rowPtr, int *colIdx,
                             int *values, int *x, int *y) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < numRows) {
        int sum = 0;
        for (int j = rowPtr[row]; j < rowPtr[row + 1]; j++) {
            sum += values[j] * x[colIdx[j]];
        }
        y[row] = sum;
    }
}

int main() {
    int N, nnz;

    printf("Enter matrix size N: ");
    scanf("%d", &N);

    printf("Enter number of non-zero elements: ");
    scanf("%d", &nnz);

    int *rowInd = (int*)malloc(nnz * sizeof(int));
    int *colInd = (int*)malloc(nnz * sizeof(int));
    int *val = (int*)malloc(nnz * sizeof(int));

    printf("Enter row col value (0-based indexing):\n");
    for (int i = 0; i < nnz; i++) {
        scanf("%d %d %d", &rowInd[i], &colInd[i], &val[i]);
    }

    int *rowPtr = (int*)calloc(N + 1, sizeof(int));
    int *colIdx = (int*)malloc(nnz * sizeof(int));
    int *values = (int*)malloc(nnz * sizeof(int));

    // Build rowPtr
    for (int i = 0; i < nnz; i++)
        rowPtr[rowInd[i] + 1]++;

    for (int i = 0; i < N; i++)
        rowPtr[i + 1] += rowPtr[i];

    int *temp = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        temp[i] = rowPtr[i];

    // Fill colIdx & values
    for (int i = 0; i < nnz; i++) {
        int r = rowInd[i];
        int pos = temp[r];
        colIdx[pos] = colInd[i];
        values[pos] = val[i];
        temp[r]++;
    }

    free(temp);

    int *x = (int*)malloc(N * sizeof(int));
    printf("Enter vector x:\n");
    for (int i = 0; i < N; i++)
        scanf("%d", &x[i]);

    int *y = (int*)calloc(N, sizeof(int));

    // Device memory
    int *d_rowPtr, *d_colIdx, *d_values, *d_x, *d_y;

    cudaMalloc(&d_rowPtr, (N + 1) * sizeof(int));
    cudaMalloc(&d_colIdx, nnz * sizeof(int));
    cudaMalloc(&d_values, nnz * sizeof(int));
    cudaMalloc(&d_x, N * sizeof(int));
    cudaMalloc(&d_y, N * sizeof(int));

    cudaMemcpy(d_rowPtr, rowPtr, (N + 1) * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_colIdx, colIdx, nnz * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_values, values, nnz * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, N * sizeof(int), cudaMemcpyHostToDevice);

    csrSpmvKernel<<<(N+255)/256, 256>>>(N, d_rowPtr, d_colIdx, d_values, d_x, d_y);

    cudaMemcpy(y, d_y, N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nResult vector y:\n");
    for (int i = 0; i < N; i++)
        printf("%d\n", y[i]);
    free(rowInd); free(colInd); free(val);
    free(rowPtr); free(colIdx); free(values);
    free(x); free(y);

    cudaFree(d_rowPtr); cudaFree(d_colIdx);
    cudaFree(d_values); cudaFree(d_x); cudaFree(d_y);

    return 0;
}