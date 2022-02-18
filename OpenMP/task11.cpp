/* Написать программу, в которой, объявить и заполнить случайными значениями массив целых
* чисел. Используя возможности OpenMP, найти максимальное числовое значение элементов массива,
* кратное 7. Длину массива и количество потоков определить самостоятельно. Результат выдать на
* экран. Для синхронизации числовых значений максимума используется механизм критических
* секций.
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>

int main() 
{
    int a[100];

    for (int i = 0; i < 10; i++) {
        a[i] = rand();
    }

    int max = a[0];
    #pragma omp parallel num_threads(6)
    {
        #pragma omp for schedule(dynamic)
        for (int i = 0; i < 10; i++) {
            if (a[i] % 7 == 0) {
                #pragma omp critical
                if (a[i] > max) {
                    max = a[i];
                }   
            }
        }
    }
    printf("max: %d", max);
}