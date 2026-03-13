#include <iostream>

using namespace std;

int main() {
    // Definición bajo estándar ISO (secuencia contigua de 5 objetos)
    int datos[5] = {10, 20, 30, 40, 50};
    int n = 5;

    cout << "--- METODOS DE RECORRIDO EN ARREGLOS ---" << endl << endl;

    // METODO 1: Por Índice (Tradicional)
    cout << "1. Recorrido por Indice:  ";
    for (int i = 0; i < n; i++) {
        cout << datos[i] << " ";
    }
    cout << "\n   (Usa la formula: Base + i * 4 bytes)" << endl << endl;


    // METODO 2: Por Punteros (Bajo Nivel)
    cout << "2. Recorrido por Punteros: ";
    // El nombre del arreglo 'datos' decae a un puntero al inicio
    for (int* p = datos; p < (datos + n); p++) {
        cout << *p << " "; // Desreferenciamos para ver el valor
    }
    cout << "\n   (Usa aritmetica: p++ salta al siguiente bloque fisico)" << endl << endl;


    // METODO 3: Range-based For (Seguridad Moderno)
    cout << "3. Recorrido por Rango:   ";
    for (int elemento : datos) {
        cout << elemento << " ";
    }
    cout << "\n   (El compilador gestiona los limites automaticamente)" << endl;

    return 0;
}
