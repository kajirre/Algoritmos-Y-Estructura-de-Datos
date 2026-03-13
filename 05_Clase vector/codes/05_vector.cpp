#include <iostream>
#include <vector>
#include <chrono>

void benchmark_memoria() {
    const int N = 1000000; // 1 Millón de elementos
    
    std::cout << "=== ESCENARIO A: SIN RESERVE (Crecimiento Dinámico) ===" << std::endl;
    
    auto inicio1 = std::chrono::high_resolution_clock::now();
    
    std::vector<int> v_dinamico;
    int reasignaciones = 0;
    size_t cap_previa = 0;

    for(int i = 0; i < N; ++i) {
        v_dinamico.push_back(i);
        
        // Detectamos cuando el vector "se muda" en el Heap
        if (v_dinamico.capacity() != cap_previa) {
            cap_previa = v_dinamico.capacity();
            reasignaciones++;
            
            // Imprimimos solo las primeras para no saturar el notebook, 
            // pero lo suficiente para ver el patrón.
            if (reasignaciones <= 10 || i > N - 100) {
                std::cout << "[MUDANZA #" << reasignaciones 
                          << "] Size: " << i 
                          << " | Nueva Capacidad: " << cap_previa 
                          << " | Nueva Dirección: " << &v_dinamico[0] << std::endl;
            }
        }
    }
    
    auto fin1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms1 = fin1 - inicio1;

    std::cout << "\n=== ESCENARIO B: CON RESERVE (Asignación Única) ===" << std::endl;
    
    auto inicio2 = std::chrono::high_resolution_clock::now();
    
    std::vector<int> v_optimizado;
    v_optimizado.reserve(N); // Una sola petición al SO
    
    std::cout << "[SISTEMA] Capacidad inicial fija: " << v_optimizado.capacity() 
              << " | Dirección: " << &v_optimizado[0] << std::endl;

    for(int i = 0; i < N; ++i) {
        v_optimizado.push_back(i);
    }
    
    auto fin2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms2 = fin2 - inicio2;

    std::cout << "\n--- COMPARATIVA FINAL ---" << std::endl;
    std::cout << ">> Mudanzas en A: " << reasignaciones << " veces." << std::endl;
    std::cout << ">> Tiempo en A:   " << ms1.count() << " ms" << std::endl;
    std::cout << ">> Tiempo en B:   " << ms2.count() << " ms" << std::endl;
    std::cout << ">> ACELERACIÓN:  " << (ms1.count() / ms2.count()) << "x más rápido." << std::endl;
}
int main(){
	benchmark_memoria();
	return 0;
}
