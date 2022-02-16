/* Написать mpi программу, печатающую "Hello, World!". Запустить программу на
4 процессах.
*/
#include <stdio.h>
#include "mpi.h"
#include <iostream>

int main(int* argc, char** argv)
{
	int numtasks, rank;

	MPI_Init(argc, &argv);

	std::cout << "Hello world!";

	MPI_Finalize();
}