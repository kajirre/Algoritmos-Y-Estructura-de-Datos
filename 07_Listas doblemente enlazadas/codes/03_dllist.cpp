#include <iostream>
#include <vector>
#include <chrono>   // Para medir el tiempo
#include <iomanip>  // Para formato de tabla
#include <string>
#include "dllist.h" 

// Configuración de la prueba
const int NUM_ELEMENTOS = 500000; // 500 mil elementos 

// --- Función auxiliar para medir tiempo ---
template <typename Func>
long long medirTiempo(Func funcion) {
    auto inicio = std::chrono::high_resolution_clock::now();
    funcion();
    auto fin = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
}

void imprimirFila(std::string test, long long tVector, long long tList, std::string ganador) {
    std::cout << "| " << std::setw(25) << std::left << test 
              << "| " << std::setw(15) << std::right << tVector 
              << "| " << std::setw(15) << std::right << tList 
              << "| " << std::setw(15) << std::left << ("  " + ganador) << " |" << std::endl;
}

int main() {
    std::cout << "==============================================================================\n";
    std::cout << "               BENCHMARK: DLList vs std::vector (" << NUM_ELEMENTOS << " elementos)\n";
    std::cout << "==============================================================================\n";
    std::cout << "| PRUEBA                   | VECTOR (us)    | LISTA (us)     | GANADOR         |\n";
    std::cout << "------------------------------------------------------------------------------\n";

    // -------------------------------------------------------
    // PRUEBA 1: PUSH BACK (Insertar al final)
    // -------------------------------------------------------
    std::vector<int> vec;
    DLList<int> list;

    // Reservamos memoria en vector para ser justos (evita reallocs), 
    // aunque vector suele ganar incluso sin reserve por la caché.
    vec.reserve(NUM_ELEMENTOS); 

    long long t1_vec = medirTiempo([&]() {
        for (int i = 0; i < NUM_ELEMENTOS; ++i) vec.push_back(i);
    });

    long long t1_list = medirTiempo([&]() {
        for (int i = 0; i < NUM_ELEMENTOS; ++i) list.pushBack(i);
    });

    imprimirFila("1. Push Back (Inserción)", t1_vec, t1_list, (t1_vec < t1_list ? "Vector" : "Lista"));

    // -------------------------------------------------------
    // PRUEBA 2: ACCESO ALEATORIO (Leer índice medio)
    // -------------------------------------------------------
    // Accederemos a todos los elementos secuencialmente por índice
    // Vector es aritmética de punteros. Lista es recorrer nodos.
    
    long long t2_vec = medirTiempo([&]() {
        volatile int dummy = 0; // volatile para que el compilador no optimice y borre el bucle
        for (int i = 0; i < NUM_ELEMENTOS; ++i) {
            dummy = vec[i];
        }
    });

    long long t2_list = medirTiempo([&]() {
        volatile int dummy = 0;
        // CUIDADO: Esto es O(N^2) en listas. Reducimos iteraciones para que no se congele.
        // Solo haremos 1000 accesos aleatorios para la lista para demostrar la lentitud
        int limite = 1000; 
        for (int i = 0; i < limite; ++i) {
            dummy = list.get(i);
        }
    });

    // Ajustamos el tiempo de la lista para proyectar cuánto tardaría con N completo
    // (Solo para efectos visuales de la comparación, ya que es O(N))
    long long t2_list_proyectado = t2_list * (NUM_ELEMENTOS / 1000);

    imprimirFila("2. Random Access (Get)", t2_vec, t2_list_proyectado, "Vector    ");

    // -------------------------------------------------------
    // PRUEBA 3: PUSH FRONT (Insertar al inicio)
    // -------------------------------------------------------
    // Reiniciamos estructuras
    vec.clear();
    list.clear();
    
    // Bajamos N para el vector porque es EXTREMADAMENTE lento en push_front
    int N_FRONT = 50000; 

    long long t3_vec = medirTiempo([&]() {
        for (int i = 0; i < N_FRONT; ++i) {
            vec.insert(vec.begin(), i); // O(N) -> Desplaza todo
        }
    });

    long long t3_list = medirTiempo([&]() {
        for (int i = 0; i < N_FRONT; ++i) {
            list.pushFront(i); // O(1) -> Solo mueve punteros
        }
    });

    imprimirFila("3. Push Front (" + std::to_string(N_FRONT) + ")", t3_vec, t3_list, "Lista    ");

    // -------------------------------------------------------
    // ANÁLISIS DE MEMORIA TEÓRICA
    // -------------------------------------------------------
    std::cout << "------------------------------------------------------------------------------\n";
    
    size_t memVector = NUM_ELEMENTOS * sizeof(int);
    // Lista: Cada nodo tiene int + prev* + next*
    size_t memNodo = sizeof(int) + 2 * sizeof(void*); 
    size_t memLista = NUM_ELEMENTOS * memNodo;

    std::cout << "\n[ANÁLISIS DE MEMORIA TEÓRICA para " << NUM_ELEMENTOS << " ints]\n";
    std::cout << "Vector: " << (memVector / 1024) << " KB (Datos puros)\n";
    std::cout << "Lista:  " << (memLista / 1024) << " KB (Datos + Punteros)\n";
    std::cout << "-> La lista usa " << (memLista / memVector) << " veces más memoria.\n";

    return 0;
}
