#include<stdio.h>
#include<mpi.h>
#include<ctype.h>
#include<math.h>
int fact(int a){
	int res = 1;
	while(a!=0){
	res = res * a;
	a--;
	}
	return res;
}
int fib(int a){
	if(a==2 || a == 1) return 1;
	return fib(a-1) + fib(a-2);	
	}
int main(int argc, char *argv[]){
	int rank, size , n=4;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank%2 == 0){
		printf("Process %d of %d : %d \n",rank, size, fact(rank));	
	}else{
		printf("Process %d of %d : %d \n",rank, size, fib(rank));
	}
	MPI_Finalize();
	return 0;
}
