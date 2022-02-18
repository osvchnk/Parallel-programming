/* Написать программу, в которой объявить и присвоить начальные значения элементам двумерного
* массива d[6][8], для инициализации значений использовать генератор случайных чисел. Используя
* конструкцию директив omp parallel for и omp critical, определить минимальное и максимальное
* значения элементов двумерного массива. Количество нитей задать самостоятельно. Результат выдать
* на экран.
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>

int main() 
{
    int d[6][8];

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            d[i][j] = rand();
        }
    }

    int min = d[0][0];
    int max = d[0][0];

    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(dynamic)
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                #pragma omp critical
                if (min > d[i][j]) {
                    min = d[i][j];
                }
            }
        }

        #pragma omp for schedule(dynamic)
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                #pragma omp critical
                if (max < d[i][j]) {
                    max = d[i][j];
                }
            }
        }
    }
    printf("max: %d\nmin: %d", max, min);
}