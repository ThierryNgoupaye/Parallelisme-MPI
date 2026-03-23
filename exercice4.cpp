//
// Created by thierry on 23/03/2026.
//

#include <mpi.h>


#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    int message;

    const int left  = (rank - 1 + size) % size;
    const int right = (rank + 1) % size;

    if (rank == 0) {
        message = 42;
        MPI_Send(&message, 1, MPI_INT, right, 10, MPI_COMM_WORLD);
        MPI_Send(&message, 1, MPI_INT, left,  10, MPI_COMM_WORLD);
        std::cout << "Moi processus j'ai diffusé " << message << std::endl;
    } else {
        const int from = (rank <= size / 2) ? left : right;
        MPI_Recv(&message, 1, MPI_INT, from, 10, MPI_COMM_WORLD, &status);
        std::cout << "Processus " << rank << " a reçu " << message << std::endl;
        if (const int to = (rank <= size / 2) ? right : left; to != 0) {
            MPI_Send(&message, 1, MPI_INT, to, 10, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
}