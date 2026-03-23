//
// Created by thierry on 23/03/2026.
//
// Calcul de la somme des éléments d’un tableau en répartissant le calcul sur tous les processus.


#include <mpi.h>

int main (int argc, char *argv[]) {

    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int data[9] = {1,2,3,4,5,6,7,8,9};
    int residu = 9%size;
    int part = 9/size;
    if (rank ==0) {
        int sum = 0;
        for (int i = 0; i < residu+part; i++) {
            sum += data[i];
        }
    }
    else {

    }




    MPI_Finalize();
    exit(0);


}