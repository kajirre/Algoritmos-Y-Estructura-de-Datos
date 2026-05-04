#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>
#include <random>
#include <sstream>
#include "ChainedHashTable.hpp"
#include "LinearHashTable.hpp"

// ============================================================================
// Funciones Auxiliares
// ============================================================================
std::string boolToString(bool value) {
    return value ? "Exito" : "Fallo/No encontrado/Lleno";
}

void printSeparator(const std::string& title) {
    std::cout << "\n==========================================================\n";
    std::cout << "   " << title << "\n";
    std::cout << "==========================================================\n";
}

// ============================================================================
// 1. Pruebas de Funcionamiento Básico
// ============================================================================
void pruebaFuncionamiento() {
    printSeparator("PRUEBA DE FUNCIONAMIENTO BASICO");

    // D = 3 -> Capacidad de 8 ranuras/cubetas. Ideal para forzar colisiones.
    ChainedHashTable<int> chained(3);
    LinearHashTable<int> linear(3);

    std::cout << "[+] Insertando datos (10, 20, 15, 12, 10-Duplicado)...\n";
    std::vector<int> datos = {10, 20, 15, 12};
    for (int num : datos) {
        chained.add(num);
        linear.add(num);
    }
    
    std::cout << "Intento de duplicado (10) en Chained: " << boolToString(chained.add(10)) << "\n";
    std::cout << "Intento de duplicado (10) en Linear : " << boolToString(linear.add(10)) << "\n\n";

    std::cout << "[+] Estado inicial tras colisiones:\n";
    std::cout << ">>> Chained (Observa las listas enlazadas):\n";
    chained.print();
    std::cout << "\n>>> Linear (Observa los espacios desplazados):\n";
    linear.print();

    std::cout << "\n[+] Eliminando el numero 20...\n";
    chained.remove(20);
    linear.remove(20);

    std::cout << "\n[+] Estado tras eliminacion:\n";
    std::cout << ">>> Chained (Nodo borrado):\n";
    chained.print();
    std::cout << "\n>>> Linear (Se debio crear una Lapida/DELETED):\n";
    linear.print();

    std::cout << "\n[+] Busqueda de un elemento existente (15):\n";
    std::cout << "Chained contiene 15? " << boolToString(chained.contains(15)) << "\n";
    std::cout << "Linear  contiene 15? " << boolToString(linear.contains(15)) << " (Atraviesa la lapida)\n";
}

// ============================================================================
// 2. Pruebas de Estrés
// ============================================================================
void pruebaEstres() {
    printSeparator("PRUEBA DE ESTRES (EL COLAPSO ASINTOTICO)");

    // Capacidad: 262,144 ranuras. 
    // Un tamaño perfecto para que el test no tarde 1 hora, pero lo suficiente 
    // para destruir el rendimiento de LinearProbing al llegar al 99%.
    int D = 18; 
    int capacidad = 1 << D;
    ChainedHashTable<int> chained(D);
    LinearHashTable<int> linear(D);

    // std::mt19937 genera números aleatorios reales de 32 bits
    // Garantiza que casi no habrá duplicados (espacio de 2 billones)
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(1, 2000000000);

    std::cout << "Capacidad real de la tabla: " << capacidad << " ranuras.\n";
    std::cout << "Metodologia: Mediremos el tiempo exacto que toma insertar 2,000 elementos\n";
    std::cout << "nuevos, partiendo de diferentes niveles de Factor de Carga.\n\n";

    std::cout << std::left << std::setw(15) << "Factor Carga"
              << std::setw(20) << "Chained Time (ms)" 
              << std::setw(20) << "Linear Time (ms)" 
              << std::setw(15) << "Multiplicador" << "\n";
    std::cout << std::string(70, '-') << "\n";

    // Los hitos de carga donde detendremos la ejecución para medir
    std::vector<double> hitos = {0.0, 50.0, 75.0, 90.0, 95.0, 98.0, 99.0};
    int insertadosTotal = 0;

    for (double hito : hitos) {
        // 1. Rellenar la tabla silenciosamente hasta llegar al hito objetivo
        int targetElements = static_cast<int>((hito / 100.0) * capacidad);
        while (insertadosTotal < targetElements) {
            int num = dist(rng);
            chained.add(num);
            linear.add(num);
            insertadosTotal++;
        }

        // 2. Preparar el lote de prueba estricto (2,000 elementos puros)
        int tamanoPrueba = 2000;
        std::vector<int> lotePrueba(tamanoPrueba);
        for(int i = 0; i < tamanoPrueba; ++i) {
            lotePrueba[i] = dist(rng);
        }

        // 3. Medir tiempo de inserción en la tabla Encadenada
        auto startChained = std::chrono::high_resolution_clock::now();
        for (int num : lotePrueba) {
            chained.add(num);
        }
        auto endChained = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> timeChained = endChained - startChained;

        // 4. Medir tiempo de inserción en la tabla Lineal
        auto startLinear = std::chrono::high_resolution_clock::now();
        for (int num : lotePrueba) {
            linear.add(num);
        }
        auto endLinear = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> timeLinear = endLinear - startLinear;

        // Sumar al total
        insertadosTotal += tamanoPrueba;

        // Calcular qué tan peor es Linear respecto a Chained
        double multiplier = timeLinear.count() / timeChained.count();
	
	// Pre-formateamos el porcentaje y el multiplicador como cadenas unidas
        std::ostringstream ossHito;
        ossHito << std::fixed << std::setprecision(1) << hito << "%";

        std::ostringstream ossMult;
        ossMult << std::fixed << std::setprecision(1) << multiplier << "x";

        // Ahora imprimimos las cadenas completas, manteniendo la alineación perfecta de las columnas
        std::cout << std::left << std::setw(15) << ossHito.str()
                  << std::setw(20) << std::fixed << std::setprecision(3) << timeChained.count()
                  << std::setw(20) << timeLinear.count()
                  << std::setw(15) << ossMult.str() << "\n";

    }
    
    std::cout << "\n* Conclusion: En cargas bajas (< 75%), Linear es mas rapido por su arquitectura\n";
    std::cout << "  de memoria contigua (Caché L1). Sin embargo, al cruzar el 95%, el Agrupamiento\n";
    std::cout << "  Primario colapsa el algoritmo, haciendolo cientos de veces mas lento.\n";
}


// ============================================================================
// 3. Prueba de Comparación Directa
// ============================================================================
void pruebaComparacion() {
    printSeparator("COMPARACION DIRECTA DE RENDIMIENTO");

    // D = 16 -> Capacidad de 65,536.
    // Insertaremos 45,000 elementos -> Factor de Carga ~ 68.6% 
    // (Un escenario realista donde Linear aun sobrevive pero empieza a sufrir)
    int D = 16;
    int elementos = 45000;
    
    ChainedHashTable<int> chained(D);
    LinearHashTable<int> linear(D);

    std::cout << "Escenario: Tabla de 65,536 ranuras. Factor de carga de ~68.6%.\n\n";
    std::cout << std::left << std::setw(25) << "Operacion" 
              << std::setw(20) << "Chained (ms)" 
              << std::setw(20) << "Linear (ms)" << "\n";
    std::cout << std::string(60, '-') << "\n";

    // --- 1. Inserción ---
    auto t1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < elementos; i++) chained.add(i * 3); // Multiplicamos para esparcir los numeros
    auto t2 = std::chrono::high_resolution_clock::now();
    
    auto t3 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < elementos; i++) linear.add(i * 3);
    auto t4 = std::chrono::high_resolution_clock::now();

    std::cout << std::left << std::setw(25) << "1. Insercion Masiva" 
              << std::setw(20) << std::chrono::duration<double, std::milli>(t2-t1).count()
              << std::setw(20) << std::chrono::duration<double, std::milli>(t4-t3).count() << "\n";

    // --- 2. Búsqueda Exitosa ---
    t1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < elementos; i++) chained.contains(i * 3);
    t2 = std::chrono::high_resolution_clock::now();
    
    t3 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < elementos; i++) linear.contains(i * 3);
    t4 = std::chrono::high_resolution_clock::now();

    std::cout << std::left << std::setw(25) << "2. Busqueda Exitosa" 
              << std::setw(20) << std::chrono::duration<double, std::milli>(t2-t1).count()
              << std::setw(20) << std::chrono::duration<double, std::milli>(t4-t3).count() << "\n";

    // --- 3. Búsqueda Fallida ---
    t1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < elementos; i++) chained.contains(i * 3 + 1); // Buscamos numeros que no existen
    t2 = std::chrono::high_resolution_clock::now();
    
    t3 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < elementos; i++) linear.contains(i * 3 + 1);
    t4 = std::chrono::high_resolution_clock::now();

    std::cout << std::left << std::setw(25) << "3. Busqueda Fallida" 
              << std::setw(20) << std::chrono::duration<double, std::milli>(t2-t1).count()
              << std::setw(20) << std::chrono::duration<double, std::milli>(t4-t3).count() << "\n";

    // --- 4. Eliminación ---
    t1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < elementos; i++) chained.remove(i * 3);
    t2 = std::chrono::high_resolution_clock::now();
    
    t3 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < elementos; i++) linear.remove(i * 3);
    t4 = std::chrono::high_resolution_clock::now();

    std::cout << std::left << std::setw(25) << "4. Eliminacion Masiva" 
              << std::setw(20) << std::chrono::duration<double, std::milli>(t2-t1).count()
              << std::setw(20) << std::chrono::duration<double, std::milli>(t4-t3).count() << "\n";
    std::cout << "\n";
}

int main() {
    // Para compilar: g++ -std=c++17 main.cpp -o hash_tests
    // Para ejecutar: ./hash_tests

    std::cout << "Iniciando Suite de Pruebas de Tablas Hash...\n";
    
    pruebaFuncionamiento();
    pruebaEstres();
    pruebaComparacion();

    return 0;
}
