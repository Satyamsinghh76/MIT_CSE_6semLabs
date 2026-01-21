#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc , char * argv[]){
    int rank,size;
    char str[100];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;
    if(rank==0){
        printf("Enter the word: ");
        scanf("%s",str);
        printf("Process: %d Sending word: %s \n",rank,str);
        MPI_Ssend(&str,sizeof(str),MPI_CHAR,1,0,MPI_COMM_WORLD);
        MPI_Recv(&str,sizeof(str),MPI_CHAR,1,1,MPI_COMM_WORLD,&status);
    	printf("Process %d: Received string %s\n",rank, str);


    }else{
        MPI_Recv(&str,sizeof(str),MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
        printf("Process: %d Received word: %s \n",rank,str);
        for(int i = 0;i<strlen(str);i++){
            if(str[i]>='A' && str[i]<='Z') str[i] += 32;
            else if(str[i]>='a' && str[i]<='z') str[i] -= 32;
        }
        printf("Process: %d Toggled string %s \n",rank,str);
        printf("Process: %d Sending String %s \n",rank,str);
        MPI_Ssend(&str,sizeof(str),MPI_CHAR,0,1,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}