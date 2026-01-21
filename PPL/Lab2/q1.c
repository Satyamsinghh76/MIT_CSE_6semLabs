#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int size, rank;
    char str[100];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* Ensure exactly 2 processes */
    if (size != 2) {
        if (rank == 0)
            printf("This program requires exactly 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        printf("Enter string: ");
        scanf("%99s", str);

        printf("Process %d: Sending string \"%s\"\n", rank, str);
        MPI_Ssend(str, strlen(str) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(str, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);
        printf("Process %d: Received toggled string \"%s\"\n", rank, str);
    }
    else if (rank == 1) {
        MPI_Recv(str, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process %d: Received string \"%s\"\n", rank, str);

        /* Toggle case */
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] += 32;
            else if (str[i] >= 'a' && str[i] <= 'z')
                str[i] -= 32;
        }

        printf("Process %d: Toggled string \"%s\"\n", rank, str);
        MPI_Ssend(str, strlen(str) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
