#include <iostream>

int main() {
    int filas, cols;
    std::cout << "Ingrese filas y columnas: ";
    std::cin >> filas >> cols;

    // --- PASO 1: ASIGNACIÓN ---
    // Creamos el arreglo de punteros (las filas)
    int** matriz = new int* [filas];

    for (int i = 0; i < filas; i++) {
        // Creamos cada arreglo de datos (las columnas)
        matriz[i] = new int[cols];
    }

    // --- PASO 2: USO ---
    // Llenamos la matriz con valores ilustrativos
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            matriz[i][j] = (i + 1) * (j + 1);
            std::cout << matriz[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    // --- PASO 3: DESASIGNACIÓN (Orden Inverso) ---
    // 1. Liberar cada fila individualmente
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
        matriz[i] = nullptr; // Buena práctica: evitar punteros colgantes en las filas
    }

    // 2. Liberar el arreglo de punteros principal
    delete[] matriz;
    matriz = nullptr; // Buena práctica: limpiar el puntero principal

    std::cout << "\nMemoria liberada exitosamente." << std::endl;

    return 0;
}
