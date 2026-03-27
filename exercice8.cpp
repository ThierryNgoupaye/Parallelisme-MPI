//
// Created by thierry on 27/03/2026.
//

// Calcul de la somme des éléments d’un tableau en répartissant le calcul sur tous les processus (autre méthode).


#include <mpi.h>
#include <iostream>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    const int data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    constexpr int n = 9;
    const int part    = n / size;
    const int residu  = n % size;


    int debut, fin;
    if (rank == 0) {
        debut = 0;
        fin   = part + residu;
    } else {
        debut = part * rank + residu;
        fin   = debut + part;
    }
    int sum = 0;
    for (int i = debut; i < fin; i++) {
        sum += data[i];
    }

    for (int step = 1; step < size; step *= 2) {
        constexpr int tag = 10;
        if (rank % (2 * step) == step) {
            MPI_Send(&sum, 1, MPI_INT, rank - step, tag, MPI_COMM_WORLD);
            std::cout << "P" << rank << " envoie " << sum<< " à P" << (rank - step) << "\n";
            break;
        }
        if (rank % (2 * step) == 0) {
            if (rank + step < size) {
                int received;
                MPI_Recv(&received, 1, MPI_INT, rank + step, tag,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                sum += received;
                std::cout << "P" << rank << " reçoit " << received<< " de P" << (rank + step)<< " → somme partielle = " << sum << "\n";
            }
        }
    }
    if (rank == 0) {
        std::cout << "\nSomme totale = " << sum << std::endl;
    }
    MPI_Finalize();
    return 0;
}
