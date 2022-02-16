/* Написать программу, в которой объявить и присвоить начальные значения элементам двумерного
* массива d[6][8], для инициализации значений использовать генератор случайных чисел. Используя
* конструкцию директивы sections...section, определить три секции для выполнения следующих
* операций:
*   - первая секция выполняет вычисление среднего арифметического значения элементов
*   двумерного массива,
*   - вторая секция выполняет вычисление минимального и максимального значений элементов
*   двумерного массива,
*   - третья секция выполняет вычисление количества элементов массива, числовые значения
*   которых кратны 3.
* В каждой секции определить и выдать на экран номер исполняющей нити и результат выполнения
* вычислений.
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>

int main() {
    int d[6][8];

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j <8; j++) {
            d[i][j] = rand();
        }
    }
    std::cout << "Array:\n";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << d[i][j] << " ";
        }
        std::cout << "\n";
    }

    omp_set_num_threads(8);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int sum = 0;
            int count = 0;
            double average; 
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    sum += d[i][j];
                    count += 1;
                }
                average = (double)sum / count;
            }
            printf("Thread %d\nAverage: %f\n", omp_get_thread_num(), average);
        }

        #pragma omp section
        {
            int d_min = d[0][0];
            int d_max = d[0][0];
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    if (d[i][j] < d_min) {
                        d_min = d[i][j];
                    }
                    if (d[i][j] > d_max) {
                        d_max = d[i][j];
                    }
                }
            }
            printf("Thread %d\nmin: %d\nmax: %d\n", omp_get_thread_num(), d_min, d_max);
        }

        #pragma omp section
        {
            int count = 0;
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    if (d[i][j] % 3 == 0) {
                        count += 1;
                    }
                }
            }
            printf("Thread %d\nMultiple of 3: %d\n", omp_get_thread_num(), count);
        }
    }
}