#include<stdio.h>
#include<mpi.h>
#include<ctype.h>
#include<math.h>

int main(int argc, char *argv[]){
	int rank, size , n;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	printf("Process %d of %d : Hello World \n",rank,size);
	MPI_Finalize();
	return 0;
}
