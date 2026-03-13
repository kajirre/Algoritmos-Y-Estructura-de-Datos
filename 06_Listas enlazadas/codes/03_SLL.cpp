#include <iostream>
#include <vector>
#include <chrono> // Para medir el tiempo
#include "SinglyLL.hpp" // Importamos TU clase

// Configuracion de la prueba
const int NUM_ELEMENTOS = 50000; // 50 mil datos

int main() {
    std::cout << "=== BATALLA DE ESTRUCTURAS DE DATOS ===\n";
    std::cout << "Insertando " << NUM_ELEMENTOS << " elementos AL INICIO (Head)...\n\n";

    // ---------------------------------------------
    // ROUND 1: Tu Lista Enlazada (SinglyLL)
    // ---------------------------------------------
    SinglyLL<int> miLista;
    
    // Inicia el cronómetro
    auto start_lista = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_ELEMENTOS; ++i) {
        miLista.pushFront(i); // O(1) constante
    }

    // Detiene el cronómetro
    auto end_lista = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tiempo_lista = end_lista - start_lista;

    std::cout << "1. SinglyLL (pushFront): " << tiempo_lista.count() << " ms\n";
    std::cout << "   -> Estado: Terminado. Size: " << miLista.getSize() << "\n\n";


    // ---------------------------------------------
    // ROUND 2: Standard Vector (std::vector)
    // ---------------------------------------------
    std::vector<int> miVector;
    
    auto start_vector = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_ELEMENTOS; ++i) {
        // insert(begin, val) obliga a mover todo el arreglo a la derecha
        miVector.insert(miVector.begin(), i); 
    }

    auto end_vector = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tiempo_vector = end_vector - start_vector;

    std::cout << "2. std::vector (insert begin): " << tiempo_vector.count() << " ms\n";
    std::cout << "   -> Estado: Terminado. Size: " << miVector.size() << "\n\n";

    // ---------------------------------------------
    // ANÁLISIS DE RESULTADOS
    // ---------------------------------------------
    std::cout << "=== VEREDICTO ===\n";
    if (tiempo_lista.count() < tiempo_vector.count()) {
        double veces_mas_rapido = tiempo_vector.count() / tiempo_lista.count();
        std::cout << "🏆 TU LISTA GANA.\n";
        std::cout << "Es " << veces_mas_rapido << " veces mas rapida insertando al inicio.\n";
        std::cout << "Razon: O(1) vs O(n) por cada insercion.\n";
    } else {
        std::cout << "🏆 EL VECTOR GANA (Raro en esta prueba).\n";
    }

    return 0;
}
