/* Написать программу, в которой, используя возможности OpenMP, найти все простые числа в
* заданном с клавиатуры диапазоне. Количество потоков определить самостоятельно. Результат выдать
* на экран.
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>

int main() {
    int start;
    int end;
    bool flag = true;

    std::cin >> start >> end;
    #pragma omp parallel
    {
        #pragma omp for firstprivate(flag)
        for (int i = start; i <= end; i++) {
            for (int j = 2; j < i; j++) {
                if (i % j == 0) {
                    flag = false;
                }
            }
            if (flag) {
                std::cout << i << " ";
            }
            flag = true;
        }
    }
}