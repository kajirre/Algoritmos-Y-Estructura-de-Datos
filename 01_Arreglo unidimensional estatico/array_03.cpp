#include <iostream>
#include <iomanip> // Para formatear la salida

using namespace std;

int main() {
    // 1. Declaración e Inicialización (Tamaño fijo definido en tiempo de compilación)
    // El compilador reserva exactamente 5 * sizeof(int) bytes en el STACK.
    double notas[5] = {85, 92, 78, 90, 88};

    cout << "--- Demostracion de Arreglo Estatico ---" << endl;
    cout << "Tamano de un entero (int): " << sizeof(int) << " bytes" << endl << endl;

    // 2. Demostración de Memoria Contigua y Acceso O(1)
    cout << "Indice | Valor | Direccion de Memoria | Calculo (Base + i * 4)" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (int i = 0; i < 5; i++) {
        // Obtenemos la dirección de memoria de cada elemento
        uintptr_t direccion = reinterpret_cast<uintptr_t>(&notas[i]);
        
        cout << "  [" << i << "]  |  " 
             << notas[i] << "   |  " 
             << &notas[i] << "      |  ";
        
        if (i == 0) cout << "(Base)";
        else {
            // Mostramos la diferencia de bytes con respecto al anterior
            uintptr_t base = reinterpret_cast<uintptr_t>(&notas[0]);
            cout << "Base + " << (direccion - base) << " bytes";
        }
        cout << endl;
    }

    // 3. Relación entre el Nombre del Arreglo y Punteros
    cout << "\n--- Relacion con Punteros ---" << endl;
    cout << "Direccion base (notas):      " << notas << endl;
    cout << "Direccion del primer elem:  " << &notas[0] << endl;

    if (notas == &notas[0]) {
        cout << "Confirmado: El nombre del arreglo apunta al primer elemento." << endl;
    }

    return 0;
}
