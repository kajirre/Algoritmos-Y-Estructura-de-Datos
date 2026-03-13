#include <iostream>
#include <vector>

/*
	Este codigo permite observar empiricamente la politica de 
    crecimiento y la invalidacion de punteros/iteradores 
*/


int main() {
    std::vector<int> v;
    size_t capacidad_inicial = v.capacity();

    std::cout << "Capacidad inicial: " << capacidad_inicial << std::endl;

    for(int i = 0; i < 100; ++i) {
        v.push_back(i);
        if (v.capacity() != capacidad_inicial) {
            capacidad_inicial = v.capacity();
            // Esto demuestra el crecimiento exponencial (factor de carga)
            std::cout << "Reasignacion detectada. Nueva capacidad: " << capacidad_inicial 
                      << " | Tamaño: " << v.size() << std::endl;
        }
    }
    return 0;
}
