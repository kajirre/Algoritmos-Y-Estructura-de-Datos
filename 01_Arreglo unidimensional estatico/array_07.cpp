#include <iostream>
using namespace std;

// Función con Efecto Secundario: Limpia los datos (pone a cero)
void resetearArreglo(int* ptr, int n) {
    cout << "\n[!] Ejecutando resetearArreglo en: " << ptr << endl;
    for (int i = 0; i < n; i++) {
        *(ptr + i) = 0; // Borrado de datos original
    }
}

int main() {
    int misAhorros[3] = {500, 1200, 350};
    
    cout << "--- ANTES del efecto secundario ---" << endl;
    cout << "Direccion: " << misAhorros << " | Valores: " 
         << misAhorros[0] << ", " << misAhorros[1] << ", " << misAhorros[2] << endl;

    // Llamada a la función
    resetearArreglo(misAhorros, 3);

    cout << "\n--- DESPUES del efecto secundario ---" << endl;
    cout << "Direccion: " << misAhorros << " | Valores: " 
         << misAhorros[0] << ", " << misAhorros[1] << ", " << misAhorros[2] << endl;
    
    cout << "\nADVERTENCIA: Los datos originales han sido destruidos." << endl;
    return 0;
}
