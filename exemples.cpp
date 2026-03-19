//
// Created by thierry on 19/03/2026.
//


#include "mpi.h"


void example1(int& argc, char* argv[]) {
    int rank, nb_proc;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
    std::cout <<"Je suis le processeur " <<rank << " parmi " << nb_proc <<std::endl;
    MPI_Finalize();
}



void example2(int& argc, char* argv[]) {
    int rank, nb_proc, i;
    MPI_Status status;
    int valeur = 1000;
    constexpr int tag = 100;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
    if (rank == 0) {
        MPI_Send(&valeur,1,MPI_INT, 1,tag, MPI_COMM_WORLD);
        std::cout << "Moi processeur "<< rank << " J'ai envoyé "  << valeur  << " au processeur 1 \n" << std::endl;
    }
    else if (rank == 1) {
        MPI_Recv(&valeur,1,MPI_INT,0, tag, MPI_COMM_WORLD, &status);
        std::cout << "Moi processeur "<< rank << " J'ai recu "  << valeur  << " du processeur 0 \n" << std::endl;
    }

    MPI_Finalize();
}

int main (int argc, char* argv[]) {
    //example1(argc, argv);
    example2(argc, argv);
    exit(0);
}










