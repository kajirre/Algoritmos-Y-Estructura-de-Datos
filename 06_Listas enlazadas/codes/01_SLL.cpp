#include <iostream>
#include <string>
#include <utility>

// Clase auxiliar para demostrar copias vs movimientos
struct HeavyObject {
    std::string name;
    
    HeavyObject(std::string n) : name(n) {}
    
    // Constructor de copia (Lento)
    HeavyObject(const HeavyObject& other) : name(other.name) {
        std::cout << " [COPIA LENTA] Duplicando " << name << "\n";
    }
    
    // Constructor de movimiento (Rápido)
    // Al usar 'noexcept', permitimos que contenedores como std::vector
    // usen esta optimización automáticamente al redimensionarse.
    HeavyObject(HeavyObject&& other) noexcept : name(std::move(other.name)) {
        std::cout << " [MOVIMIENTO RAPIDO] Robando recursos de " << name << "\n";
    }
};

// Nuestra estructura Node actualizada
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& val) : data(val), next(nullptr) {}     // Copia
    Node(T&& val) : data(std::move(val)), next(nullptr) {} // Movimiento
};

int main() {
    std::cout << "--- ESCENARIO 1: Insertando variable existente (Copia) ---\n";
    HeavyObject obj1("Objeto1");
    Node<HeavyObject> n1(obj1); // Invoca constructor por copia

    std::cout << "\n--- ESCENARIO 2: Insertando temporal (Movimiento) ---\n";
    // "Objeto2" es un temporal, así que entra al constructor T&&
    Node<HeavyObject> n2(HeavyObject("Objeto2")); 

    return 0;
}
