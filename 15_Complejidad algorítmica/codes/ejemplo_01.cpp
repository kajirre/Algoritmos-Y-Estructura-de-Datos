#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include <chrono>

// Función genérica para medir el tiempo de recorrido de cualquier contenedor
template <typename Contenedor>
long long medirRecorrido(const Contenedor& c) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    volatile long long suma = 0;
    // Recorrido O(n) para cualquier contenedor que soporte iteradores
    for (const auto& elemento : c) {
        suma += elemento;
    }
    
    auto fin = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
}

int main() {
    const size_t N = 10'000'000; // 10 millones de elementos
    
    std::cout << "Inicializando estructuras de datos...\n";
    std::vector<int> arreglo(N, 1);
    std::list<int> lista_enlazada(N, 1);
    
    std::cout << "Midiendo tiempo de recorrido O(n):\n";
    
    long long tiempo_vector = medirRecorrido(arreglo);
    std::cout << "Estructura Contigua (std::vector): " << tiempo_vector << " microsegundos.\n";
    
    long long tiempo_lista = medirRecorrido(lista_enlazada);
    std::cout << "Estructura Enlazada (std::list):   " << tiempo_lista << " microsegundos.\n";
    
    std::cout << "\nDiferencia de rendimiento empírico: Factor de " 
              << (double)tiempo_lista / tiempo_vector << "x a favor del arreglo contiguo.\n";
              
    return 0;
}
