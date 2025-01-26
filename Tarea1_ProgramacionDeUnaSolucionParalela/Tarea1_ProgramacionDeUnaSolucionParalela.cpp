// Tarea1_ProgramacionDeUnaSolucionParalela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream> // Librería estandar para operaciones de entrada y salida

// Solo si OpenMP está disponible se incluye la libreria necesaria para su uso
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

/// <summary>
/// Imprime los valores del arreglo pasado como parametro
/// El numero de valores es tomado de la macro mostrar
/// </summary>
/// <param name="d"></param>
void imprimeArreglo(float* d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    // Se declaran los arreglos a sumar (a, b) y el arreglo donde se almacenara el resultado (c)
    // El tamaño es el mismo para todos con base a la macro definida N
    float a[N], b[N], c[N];
    int i;

    // Se llenan los arreglos a y b.
    llenarArreglos(a, b, 10);

    // se define el numero de particiones en el cual se dividiran los arreglos a sumar
    int pedazos = chunk;

    // Se hace la declaración el comportamiento que nuestro ciclo "for" tendrá
    // Se establece que los arreglos a, b y c se compartiran entre todas las particiones
    // la variable i se declara como privada para cada hilo para que su valor permazca sin mezclarse entre ellos
    // finalmente se establece con la palabra "static" que la particion será establecida de forma fija mediante un numero que es "pedazos"
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private (i) \
    schedule(static, pedazos)

    // Una vez declarado el comportamiento que nuestro ciclo "for" tendrá, se llama de manera convencional
    // Aunque internamente estará ejecutandose paralelamente con base a las especificaciones establecides con OpenMP
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