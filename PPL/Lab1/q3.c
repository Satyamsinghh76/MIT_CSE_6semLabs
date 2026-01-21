#include<stdio.h>
#include<mpi.h>
#include<ctype.h>
#include<math.h>
#include<string.h>

int main(int argc, char *argv[]){
	int rank, size , n=4;
	char s[] = "HELLO";
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank<strlen(s)){
	s[rank] = tolower(s[rank]);
	printf("Process %d of %d : %c \n",rank, size, s[rank]);
	}
	MPI_Finalize();
	return 0;
}
