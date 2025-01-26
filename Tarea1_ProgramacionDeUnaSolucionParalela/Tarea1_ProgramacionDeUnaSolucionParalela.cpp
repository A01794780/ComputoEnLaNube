// Tarea1_ProgramacionDeUnaSolucionParalela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#if _OPENMP
    #include <omp.h>
#endif // _OPENMP

#define N 1500 // Cantidad de elementos a manejar
#define chunk  10 // Tamaño que tienen los pedazos de los arreglos para cada hilo
#define mostrar 15// Cantidad de datos a imprimir

/// <summary>
/// Llena los arreglos a y b que se sumaran haciendo uso de un valor pasado como parametro
/// </summary>
/// <param name="a">Arreglo a llenar</param>
/// <param name="b">Arreglo a llenar</param>
/// <param name="valor">Valor que se usara para generar valores para llenar los arreglos a y b</param>
void llenarArreglos(float* a, float* b, float valor);
void imprimeArreglo(float* d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    llenarArreglos(a, b, 10);

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

void llenarArreglos(float* a, float* b, float valor)
{
    for (int i = 0; i < N; i++)
    {
        a[i] = i * valor;
        b[i] = (i + valor*2) * (valor/2);
    }
}

void imprimeArreglo(float* d)
{
    for (int i = 0; i < mostrar; i++)
        std::cout << d[i] << " - ";
    std:: cout << std::endl;
}