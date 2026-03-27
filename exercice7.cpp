//
// Created by thierry on 23/03/2026.
//
// Calcul de la somme des éléments d’un tableau en répartissant le calcul sur tous les processus.


#include <mpi.h>

int sum_elements(const int& debut, const int& fin, const int data[]) {
    int sum = 0;
    for (int j = debut; j < fin; j++) {
        sum += data[j];
    }
    return sum;
}




int main (int argc, char *argv[]) {

    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int data[9] = {1,2,3,4,5,6,7,8,9};
    const int residu = 9%size;
    const int part = 9/size;
    constexpr int tag = 10;

    int indice_depart;
    int indice_fin;
    int sum = 0;

    if (rank == 0) {
        indice_depart = 0;
        indice_fin = part + residu;
        sum = ::sum_elements(indice_depart, indice_fin, data);
        for (int i = 1; i<size; i++) {
            int sum_received;
            MPI_Recv(&sum_received, 1, MPI_INT, i,tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Moi processeur 0, j'ai recu " << sum_received << ", de la part du processeur " << i <<"\n";
            sum+=sum_received;
        }
        std::cout << "La somme des élements du tableau est " << sum << std::endl;
    }
    else {
        indice_depart = part*rank + residu;
        indice_fin = indice_depart + part;
        sum = ::sum_elements(indice_depart, indice_fin, data);
        MPI_Send(&sum, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
        std::cout << "Moi processeur  " <<rank <<", j'ai envoyé " << sum << ", au processeur 0" <<std::endl;

    }
    MPI_Finalize();
    exit(0);
}