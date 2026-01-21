#include<stdio.h>
#include<mpi.h>
int fact(int n){
    if(n==0||n==1) return 1;
    return n*fact(n-1);
}
int main(int argc,char *argv[]){
    int rank,size,N,A[10],B[10],c,i,sum=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0){
        N=size;
        printf("Enter %d values:\n",N);
        for(i=0;i<N;i++){
            scanf("%d",&A[i]);
        }
    }
    MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
    c=fact(c);
    MPI_Gather(&c,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("The result gathered in the root\n");
        for (int i = 0; i < N; i++)
        {
            sum+=B[i];
        }
        printf("The sum :%d",sum);
        
    }
    MPI_Finalize();
    return 0;
}