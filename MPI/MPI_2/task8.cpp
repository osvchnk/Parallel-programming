/* Пусть матрицы вещественных чисел A, B заданы на нулевом процессе. Написать
* программу, в которой матрицы равными кусками с нулевого процесса пересылаются
* остальным процессам. Пересылка данных осуществляется функцией MPI_Send. Все
* процессы по формуле вычисляют свои элементы искомых матриц. Каждый процесс
* отправляет на нулевой процесс подсчитанные элементы матриц. В программе
* реализовать следующие операции вычисления матриц:
*		a. C = A * B (C[i][j] = A[i][j] * B[i][j] ) - поэлементное умножение;
*/
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <iostream>
#include <string>

float getRandomNumber()
{
	int max = 100;
	int min = 10;
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return static_cast<float>(rand() * fraction * (max - min + 1) + min);
}

void elem_multi (int* argc, char** argv) {

	const int a_row = 5;
	const int a_col = 7;
	const int b_row = 5;
	const int b_col = 7;

	float a[a_row][a_col];
	float b[b_row][b_col];

	for (int row = 0; row < a_row; row++) {
		for (int col = 0; col < a_col; col++) a[row][col] = getRandomNumber();
	}
	for (int row = 0; row < b_row; row++) {
		for (int col = 0; col < b_col; col++) b[row][col] = getRandomNumber();
	}

	int rank, size;
	MPI_Status status;
	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {

		const int arr_size = sizeof a / sizeof a[0][0];
		float x[arr_size], y[arr_size];
		// 2d array to 1d
		for (int i = 0; i < a_row; i++) {
			for (int j = 0; j < a_col; j++) {
				x[a_col * i + j] = a[i][j];
				y[a_col * i + j] = b[i][j];
			}
		}

		int range = arr_size / (size - 1);
		float result[arr_size];

		// send block
		for (int j = 1; j < size; j++) {

			if (range * (j + 1) > arr_size) {
				MPI_Send(&x[range * (j - 1)], arr_size - (range * (j - 1)), MPI_FLOAT, j, 0, MPI_COMM_WORLD);
				MPI_Send(&y[range * (j - 1)], arr_size - (range * (j - 1)), MPI_FLOAT, j, 1, MPI_COMM_WORLD);
			}
			else {
				MPI_Send(&x[range * (j - 1)], range, MPI_FLOAT, j, 0, MPI_COMM_WORLD);
				MPI_Send(&y[range * (j - 1)], range, MPI_FLOAT, j, 1, MPI_COMM_WORLD);
			}
		}

		// receive block
		for (int i = 0; i < (size - 1); i++) {

			int count_z;

			MPI_Probe(MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_FLOAT, &count_z);
			int source = status.MPI_SOURCE;

			float* buf = new float[count_z];
			MPI_Recv(buf, count_z, MPI_FLOAT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);

			std::string str_result;
			for (int i = 0; i < count_z; i++) {
				result[i + (source - 1) * range] = buf[i];
				str_result += std::to_string(result[i + (source - 1) * range]) + " ";
			}
			std::cout << "from source : " << source << "\n";
			std::cout << "count : " << count_z << "\n";
			std::cout << "message result : " << str_result << "\n";
		}
	}
	else {
		int count;

		MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_FLOAT, &count);
		float* buf_x = new float[count];
		MPI_Recv(buf_x, count, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);

		MPI_Probe(0, 1, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_FLOAT, &count);
		float* buf_y = new float[count];
		MPI_Recv(buf_y, count, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);

		float* multi = new float[count];
		for (int i = 0; i < count; i++) {
			multi[i] = buf_x[i] * buf_y[i];
		}

		MPI_Send(multi, count, MPI_FLOAT, 0, 2, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}

int main(int* argc, char** argv)
{
	elem_multi(argc, argv);
}