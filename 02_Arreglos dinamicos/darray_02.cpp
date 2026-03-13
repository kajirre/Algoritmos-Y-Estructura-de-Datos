#include <iostream>

int main() {
    // --- PASO 1: ASIGNACIÓN ---
    int* ptr = new int[2]; // Reservamos espacio para 2 enteros
    ptr[0] = 77;
    ptr[1] = 88;

    std::cout << "--- PASO 1: Memoria Asignada ---" << std::endl;
    std::cout << "Direccion almacenada en ptr: " << ptr << std::endl;
    std::cout << "Contenido: [" << ptr[0] << ", " << ptr[1] << "]" << std::endl << std::endl;

    // --- PASO 2: LIBERACIÓN (EL PELIGRO) ---
    delete[] ptr; 
    
    std::cout << "--- PASO 2: Despues de delete[] (Puntero Colgante) ---" << std::endl;
    std::cout << "Direccion todavia en ptr: " << ptr << " (¡Sigue apuntando al mismo sitio!)" << std::endl;
    // Intentamos leer (Comportamiento Indefinido)
    std::cout << "Contenido 'fantasma': [" << ptr[0] << ", " << ptr[1] << "]" << std::endl;
    std::cout << "Nota: Los valores pueden ser los originales o basura, el sistema ya no los protege." << std::endl << std::endl;

    // --- PASO 3: REUTILIZACIÓN DE MEMORIA ---
    // Creamos otra variable. Es muy probable que el heap use la misma direccion liberada.
    int* nuevoPtr = new int[2];
    nuevoPtr[0] = 100;
    nuevoPtr[1] = 200;

    std::cout << "--- PASO 3: Nueva asignacion detectada ---" << std::endl;
    std::cout << "Direccion de nuevoPtr: " << nuevoPtr << std::endl;
    
    // Aquí es donde ocurre el desastre:
    if (ptr == nuevoPtr) {
        std::cout << "¡ALERTA! El puntero colgante 'ptr' y 'nuevoPtr' apuntan al mismo sitio." << std::endl;
        std::cout << "Si uso el viejo 'ptr[0]', estoy modificando accidentalmente 'nuevoPtr'." << std::endl;
        std::cout << "Valor visto desde ptr[0]: " << ptr[0] << " (Deberia ser 77, pero es 100)" << std::endl;
    }

    // --- LIMPIEZA CORRECTA ---
    delete[] nuevoPtr;
    nuevoPtr = nullptr;
    ptr = nullptr; // Ahora ambos son seguros

    return 0;
}
