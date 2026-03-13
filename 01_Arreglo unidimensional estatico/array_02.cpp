#include <iostream>
using namespace std;

int main() {
    int variableSana = 100;
    int miArreglo[3] = {1, 2, 3}; // Índices válidos: 0, 1, 2

    cout << "--- Experimento de Acceso Fuera de Rango ---" << endl;
    cout << "Valor de variableSana: " << variableSana << endl;
    cout << "Direccion de variableSana: " << &variableSana << endl;

    // Intentamos acceder a un índice que NO existe
    // En muchas arquitecturas, el Stack coloca las variables cerca una de otra.
    cout << "\nAccediendo a miArreglo[4] (Fuera de rango!): " << miArreglo[4] << endl;

    // PELIGRO: Intentar escribir fuera del rango
    // Esto podria sobreescribir 'variableSana' si el compilador las puso juntas.
    miArreglo[4] = 999; 

    cout << "\nDespues de escribir en miArreglo[4]:" << endl;
    cout << "Nuevo valor de miArreglo[4]: " << miArreglo[4] << endl;
    cout << "Valor de variableSana (¿cambio?): " << variableSana << endl;

    return 0;
}
