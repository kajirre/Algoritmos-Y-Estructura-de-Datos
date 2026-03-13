#include <iostream>

using namespace std;

// Función que acepta un rango definido por [begin, end)
// Observa que los nombres de los argumentos ya sugieren su función
void imprimir_rango(int* begin, int* end) {
    cout << "[ ";
    
    // ESTE ES EL BUCLE UNIVERSAL DE C++
    // No importa si es un vector, lista o arreglo dinámico, 
    // la lógica siempre es: inicializar en begin, parar en end, avanzar con ++.
    /*
    for (int* it = begin; it != end; ++it) {
        cout << *it << " ";
    }
    */
    for (int* it = end - 1; it != begin; --it) {
        cout << *it << " ";
    }
    cout << "]" << endl;
}

int main() {
    // 1. Configuración del escenario (Arreglo Dinámico)
    int n = 5;
    int* data = new int[n];

    // Rellenamos datos: 10, 20, 30, 40, 50
    for (int i = 0; i < n; i++) {
        data[i] = (i + 1) * 10;
    }

    // -------------------------------------------------------------
    // CONSTRUCCIÓN DE LOS "ITERADORES" (Punteros con semántica)
    // -------------------------------------------------------------
    
    // 'begin': Apunta al primer elemento válido (índice 0)
    int* begin = data;
    
    // 'end': Apunta UNO DESPUÉS del último elemento válido.
    // MATEMÁTICAMENTE: dirección_base + cantidad_elementos
    int* end = data + n; 

    // Visualización lógica:
    // [ 10 | 20 | 30 | 40 | 50 ]  [ ?? ]
    //   ^                          ^
    //   |                          |
    // begin                       end (¡Zona prohibida!)

    // -------------------------------------------------------------
    // USO 1: Recorrer todo el contenedor
    // -------------------------------------------------------------
    cout << "Recorrido Completo:" << endl;
    imprimir_rango(begin, end);

    // -------------------------------------------------------------
    // USO 2: Sub-rangos (Slicing)
    // -------------------------------------------------------------
    // Queremos imprimir desde el 30 hasta el final.
    // El 30 está en la posición (begin + 2)
    
    cout << "Desde el tercer elemento hasta el final:" << endl;
    // Creamos un nuevo punto de partida, pero usamos el mismo final
    imprimir_rango(begin + 2, end);

    // Queremos imprimir solo el 20 y el 30.
    // Inicio: begin + 1 (donde está el 20)
    // Fin:    begin + 3 (uno después del 30, para que el bucle pare ahí)
    
    cout << "Sub-rango central (20, 30):" << endl;
    imprimir_rango(begin + 1, begin + 3);

    // Limpieza
    delete[] data;

    // Buenas prácticas: Anular los punteros manualmente
    // Esto es lo que hacen los destructores de las clases (como vector) automáticamente.
    data = nullptr;
    begin = nullptr;
    end = nullptr;

    cout << "Memoria liberada y punteros anulados de forma segura." << endl;

    return 0;
}
