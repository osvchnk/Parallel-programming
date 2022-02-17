/* Пусть векторы х, у заданы на нулевом процессе. Написать программу, в которой
* векторы равными блоками с нулевого процесса пересылаются остальным процессам.
* Пересылка данных осуществляется функцией MPI_Send. Все процессы по формуле
* вычисляют свои элементы искомых массивов. Каждый процесс отправляет на нулевой
* процесс подсчитанные элементы массивов. В программе реализовать следующие
* операции вычисления векторов:
*   - z_i = a * x_i + b * y_i;
*	- z_i = x_i * y_i;
*	- Обмен элементов двух векторов x_i <--> y_i;
*/
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <iostream>
#include <string>

//int main(int* argc, char** argv)
//{
//	int rank, size;
//	MPI_Status status;
//	MPI_Init(argc, &argv);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//	int a = 2;
//	int b = 3;
//	int x[100], y[100], z_sum[100], z_multi[100];
//	int range = 100 / (size - 1);
//
//	if (rank == 0) {
//
//		for (int i = 0; i < 100; i++) {
//			x[i] = i;
//			y[i] = i;
//		}
//
//		for (int j = 1; j < size; j++) {
//
//			if (range * (j + 1) > 100) {
//				MPI_Send(&x[range * (j - 1)], 100 - (range * (j - 1)), MPI_INT, j, 0, MPI_COMM_WORLD);
//				MPI_Send(&y[range * (j - 1)], 100 - (range * (j - 1)), MPI_INT, j, 1, MPI_COMM_WORLD);
//			}
//			else {
//				MPI_Send(&x[range * (j - 1)], range, MPI_INT, j, 0, MPI_COMM_WORLD);
//				MPI_Send(&y[range * (j - 1)], range, MPI_INT, j, 1, MPI_COMM_WORLD);
//			}
//		}
//
//		int count_z;
//
//		// sum block
//		MPI_Probe(MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
//		MPI_Get_count(&status, MPI_INT, &count_z);
//
//		int source = status.MPI_SOURCE;
//		int* buf_z = new int[count_z];
//		MPI_Recv(buf_z, count_z, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
//
//		std::string str_z_sum;
//		std::cout << "source : " << source << "\n";
//		for (int i = 0; i < count_z; i++) {
//			z_sum[i + (source - 1) * range] = buf_z[i];
//			str_z_sum += std::to_string(z_sum[i + (source - 1) * range]) + " ";
//		}
//		std::cout << "message sum : " << str_z_sum << "\n";
//
//		// multi block
//		MPI_Probe(MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &status);
//		MPI_Get_count(&status, MPI_INT, &count_z);
//
//		int source = status.MPI_SOURCE;
//		int* buf_z = new int[count_z];
//		MPI_Recv(buf_z, count_z, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &status);
//
//		std::string str_z_multi;
//		std::cout << "source : " << source << "\n";
//		for (int i = 0; i < count_z; i++) {
//			z_multi[i + (source - 1) * range] = buf_z[i];
//			str_z_multi += std::to_string(z_sum[i + (source - 1) * range]) + " ";
//		}
//		std::cout << "message multi : " << str_z_multi << "\n";
//
//	}
//	else {
//		int count;
//
//		MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
//		MPI_Get_count(&status, MPI_INT, &count);
//		int *buf_x = new int[count];
//		MPI_Recv(buf_x, count, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//
//		MPI_Probe(0, 1, MPI_COMM_WORLD, &status);
//		MPI_Get_count(&status, MPI_INT, &count);
//		int* buf_y = new int[count];
//		MPI_Recv(buf_y, count, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
//
//		int* sum = new int[count];
//		int* multi = new int[count];
//		for (int i = 0; i < count; i++) {
//			sum[i] = a * buf_x[i] + b * buf_y[i];
//			multi[i] = buf_x[i] * buf_y[i];
//		}
//
//		// tag=2 - sum
//		// tag=3 - multi
//		MPI_Send(sum, count, MPI_INT, 0, 2, MPI_COMM_WORLD);
//		MPI_Send(multi, count, MPI_INT, 0, 3, MPI_COMM_WORLD);
//	}
//	MPI_Finalize();
//}

int main(int* argc, char** argv)
{
	int rank, size;
	MPI_Status status;
	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int a = 2;
	int b = 3;
	int x[100], y[100], z[100];
	int range = 100 / (size - 1);

	if (rank == 0) {

		for (int i = 0; i < 100; i++) {
			x[i] = i;
			y[i] = i;
		}

		for (int j = 1; j < size; j++) {

			if (range * (j + 1) > 100) {
				MPI_Send(&x[range * (j - 1)], 100 - (range * (j - 1)), MPI_INT, j, 0, MPI_COMM_WORLD);
				MPI_Send(&y[range * (j - 1)], 100 - (range * (j - 1)), MPI_INT, j, 1, MPI_COMM_WORLD);
			}
			else {
				MPI_Send(&x[range * (j - 1)], range, MPI_INT, j, 0, MPI_COMM_WORLD);
				MPI_Send(&y[range * (j - 1)], range, MPI_INT, j, 1, MPI_COMM_WORLD);
			}

		}
		for (int i = 0; i < (size - 1); i++) {
			int count_z;

			MPI_Probe(MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_INT, &count_z);

			int source = status.MPI_SOURCE;
			int* buf_z = new int[count_z];
			MPI_Recv(buf_z, count_z, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);

			std::string str_z;
			std::cout << "source : " << source << "\n";
			for (int i = 0; i < count_z; i++) {
				z[i + (source - 1) * range] = buf_z[i];
				str_z += std::to_string(z[i + (source - 1) * range]) + " ";
			}
			std::cout << "message : " << str_z << "\n";
		}
	}
	else {
		int count;

		MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &count);
		int* buf_x = new int[count];
		MPI_Recv(buf_x, count, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		MPI_Probe(0, 1, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &count);
		int* buf_y = new int[count];
		MPI_Recv(buf_y, count, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

		int* res = new int[count];
		for (int i = 0; i < count; i++) {
			res[i] = a * buf_x[i] + b * buf_y[i];
		}

		MPI_Send(res, count, MPI_INT, 0, 2, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}