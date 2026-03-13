#include <iostream>
#include <vector>
#include <string>

class Analizador {
private:
    std::string nombre;
    double* datos;

public:
    // Constructor con parámetros
    Analizador(std::string n) : nombre(n) {
        datos = new double[10]; // Simulamos carga de datos
        std::cout << "[C] Constructor para '" << nombre 
                  << "' en STACK: " << this 
                  << " | HEAP asignado: " << static_cast<void*>(datos) << std::endl;
    }

    // Constructor de Movimiento
    Analizador(Analizador&& otro) noexcept : nombre(std::move(otro.nombre)), datos(otro.datos) {
        otro.datos = nullptr;
        std::cout << "[M] MOVIMIENTO de '" << nombre 
                  << "'. Nueva dirección STACK: " << this 
                  << " | Mantiene HEAP: " << static_cast<void*>(datos) << std::endl;
    }

    // Destructor
    ~Analizador() {
        if (datos != nullptr) {
            std::cout << "[D] Liberando HEAP de '" << nombre << "' en: " << static_cast<void*>(datos) << std::endl;
            delete[] datos;
        }
    }

    // Deshabilitamos copia para obligar a ver la diferencia
    Analizador(const Analizador&) = delete;
};

void comparativa_optimizacion() {
    std::vector<Analizador> v;
    v.reserve(5); // Reservamos para evitar que las reasignaciones ensucien la salida

    std::cout << "--- ESCENARIO 1: push_back ---" << std::endl;
    // 1. Se crea un objeto temporal en el stack
    // 2. Se mueve al vector
    // 3. El temporal se destruye
    v.push_back(Analizador("Temp_Push"));

    std::cout << "\n--- ESCENARIO 2: emplace_back ---" << std::endl;
    // Solo se llama al constructor una vez, directamente en la memoria del vector.
    // No hay temporales, no hay movimientos, no hay destrucción extra.
    v.emplace_back("InPlace_Emplace");

    std::cout << "\n--- FIN DE FUNCIÓN (Limpieza final) ---" << std::endl;
}


int main() {
	comparativa_optimizacion();\
	return 0;
}
