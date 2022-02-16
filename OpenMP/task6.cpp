/* Написать программу, в которой объявить и присвоить начальные значения целочисленным
* массивам a[10] и b[10]. Используя конструкцию parallel for и reduction, вычислить средние
* арифметические значения элементов массивов a и b, сравнить полученные значения, результат
* выдать на экран.
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>

int main()
{
    int a[10];
    int b[10];

    std::cout << "Enter a[10]: ";
    for (int i = 0; i < 10; i++) {
        std::cin >> a[i];
    }

    std::cout << "Enter b[10]: ";
    for (int i = 0; i < 10; i++) {
        std::cin >> b[i];
    }

    int sum_a = 0;
    int sum_b = 0;
    // double average_a;
    float average_b;
    float average_a;
    #pragma omp parallel shared(sum_a, sum_b, average_a, average_b)
    {
        #pragma omp for reduction(+ : sum_a)
        for (int i = 0; i < 10; i++) {
            sum_a += a[i];
        }
        average_a = (float) sum_a / 10;

        #pragma omp for reduction(+ : sum_b)
        for (int i = 0; i < 10; i++) {
            sum_b += b[i];
        }
        average_b = (float)sum_b / 10;
    }
    printf("Average of a[10]: %f\n", average_a);
    printf("Average of b[10]: %f\n", average_b);
}