#include <iostream>
#include <vector>

void demostracion_itinerarios() {
    std::vector<int> v = {10, 20, 30, 40, 50};
    
    // Obtenemos iteradores
    auto it_inicio = v.begin();
    auto it_final  = v.end();

    std::cout << "--- Geometría del Vector ---" << std::endl;
    std::cout << "Dirección begin() : " << &(*it_inicio) << " (Valor: " << *it_inicio << ")" << std::endl;
    std::cout << "Dirección end()   : " << &(*it_final)  << " (¡Cuidado! Apunta fuera)" << std::endl;

    // Aritmética de Acceso Aleatorio O(1)
    auto it_medio = it_inicio + 2; // Salto matemático de 2 posiciones
    
    std::cout << "\n--- Aritmética de Iteradores ---" << std::endl;
    std::cout << "it_inicio + 2     : " << &(*it_medio) << " (Valor: " << *it_medio << ")" << std::endl;
    
    // Distancia entre iteradores (Matemáticamente: it2 - it1)
    std::cout << "Distancia total   : " << (it_final - it_inicio) << " elementos." << std::endl;
}

int main(){
	demostracion_itinerarios();
	return 0;
}
