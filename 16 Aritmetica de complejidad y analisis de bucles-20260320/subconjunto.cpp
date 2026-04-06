#include <iostream>
#include <vector>
#include <algorithm> // Para usar la función max()

using namespace std;

int encontrarSumaMaxima(int A[], int n) {
    int max_Sum = 0;

    for (int i = 0; i < n; i++) {
        int current_Sum = 0;
        
        for (int j = i; j < n; j++) {
            current_Sum = current_Sum + A[j];
            
            if (current_Sum > max_Sum) {
                max_Sum = current_Sum;
            }
        }
    }
    
    return max_Sum;
}

int main() {
    // Ejemplo de prueba: un arreglo con números positivos y negativos
    int datos[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(datos) / sizeof(datos[0]);

    int resultado = encontrarSumaMaxima(datos, n);

    cout << "La suma maxima encontrada es: " << resultado << endl;

    return 0;
}