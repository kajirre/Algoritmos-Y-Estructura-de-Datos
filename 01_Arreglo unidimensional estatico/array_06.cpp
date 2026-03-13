#include <iostream>
#include <iomanip>
using namespace std;

// Opción 1: Notación de Arreglo []
// Aunque use [], C++ recibe la DIRECCIÓN de memoria original.
void modificarConArreglo(int arr[], int n) {
    cout << "\n[Funcion A - arr[]] Recibida direccion: " << arr << endl;
    for (int i = 0; i < n; i++) {
        arr[i] = arr[i] * 2; // Modificación directa
    }
}

// Opción 2: Notación de Puntero *
// Aquí la sintaxis es explícita: recibimos un puntero a la dirección original.
void modificarConPuntero(int* ptr, int n) {
    cout << "\n[Funcion B - *ptr ] Recibida direccion: " << ptr << endl;
    for (int i = 0; i < n; i++) {
        *(ptr + i) = *(ptr + i) + 100; // Modificación via aritmética
    }
}

int main() {
    const int n = 3;
    int datos[n] = {10, 20, 30};

    cout << "--- RASTREO DE DIRECCIONES Y ESTADOS ---" << endl;
    cout << "Direccion original en main (&datos): " << datos << endl;
    cout << "Estado Inicial: [ " << datos[0] << ", " << datos[1] << ", " << datos[2] << " ]" << endl;

    // 1. Llamado con []
    modificarConArreglo(datos, n);
    cout << "Estado Post-Funcion A: [ " << datos[0] << ", " << datos[1] << ", " << datos[2] << " ]" << endl;

    // 2. Llamado con *
    modificarConPuntero(datos, n);
    cout << "Estado Post-Funcion B: [ " << datos[0] << ", " << datos[1] << ", " << datos[2] << " ]" << endl;

    cout << "\nCONCLUSION PARA LA CLASE:" << endl;
    cout << "Las tres direcciones impresas son IDENTICAS. Esto confirma que" << endl;
    cout << "C++ no copia los elementos; solo pasa la referencia al bloque contiguo." << endl;

    return 0;
}
