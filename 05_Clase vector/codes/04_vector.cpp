#include <iostream>
#include <vector>

void demostracion_invalidacion() {
    std::vector<int> v = {100, 200, 300};
    
    // 1. Estado Inicial
    std::cout << "--- 1. ESTADO INICIAL ---" << std::endl;
    std::cout << "Capacidad actual: " << v.capacity() << std::endl;
    std::cout << "Dirección real de v[0]: " << &v[0] << std::endl;

    // Guardamos un iterador al inicio
    auto it_viejo = v.begin();
    std::cout << "Iterador 'it_viejo' apunta a: " << &(*it_viejo) 
              << " | Valor: " << *it_viejo << std::endl;

    // 2. Provocar la "Mudanza" (Realloc)
    // Agregamos elementos hasta que supere la capacidad de 3
    std::cout << "\n--- 2. AGREGANDO ELEMENTOS (Provocando Reasignación) ---" << std::endl;
    for(int i = 0; i < 5; ++i) v.push_back(i);

    // 3. Verificación de la Catástrofe
    std::cout << "\n--- 3. RESULTADO DE LA MUDANZA ---" << std::endl;
    std::cout << "Nueva Capacidad: " << v.capacity() << std::endl;
    std::cout << "Nueva dirección real de v[0]: " << &v[0] << std::endl;

    std::cout << "\n--- 4. COMPARATIVA CRÍTICA ---" << std::endl;
    std::cout << "El iterador 'it_viejo' se quedó en: " << &(*it_viejo) << std::endl;
    
    if (&(*it_viejo) != &v[0]) {
        std::cout << "Valor de v[0]: " << v[0] << std::endl;
        std::cout << "[ALERTA] El iterador es INVÁLIDO. " << std::endl;
        std::cout << "Iterador 'it_viejo' apunta a: " << &(*it_viejo) 
              << " | Valor en 'it_viejo': " << *it_viejo << std::endl;
        std::cout << "Apunta a memoria que el SO ya liberó o marcó como basura." << std::endl;
        // Acceder a *it_viejo aquí es comportamiento indefinido (UB)
    }
}

int main(){

	demostracion_invalidacion();
	return 0;
}
