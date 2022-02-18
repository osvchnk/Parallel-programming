/* Используя возможности OpenMP, написать программу умножения матрицы на вектор. Память для
* матрицы и векторов выделять динамически. Сравнить результат выполнения последовательной и
* параллельной программ. Сравнить время работы последовательной и параллельных программ.
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main()
{
    int m;
    int n;

    std::cout << "Enter size of matrix: ";
    std::cin >> m;
    std::cin >> n;

    int matrix[m][n];

    printf("%d %d\n", m , n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
        }
    }

    int v[n];
    std::cout << "Enter vector: ";
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }

    std::cout << "Matrix: \n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Vector: \n";
    for (int i = 0; i < n; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
    
    int result[n];
    clock_t start_p = clock();
    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic) firstprivate(v)
        for (int i = 0; i < n; i++) {
            result[i] = 0;
            for (int j = 0; j < m; j++) {
                result[i] += v[j] * matrix[i][j];
            }
        }
        
    }
    clock_t end_p = clock() - start_p;

    std::cout << "Result: \n";
    for (int i = 0; i < n; i++) {
        std::cout << result[i] << " ";
    }
    std::cout << "\nparallel program time: " << (float)end_p/CLOCKS_PER_SEC;
}