#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char **argv){
    int id, np, i,  n, s;
    char msg[100];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    
    n = 2*id;
    /*
    if(id != 0){
        MPI_Send(&n, 1, MPI_INT, 0, 100, MPI_COMM_WORLD);
    } else {
        s = n;
        for(i=1; i<np; i++){
            MPI_Recv(&n, 1, MPI_INT, i, 100, MPI_COMM_WORLD, &status);
            s+=n;
        }
    }

    if(id == 0){
        for(i=1; i<np; i++){
            MPI_Send(&s, 1, MPI_INT, i, 200, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&s, 1, MPI_INT, 0, 200, MPI_COMM_WORLD, &status);
    }
    */

    MPI_Allreduce(&n, &s, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("ID: %d | S=%d\n", id, s);

    MPI_Finalize();
}