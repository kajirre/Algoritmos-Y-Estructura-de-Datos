#include <iostream>

int main() {
    int tamaño;
    std::cout << "Ingrese el numero de elementos: ";
    std::cin >> tamaño;

    // 1. Asignación dinámica: se reserva memoria en el heap
    // Buena práctica: siempre usar un puntero del tipo de dato correspondiente
    int* miArreglo = new int[tamaño]; 

    // 2. Uso del arreglo: se accede mediante índices (como un arreglo estático)
    for (int i = 0; i < tamaño; i++) {
        miArreglo[i] = i * 10; // Inicialización
    }

    // Mostrar contenido
    std::cout << "Contenido del arreglo dinámico:" << std::endl;
    for (int i = 0; i < tamaño; i++) {
        std::cout << "Indice [" << i << "]: " << miArreglo[i] << std::endl;
    }

    // 3. Liberación de memoria: obligatoria para evitar fugas
    // Buena práctica: usar delete[] (con corchetes) para arreglos
    delete[] miArreglo; 

    // Buena práctica: poner el puntero en nullptr tras liberar para evitar punteros "colgantes"
    miArreglo = nullptr; 

    return 0;
}
