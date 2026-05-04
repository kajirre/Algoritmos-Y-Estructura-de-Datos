#include <iostream>
#include <string>
#include <chrono>
#include "ChainedHashTable.hpp"

// Función auxiliar para imprimir resultados booleanos
std::string boolToString(bool value) {
    return value ? "Exito (True)" : "Fallo/Ya existe (False)";
}

void pruebaBasica() {
    std::cout << "========================================\n";
    std::cout << "   Prueba Basica de ChainedHashTable    \n";
    std::cout << "========================================\n\n";

    ChainedHashTable<int> mySet(3); // 2^3 = 8 cubetas

    mySet.add(15);
    mySet.add(23);
    mySet.add(42);
    mySet.add(8);
    mySet.add(16);
    mySet.add(4);

    std::cout << "Estado de la Tabla tras inserciones (buscando colisiones):\n";
    mySet.print();
    std::cout << "\n";

    std::cout << "Eliminando 15...\n";
    mySet.remove(15);
    std::cout << "Contiene 15 ahora? " << (mySet.contains(15) ? "Si" : "No") << "\n\n";
}

void pruebaDeEstres() {
    std::cout << "========================================\n";
    std::cout << "   Prueba de Estres y Degradacion       \n";
    std::cout << "========================================\n\n";

    // Instanciamos una tabla con D=8 (2^8 = 256 cubetas)
    // Es un numero pequeño intencionalmente para forzar listas largas rapidamente.
    ChainedHashTable<int> stressTable(8); 
    
    const int lotes = 6;
    const int elementosPorLote = 20000;
    int insertadosTotal = 0;

    std::cout << "Tabla inicializada con 256 cubetas.\n";
    std::cout << "Insertando lotes de " << elementosPorLote << " elementos...\n\n";
    std::cout << "Lote\t| Elementos Totales\t| Tiempo de Insercion (ms)\n";
    std::cout << "----------------------------------------------------------\n";

    for (int i = 0; i < lotes; ++i) {
        // Iniciamos el cronómetro
        auto start = std::chrono::high_resolution_clock::now();

        // Insertamos un lote de números (simulando datos nuevos)
        for (int j = 0; j < elementosPorLote; ++j) {
            stressTable.add(insertadosTotal + j);
        }

        // Detenemos el cronómetro
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        insertadosTotal += elementosPorLote;

        // Imprimimos los resultados de este lote
        std::cout << (i + 1) << "\t| " 
                  << insertadosTotal << "\t\t| " 
                  << duration.count() << " ms\n";
    }

    std::cout << "\nConclusion de la prueba:\n";
    std::cout << "Notaras que a medida que las listas enlazadas en cada cubeta crecen,\n";
    std::cout << "el costo de verificar duplicados (recorrer la lista) hace que el\n";
    std::cout << "tiempo de insercion por lote aumente significativamente.\n\n";
}

int main() {
    pruebaBasica();
    pruebaDeEstres();
    return 0;
}
