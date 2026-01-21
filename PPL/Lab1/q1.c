#include<stdio.h>
#include<mpi.h>
#include<ctype.h>
#include<math.h>

int main(int argc, char *argv[]){
	int rank, size , n=4;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int res = pow(n,rank);
	if(rank%2==0){
	printf("process %d of %d : Hello \n",rank,size);
	}else{
	printf("process %d of %d : World \n",rank,size);
	}
	//printf("Process %d of %d : %d \n",rank,size,res);
	MPI_Finalize();
	return 0;
}
