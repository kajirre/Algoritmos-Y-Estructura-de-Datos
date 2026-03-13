#include <iostream>
#include <vector>

class Elemento {
public:
    double coordenadas[3]; // El objeto tiene un "cuerpo" (24 bytes)
    int id;

    // Constructor: Se activa con resize()
    Elemento() : id(10) {
        std::cout << "  [C] Constructor invocado en: " << this << " (Tamaño: " << sizeof(*this) << " bytes)" << std::endl;
    }

    ~Elemento() {
        std::cout << "  [D] Destructor invocado en:  " << this << std::endl;
    }

    // Declaración 'friend' DENTRO de la clase
    // Esto permite definirlo aquí mismo, pero C++ lo trata como función global
    friend std::ostream& operator<<(std::ostream& os, const Elemento& e) {
    os << "Elemento[ID: " << e.id << "]";
    return os;
}
};

void demostracion_tecnica() {
    std::cout << "--- ESCENARIO A: reserve(3) ---" << std::endl;
    std::vector<Elemento> v_a;
    v_a.reserve(3); 
    std::cout << "Size: " << v_a.size() << " | Capacity: " << v_a.capacity() << std::endl;
    std::cout << "Nota: El contador de objetos es 0. El Heap tiene el espacio, pero no hay objetos vivos." << std::endl;

    std::cout << "\n--- ESCENARIO B: resize(3) ---" << std::endl;
    std::vector<Elemento> v_b;
    v_b.resize(3);
    std::cout << "ID del objeto: " << v_b[0] << std::endl;
    
    std::cout << "Size: " << v_b.size() << " | Capacity: " << v_b.capacity() << std::endl;
    
    std::cout << "\n--- ANÁLISIS DE DIRECCIONES (CONTIGÜIDAD) ---" << std::endl;
    for(int i = 0; i < 3; ++i) {
        std::cout << "Objeto [" << i << "] dirección: " << &v_b[i] << std::endl;
    }
}

int main(){
	demostracion_tecnica();
	return 0;
}
