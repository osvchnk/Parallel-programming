/* Написать программу и запустить ее на p (= 2, 3, 4, 6, 8) процессах. На нулевом
* процессе объявить и задать массив из 12 элементов. С помощью функции
* MPI_Send разослать блоки массива на остальные процессы. Размер блока
* массива (12/p)+1. В результате на нулевом процессе должны быть элементы
* массива с 0 до 12/p, на первом процессе с 12/p+1 до 2×(12/p), на 3м процессе с
* 2×(12/p)+1 до 3×(12/p) и т.д. Вывести элементы массива на экран на каждом
* процессе. ​Обратите внимание, что не на все процессы хватит элементов​.
*/
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <iostream>
#include <string>

int main(int* argc, char** argv)
{
	int rank, size;
	MPI_Status status;
	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int range = 12 / size;
	if (rank == 0) {

		int a[12];
		for (int i = 0; i < 12; i++) {
			a[i] = i;
		}

		for (int j = 1; j < size; j++) {

			if (range * (j + 1) + 1 >= 12) {
				MPI_Send(&a[range * j + 1], 12 - (range * j + 1), MPI_INT, j, 0, MPI_COMM_WORLD);
			}
			else {
				MPI_Send(&a[range * j + 1], range, MPI_INT, j, 0, MPI_COMM_WORLD);
			}
		}

		std::string str;
		for (int i = 0; i < range + 1; i++) {
			str += std::to_string(a[i]) + " ";
		}
		std::cout << "Process: " << rank << " Message: " << str;
	}
	else {
		int count;

		MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &count);

		int *buf = new int[count];
		MPI_Recv(buf, count, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		std::string str;
		for (int i = 0; i < count; i++) {
			str += std::to_string(buf[i]) + " ";
		}
		std::cout << "Process: " << rank << " Message: " << str;
	}
	MPI_Finalize();
}