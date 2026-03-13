#include <iostream>

using namespace std;

// ---------------------------------------------------------
// 1. LA "MICRO-OPERACIÓN" (Paso por Referencia)
// ---------------------------------------------------------
// Esta función recibe una REFERENCIA a una celda de memoria (&destino).
// Cualquier cambio que hagamos a 'destino' alterará el arreglo original.
// 'valor' se pasa por copia (int normal) porque solo lo leemos.
void agregar_valor(int& destino, int valor) {
    destino = destino + valor;
}

// ---------------------------------------------------------
// 2. LA FUNCIÓN DE RECORRIDO (Iteradores)
// ---------------------------------------------------------
// Recorre el vector destino y le suma lo que haya en el vector fuente.
// Asumimos que 'fuente' tiene al menos el mismo tamaño que 'destino'.
void sumar_vectores(int* begin_dest, int* end_dest, int* begin_source) {
    
    // Dos iteradores: uno para leer y otro para escribir
    int* it_dest = begin_dest;
    int* it_src = begin_source;

    // Recorremos hasta que se acabe el vector destino
    while (it_dest != end_dest) {
        
        // LLAMADA CLAVE:
        // *it_dest : Es la celda real en memoria (se pasa por REFERENCIA a la función)
        // *it_src  : Es el valor a sumar (se pasa por VALOR)
        agregar_valor(*it_dest, *it_src);

        // Avanzamos ambos punteros
        it_dest++;
        it_src++;
    }
}

// Función auxiliar para imprimir
void imprimir(const char* nombre, int* begin, int* end) {
    cout << nombre << ": [ ";
    for (int* it = begin; it != end; ++it) cout << *it << " ";
    cout << "]" << endl;
}

int main() {
    int n = 5;
    
    // 1. Crear Arreglo A (Acumulador) en Memoria Dinámica
    int* vecA = new int[n]; 
    for(int i=0; i<n; i++) vecA[i] = 10; // Todos valen 10

    // 2. Crear Arreglo B (Sumando) en Memoria Dinámica
    int* vecB = new int[n];
    for(int i=0; i<n; i++) vecB[i] = (i+1); // 1, 2, 3, 4, 5

    // Definir límites de A
    int* beginA = vecA;
    int* endA = vecA + n;

    cout << "--- Antes de la suma ---" << endl;
    imprimir("Vector A", beginA, endA);
    imprimir("Vector B", vecB, vecB + n);

    // -----------------------------------------------------
    // 3. EJECUTAR LA SUMA (A += B)
    // -----------------------------------------------------
    // Pasamos el rango de A (donde escribiremos) 
    // y el inicio de B (de donde leeremos).
    sumar_vectores(beginA, endA, vecB);

    cout << "\n--- Despues de la suma (A += B) ---" << endl;
    imprimir("Vector A", beginA, endA); // A ha sido modificado
    
    // Limpieza de memoria (¡Vital!)
    delete[] vecA;
    delete[] vecB;
    
    return 0;
}
