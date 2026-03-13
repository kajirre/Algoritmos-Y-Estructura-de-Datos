#include <iostream>
#include "dllist.h"

// Función auxiliar para concatenar dos listas.
// Mueve los elementos de 'fuente' al final de 'destino'.
template <typename T>
void empetarListas(DLList<T>& destino, DLList<T>& fuente) {
    // 1. Recorremos la lista fuente
    // Gracias a tus iteradores, podemos usar un for-loop moderno
    for (const auto& elemento : fuente) {
        destino.pushBack(elemento); // Copiamos el dato al final de destino
    }

    // 2. Vaciamos la lista fuente para evitar datos duplicados
    // (Opcional, pero usualmente cuando empetas, quieres mover los datos)
    fuente.clear();
}

int main() {
    // --- Preparación ---
    DLList<std::string> listaA;
    listaA.pushBack("A1");
    listaA.pushBack("A2");

    DLList<std::string> listaB;
    listaB.pushBack("B1");
    listaB.pushBack("B2");
    listaB.pushBack("B3");

    std::cout << "--- Antes de Concatenar ---" << std::endl;
    std::cout << "Lista A: "; listaA.print();
    std::cout << "Lista B: "; listaB.print();

    // --- Acción ---
    std::cout << "\nConcatenando Lista B dentro de Lista A..." << std::endl;
    empetarListas(listaA, listaB);

    // --- Resultado ---
    std::cout << "\n--- Después de Concatenar ---" << std::endl;
    std::cout << "Lista A (Resultado): "; listaA.print();
    std::cout << "Lista B (debe estar vacía): "; listaB.print();

    // Verificación de integridad circular
    std::cout << "\nVerificando tamaño final de A: " << listaA.getSize() << std::endl;

    return 0;
}
