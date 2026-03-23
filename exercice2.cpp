//
// Created by thierry on 23/03/2026.
//

#include <mpi/mpi.h>


int main(int argc, char* argv[]) {

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    constexpr int message = 10;
    constexpr int tag = 10;
    for (int i = 1; i < 10; i++) {
        if (rank == 0) {
            int message_recu;
            MPI_Send(&message, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
            MPI_Recv(&message_recu, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
            std::cout << "Moi processeur " << rank+1  <<", J'ai envoyé " << message << " au processeur 2 "<< " (" << i <<"er/eme fois) ";
            std::cout << "Moi processeur "<< rank+1 << ", J'ai recu " << message << " du processeur 2" << " (" << i <<"er/eme fois) " << std::endl;
        }
        else if (rank == 1) {
            int message_recu;
            MPI_Recv(&message_recu, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
            MPI_Send(&message_recu, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);

            std::cout << "Moi processeur " << rank+1  <<", J'ai envoyé " << message_recu << " au processeur 1 "<< " (" << i <<"er/eme fois) ";
            std::cout << "Moi processeur "<< rank+1 << ", J'ai recu " << message_recu << " du processeur 1" << " (" << i <<"er/eme fois) " << std::endl;
        }

    }

    MPI_Finalize();
}