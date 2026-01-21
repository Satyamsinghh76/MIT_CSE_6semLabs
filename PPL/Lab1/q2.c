#include<stdio.h>
#include<mpi.h>
#include<ctype.h>
#include<math.h>

int main(int argc, char *argv[]){
	int rank, size , n=4;
	int ch, a =4,b = 3, res;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	switch(rank){
	case 0 : res = a + b;
		printf("Process %d of %d : %d \n",rank,size,res);
		break;
	case 1 : res = a - b;
		printf("Process %d of %d : %d \n",rank,size,res);
		break;
	case 2 : res = a * b;
		printf("Process %d of %d : %d \n",rank,size,res);
		break;
	case 3 : res = a / b;
		printf("Process %d of %d : %d \n",rank,size,res);
		break;
	default : res = 0;
		printf("Process %d of %d : %d \n",rank,size,res);
	}
	
	MPI_Finalize();
	return 0;
}
