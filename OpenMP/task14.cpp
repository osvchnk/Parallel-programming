/* Написать параллельную программу возведения числа 210 в квадрат без операции умножения.
* Пояснение: Квадрат натурального числа N равен сумме первых N нечетных чисел. Например, 32 = 9
* это 1+3+5=9; 52 = 25 это 1+3+5+7+9=25
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <stdlib.h>

int main()
{
    int result;
    #pragma omp parallel
    {
        #pragma omp for reduction(+ : result)
        for (int i = 0; i < 210; i++) {
            result += i * 2 + 1;
        }
    }
    printf("result: %d", result);
    return 0;
}