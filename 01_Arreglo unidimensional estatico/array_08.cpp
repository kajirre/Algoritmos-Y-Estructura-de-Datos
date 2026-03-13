#include <iostream>
using namespace std;

void funcionConProblema(int arr[]) {
    cout << "\n--- DENTRO DE LA FUNCION ---" << endl;
    cout << "Direccion recibida: " << arr << endl;
    
    // ERROR TIPICO: Intentar calcular el tamaño aqui
    // sizeof(arr) aqui devuelve el tamaño del PUNTERO (8 bytes en 64-bit), no del arreglo total.
    int tamanoCalculado = sizeof(arr) / sizeof(arr[0]);
    
    cout << "sizeof(arr) en funcion: " << sizeof(arr) << " bytes" << endl;
    cout << "Tamano calculado (ERROR): " << tamanoCalculado << " elementos" << endl;
}

int main() {
    int misDatos[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "--- EN EL MAIN ---" << endl;
    cout << "Direccion original: " << misDatos << endl;
    
    // En el main, el contexto es completo
    int tamanoReal = sizeof(misDatos) / sizeof(misDatos[0]);
    
    cout << "sizeof(misDatos) en main: " << sizeof(misDatos) << " bytes (4 bytes * 10)" << endl;
    cout << "Tamano real: " << tamanoReal << " elementos" << endl;

    // Llamamos a la funcion
    funcionConProblema(misDatos);

    return 0;
}
