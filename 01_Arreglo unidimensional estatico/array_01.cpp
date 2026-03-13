#include <iostream>

using namespace std;

int main() {
    // 1. INICIALIZACIÓN COMPLETA
    // Se definen todos los elementos explícitamente.
    int completa[5] = {10, 20, 30, 40, 50};

    // 2. INICIALIZACIÓN PARCIAL
    // Se definen solo los primeros. ¿Qué pasa con el resto? 
    // C++ rellena automáticamente los faltantes con CERO.
    int parcial[5] = {1, 2};

    // 3. SIN INICIALIZAR (Cuidado aquí)
    // Se reserva el espacio en el STACK, pero no se limpia.
    // Contendrá lo que sea que hubiera en esa dirección de memoria antes ("Basura").
    int sinInits[5];

    cout << "--- Estrategias de Inicializacion ---" << endl << endl;

    // Mostrar Completa
    cout << "COMPLETA {10, 20, 30, 40, 50}: ";
    for(int i=0; i<5; i++) cout << completa[i] << " ";
    cout << endl;

    // Mostrar Parcial
    cout << "PARCIAL {1, 2}:               ";
    for(int i=0; i<5; i++) cout << parcial[i] << " "; 
    cout << " <- (Los ceros son automaticos)" << endl;

    // Mostrar Sin Inicializar
    cout << "SIN INICIALIZAR:             ";
    for(int i=0; i<5; i++) cout << sinInits[i] << " ";
    cout << " <- (Valores basura del Stack)" << endl;

    return 0;
}
