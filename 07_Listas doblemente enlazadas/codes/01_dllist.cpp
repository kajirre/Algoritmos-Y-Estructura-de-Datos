#include <iostream>
#include <string>
#include "dllist.h"

// Función auxiliar para imprimir encabezados de pruebas
void printHeader(const std::string& title) {
    std::cout << "\n========================================\n";
    std::cout << "PRUEBA: " << title << "\n";
    std::cout << "========================================\n";
}

int main() {
    try {
        // -------------------------------------------------
        // 1. Operaciones Básicas (Push, Pop, Print)
        // -------------------------------------------------
        printHeader("Operaciones Básicas con int");
        
        DLList<int> listaNumeros;
        
        std::cout << "Insertando al final (pushBack): 10, 20, 30" << std::endl;
        listaNumeros.pushBack(10);
        listaNumeros.pushBack(20);
        listaNumeros.pushBack(30);
        listaNumeros.print(); // Esperado: [ 10 20 30 ]

        std::cout << "Insertando al inicio (pushFront): 5" << std::endl;
        listaNumeros.pushFront(5);
        listaNumeros.print(); // Esperado: [ 5 10 20 30 ]

        std::cout << "Eliminando último (popBack)" << std::endl;
        listaNumeros.popBack();
        listaNumeros.print(); // Esperado: [ 5 10 20 ]

        std::cout << "Tamaño actual: " << listaNumeros.getSize() << std::endl;

        // -------------------------------------------------
        // 2. Inserción y Eliminación por Índice
        // -------------------------------------------------
        printHeader("InsertAt y RemoveAt");

        std::cout << "Insertando 15 en índice 2" << std::endl;
        listaNumeros.insertAt(2, 15);
        listaNumeros.print(); // Esperado: [ 5 10 15 20 ]

        std::cout << "Eliminando índice 0 (el 5)" << std::endl;
        listaNumeros.removeAt(0);
        listaNumeros.print(); // Esperado: [ 10 15 20 ]

        // -------------------------------------------------
        // 3. Uso de Iteradores (Range-based for loop)
        // -------------------------------------------------
        printHeader("Iteradores (C++ Style)");
        
        // Esto funciona gracias a que definiste begin(), end() y la clase Iterator
        std::cout << "Recorriendo la lista con for-loop moderno:" << std::endl;
        for (int num : listaNumeros) {
            std::cout << " -> " << num;
        }
        std::cout << std::endl;

        // -------------------------------------------------
        // 4. Constructor de Copia (Deep Copy)
        // -------------------------------------------------
        printHeader("Constructor de Copia");

        DLList<int> listaCopia = listaNumeros; // Invoca al constructor copia
        std::cout << "Lista Original: "; listaNumeros.print();
        std::cout << "Lista Copia:    "; listaCopia.print();

        std::cout << "Modificando copia (pushBack 99)..." << std::endl;
        listaCopia.pushBack(99);
        
        std::cout << "Original (intacta): "; listaNumeros.print();
        std::cout << "Copia (modificada): "; listaCopia.print();

        // -------------------------------------------------
        // 5. Semántica de Movimiento (Move Semantics)
        // -------------------------------------------------
        printHeader("Semántica de Movimiento (std::move)");

        // 
        // Aquí "robamos" los recursos de listaNumeros para dárselos a listaMovida.
        // Esto es muy eficiente porque solo intercambia punteros, no copia nodos.
        
        DLList<int> listaMovida = std::move(listaNumeros);

        std::cout << "Lista Movida (ahora tiene los datos): "; 
        listaMovida.print();

        std::cout << "Lista Original (debe estar vacía/init): "; 
        listaNumeros.print(); // Debería imprimir [] o estar vacía
        
        if (listaNumeros.isEmpty()) {
            std::cout << "VERIFICADO: La lista original quedó vacía tras el move." << std::endl;
        }

        // -------------------------------------------------
        // 6. Manejo de Excepciones
        // -------------------------------------------------
        printHeader("Manejo de Errores");

        try {
            std::cout << "Intentando acceder a índice inválido (100)..." << std::endl;
            listaMovida.get(100);
        } catch (const std::out_of_range& e) {
            std::cout << "EXCEPCIÓN ATRAPADA: " << e.what() << std::endl;
        }

        // -------------------------------------------------
        // 7. Tipos Complejos (std::string)
        // -------------------------------------------------
        printHeader("Uso con std::string");
        
        DLList<std::string> listaTexto;
        listaTexto.pushBack("Hola");
        listaTexto.pushBack("Mundo");
        listaTexto.pushFront("Saludo:");
        
        listaTexto.print(); // [ Saludo: Hola Mundo ]

    } catch (const std::exception& e) {
        std::cerr << "Error inesperado: " << e.what() << std::endl;
    }

    return 0;
}
