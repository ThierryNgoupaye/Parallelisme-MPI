//
// Created by thierry on 27/03/2026.
//


#include <mpi.h>

// Algorithme de commérage
int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int tableau[size];


    for (int i= 0; i<size; i++) {
        MPI_Send(&rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

        MPI_Recv(&tableau[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }


    for (const int value : tableau) {
        std::cout << "P" <<rank << " " << value <<"\n";
    }
    std::cout << std::endl;










    MPI_Finalize();
}
