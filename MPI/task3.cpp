/* Написать программу, запустить ее на 2х процессах. На нулевом процессе задать
* массив а из 10 элементов, значения сгенерировать случайным образом.
* Переслать этот массив целиком первому процессу с помощью функции
* MPI_Send. Распечатать на первом процессе принятый массив.
*/
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <iostream>

int main(int* argc, char** argv)
{
	int rank;
	MPI_Status status;
	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {

		int a[10];
		for (int i = 0; i < 10; i++) {
			a[i] = rand();
		}

		MPI_Send(&a[0], 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else {
		int b[10];
		MPI_Recv(&b[0], 10, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		printf("Process %d\n", rank);
		for (int i = 0; i < 10; i++) {
			std::cout << b[i] << " ";
		}
	}

	MPI_Finalize();
}