/* Написать программу, в которой объявить и присвоить начальные значения массиву целых чисел
* a[30], для инициализации значений использовать генератор случайных чисел. Используя
* конструкции omp parallel for и omp atomic, вычислить количество элементов массива, числовые
* значения которых кратны 9. Количество нитей задать самостоятельно. Результат выдать на экран.
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>

int main()
{
    int a[30];
    for (int i; i < 30; i++) {
        a[i] = rand();
    }

    int count;
    #pragma omp parallel num_threads(6)
    {
        #pragma omp for schedule(dynamic)
        for (int i = 0; i < 30; i++) {
            if (a[i] % 9 == 0) {
                #pragma omp atomic
                count++;
            }
        }
    }
    printf("count: %d", count);
}