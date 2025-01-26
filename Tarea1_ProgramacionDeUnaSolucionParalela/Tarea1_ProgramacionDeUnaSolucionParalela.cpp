// Tarea1_ProgramacionDeUnaSolucionParalela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#if _OPENMP
    #include <omp.h>
#endif // _OPENMP

#define N 1000 // Cantidad de elementos a manejar
#define chunk  10 // Tamaño que tienen los pedazos de los arreglos para cada hilo
#define mostrar 10// Cantidad de datos a imprimir

void imprimeArreglo(float* d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++)
    {
        a[i] = i * 5;
        b[i] = (i + 10) * 5.5;
    }
    int pedazos = chunk;

    #pragma omp parallel for \
    shared(a, b, c, pedazos) private (i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    std::cout << "Impimiendo los primero " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Impimiendo los primero " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Impimiendo los primero " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}

void imprimeArreglo(float* d)
{
    for (int i = 0; i < mostrar; i++)
        std::cout << d[i] << " - ";
    std:: cout << std::endl;
}