/* Написать программу, в которой объявить и присвоить начальные значения целочисленным
* массивам a[10] и b[10], определить параллельную область, количество нитей задать равным 2,
* выделить код для основной нити (номер 0) и нити с номером 1. 
* Основная нить должна выполнять поиск min значения элементов массива a, 
* нить с номером 1 - поиск max значения элементов массива b. Результат выдать на экран.
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>

int main()
{
    int a[10];
    int b[10];

    std::cout << "Enter a[10]: ";
    for (int i = 0; i < 10; i++) 
    {
        std::cin >> a[i];
    }

    std::cout << "Enter b[10]: ";
    for (int i = 0; i < 10; i++) 
    {
        std::cin >> b[i];
    }

    #pragma omp parallel num_threads(2)
    {
        #pragma omp master
        {
            printf("Thread %d\n", omp_get_thread_num());
            int a_min = a[0];
            for (int i = 1; i < 10; i++) {
                if (a[i] < a_min) {
                    a_min = a[i];
                }
            }
            printf("a_min=%d\n", a_min);
        }
        #pragma omp single
        {
            printf("Thread %d\n", omp_get_thread_num());
            int b_max;
            for (int i = 1; i < 10; i++) {
                if (b[i] > b_max) {
                    b_max = b[i];
                }
            }
            printf("b_max=%d\n", b_max);
        }
    }
}
