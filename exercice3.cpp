//
// Created by thierry on 23/03/2026.
//

// Programme de synchronisation entre processeurs

#include <mpi.h>


int main(int argc, char* argv[]) {


    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;


    if (rank == 0) {
        int count = 0;
        while (count != size-1) {
            int recv_message;
            for (int i = 1; i < size; i++) {
                MPI_Recv(&recv_message, 1, MPI_INT, i, 10, MPI_COMM_WORLD, &status);
                if (recv_message == 1) {
                    count++;
                }
            }
            if (count != size-1) {
                std::cout << "En attente de synchronisation";
                count = 0;
            }
            else {
                std::cout << "Tous les processeurs sont okay" << std::endl;
                int send_message = 15;
                for (int j =1 ; j < size; j++) {
                    MPI_Send(&send_message, 1, MPI_INT, j, 10, MPI_COMM_WORLD);
                    std::cout << "Moi processeur "<<rank << ", J'ai envoyé " << send_message << " au du processeur " << j << std::endl;
                }
            }
        }
    }
    else  {
        constexpr int message = 1;
        int rcv_message;
        MPI_Send(&message,1, MPI_INT, 0, 10, MPI_COMM_WORLD);
        if (const int r_status = MPI_Recv(&rcv_message, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status); r_status == 0) {
            std::cout << "Moi processeur "<<rank << ", J'ai recu " << rcv_message << " De la part du processeur 0"<< std::endl;
        }
    }
    MPI_Finalize();
    exit(0);
}