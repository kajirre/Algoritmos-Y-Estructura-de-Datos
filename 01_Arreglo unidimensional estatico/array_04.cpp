#include <iostream>
using namespace std;

int main() {
    // --- PARTE 1: EL PUNTERO INDEPENDIENTE ---
    int numero = 50;
    int* ptrIndividual = &numero; // & extrae la direccion

    cout << "--- 1. Concepto de Puntero ---" << endl;
    cout << "Variable 'numero': " << numero << endl;
    cout << "Direccion (&numero): " << ptrIndividual << endl;
    cout << "Contenido apuntado (*ptrIndividual): " << *ptrIndividual << endl;

    // --- PARTE 2: EL ARREGLO (ESTRUCTURA ISO) ---
    // Segun ISO, 'datos' es una secuencia contigua de 3 doubles
    double datos[3] = {10.5, 20.2, 30.7};
    double* ptrArreglo = datos; // El nombre del arreglo decae a puntero al primer elemento

    cout << "\n--- 2. Aritmetica de Punteros (Relacion con Arreglo) ---" << endl;
    cout << "Tamano de un double: " << sizeof(double) << " bytes" << endl;

    for (int i = 0; i < 3; i++) {
        // (ptrArreglo + i) aplica la aritmetica de escala ISO:
        // Direccion = Base + (i * sizeof(double))
        cout << "Indice [" << i << "]:" << endl;
        cout << "  Acceso Subindice datos[" << i << "]: " << datos[i] << endl;
        cout << "  Acceso Puntero   *(ptr + " << i << "): " << *(ptrArreglo + i) << endl;
        cout << "  Direccion en Memoria: " << (ptrArreglo + i) << endl;
        cout << "------------------------------------------" << endl;
    }

    return 0;
}
