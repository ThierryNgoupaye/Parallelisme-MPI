//
// Created by thierry on 19/03/2026.
// Exercice 1
//

#include <mpi.h>


// Programme d'envoi de N valeurs entre le processus 0 et le processus 1
int main (int argc, char* argv[]) {

    int rank, size;
    constexpr int tab_size = 1000000;
    int values[tab_size];
    for (int i =0; i<tab_size; ++i) {
        values[i] = i;
    }
    constexpr int tag =1;
    MPI_Status status;
    const double debut_algorithme_1_time = MPI_Wtime();
    const double debut_algorithme_2_time  = MPI_Wtime();


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    // 1ᵉre version en envoyant tout le tableau au processus 1
    if (rank == 0) {
        MPI_Send(values, tab_size, MPI_INT, 1, tag, MPI_COMM_WORLD);
        std::cout << "Moi processeur " << rank << " J'ai envoyé ";
        for (const int value : values) {
            std::cout << value <<", ";
        }
        std::cout << " Au processeur 1" <<std::endl;
    }
    else if (rank == 1) {
        int tab[tab_size];
        MPI_Recv(tab, tab_size, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        std::cout << "Moi processeur " << rank << " J'ai recu ";
        for (const int value : tab) {
            std::cout << value <<", ";
        }
        std::cout << " du processeur 0" <<std::endl;
        const double fin_algorithme_1_time = MPI_Wtime();
        std::cout << "P1: Temps écoulé de la version 1: " << fin_algorithme_1_time-debut_algorithme_1_time <<" s"  <<std::endl;
    }



    // 2e version en envoyant valeur par valeur du processus 2 vers le processus 3
    else if (rank == 2) {
        for (const int value : values) {
            MPI_Send(&value, 1, MPI_INT, 3, tag, MPI_COMM_WORLD);
        }
        std::cout << "Moi processeur " << rank << " J'ai envoyé ";
        for (const int value : values) {
            std::cout << value <<", ";
        }
        std::cout << " au processeur 3" <<std::endl;
        MPI_Wtime();
    }
    else if (rank == 3) {
        int tabl_recv[tab_size];
        for (int& value : tabl_recv) {
            MPI_Recv(&value, 1, MPI_INT, 2, tag, MPI_COMM_WORLD, &status);
        }
        std::cout << "Moi processeur " << rank << " J'ai recu ";
        for (const int value : tabl_recv) {
            std::cout << value <<", ";
        }
        std::cout << " du processeur 2" <<std::endl;
        const double fin_algorithme_2_time = MPI_Wtime();
        std::cout << "P3: Temps écoulé de la version 2: " << fin_algorithme_2_time-debut_algorithme_2_time <<" s" <<std::endl;
    }
    MPI_Finalize();
    exit(0);
}