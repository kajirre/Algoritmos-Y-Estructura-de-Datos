#include <iostream>

using namespace std;

// ---------------------------------------------------------
// 1. LA FUNCIÓN TRAMPA (Paso por Valor - COPIA)
// ---------------------------------------------------------
// Recibe COPIAS de los valores. 
// Intercambia las copias, pero las variables originales no se enteran.
void swap_trampa(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    // Aquí 'a' y 'b' se destruyen al terminar la función.
}

// ---------------------------------------------------------
// 2. LA FUNCIÓN CORRECTA (Paso por Referencia)
// ---------------------------------------------------------
// Recibe las DIRECCIONES de memoria originales (alias).
void swap_correcto(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Función auxiliar para imprimir
void imprimir(int* begin, int* end) {
    cout << "[ ";
    for (int* it = begin; it != end; ++it) cout << *it << " ";
    cout << "]" << endl;
}

// Algoritmo de Inversión (Recibe la función de swap como puntero a función para no repetir código)
// Nota: Si esto es muy avanzado, puedes copiar y pegar el while dos veces en el main.
void invertir_arreglo(int* begin, int* end, void (*funcion_swap)(int, int)) {
    // Sobrecarga para la función trampa (por valor)
    int* izq = begin;
    int* der = end - 1;
    while (izq < der) {
        funcion_swap(*izq, *der); // Pasamos valores
        izq++; der--;
    }
}

void invertir_arreglo_ref(int* begin, int* end, void (*funcion_swap)(int&, int&)) {
    // Sobrecarga para la función correcta (por referencia)
    int* izq = begin;
    int* der = end - 1;
    while (izq < der) {
        funcion_swap(*izq, *der); // Pasamos referencias
        izq++; der--;
    }
}

int main() {
    int n = 5;
    int* data = new int[n];
    for(int i=0; i<n; i++) data[i] = (i+1)*10;
    
    int* begin = data;
    int* end = data + n;

    cout << "1. Estado Inicial:" << endl;
    imprimir(begin, end);
    cout << "------------------------------------------------" << endl;

    // INTENTO 1: Usando la función TRAMPA
    // Lógica: Intentamos invertir el arreglo, pero usando paso por valor.
    
    // Simulación del bucle con la función mala:
    int* izq = begin;
    int* der = end - 1;
    while (izq < der) {
        swap_trampa(*izq, *der); // <--- AQUÍ ESTÁ EL ERROR SILENCIOSO
        izq++; der--;
    }

    cout << "2. Después de 'swap_trampa':" << endl;
    imprimir(begin, end);
    cout << "   (¡Observen que NO cambió nada! Trabajamos sobre fotocopias)" << endl;
    cout << "------------------------------------------------" << endl;

    // INTENTO 2: Usando la función CORRECTA
    // Reiniciamos punteros
    izq = begin;
    der = end - 1;
    while (izq < der) {
        swap_correcto(*izq, *der); // <--- AQUÍ USAMOS REFERENCIA (&)
        izq++; der--;
    }

    cout << "3. Después de 'swap_correcto':" << endl;
    imprimir(begin, end);
    cout << "   (Ahora sí se invirtieron los datos originales)" << endl;

    delete[] data;
    return 0;
}
