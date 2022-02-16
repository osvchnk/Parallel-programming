/* Написать программу, в которой объявить и присвоить начальные значения целочисленным
* переменным: a и b, определить две параллельные области, первая – с числом нитей 2, 
* вторая – с числом нитей 4. Для первой области переменные a и b объявить защищенными, 
* с режимом доступа private и firstprivate соответственно, внутри области определить номер нити и
* выполнить увеличение значения переменных на эту величину. Выдать на экран значения переменных до входа
* в параллельную область, внутри параллельной области и после выхода из параллельной области. Для
* второй области переменную a объявить общей, переменную b объявить защищенной, с режимом
* доступа private, определить номер нити и выполнить уменьшение значения переменных на эту
* величину. Выдать на экран значения переменных до входа в параллельную область, внутри
* параллельной области и после выхода из параллельной области.
*/
#include <stdio.h>
#include <omp.h>
#include <iostream>

int main()
{
    int a;
    int b;
    std::cin >> a >> b;

    printf("Parallel region 1\nBefore a=%d b=%d\n", a, b);

    #pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        int nthread = omp_get_thread_num();
        a += nthread;
        b += nthread;
        printf("Thread %d a=%d b=%d\n", omp_get_thread_num(), a, b);
    }
    printf("After a=%d b=%d\n\n", a, b);

    printf("Parallel region 2\nBefore a=%d b=%d\n", a, b);

    #pragma omp parallel num_threads(4) shared(a) private(b)
    {
        int nthread = omp_get_thread_num();
        a -= nthread;
        b -= nthread;
        printf("Thread %d a=%d b=%d\n", omp_get_thread_num(), a, b);
    }
    printf("After a=%d b=%d\n", a, b);
}