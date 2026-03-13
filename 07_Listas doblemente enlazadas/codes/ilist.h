#ifndef ILIST_H
#define ILIST_H

#include <cstddef> // Para size_t

/**
 * Interfaz abstracta para listas (Simple, Doble, Circular).
 * Define el contrato que todas las listas deben cumplir.
 */
template <typename T>
class IList {
public:
    // Destructor virtual: Es CRUCIAL para evitar fugas de memoria
    // cuando se elimina una instancia derivada usando un puntero de tipo IList.
    virtual ~IList() {}

    // --- Métodos de Inserción ---
    
    // Inserta un elemento al final de la lista
    virtual void pushBack(const T& item) = 0;

    // Inserta un elemento al inicio de la lista
    virtual void pushFront(const T& item) = 0;

    // Inserta un elemento en una posición específica (opcional, pero recomendado)
    virtual void insertAt(size_t index, const T& item) = 0;

    // --- Métodos de Eliminación ---

    // Elimina el elemento en una posición específica
    virtual void removeAt(size_t index) = 0;

    // Elimina el primer elemento
    virtual void popFront() = 0;

    // Elimina el último elemento
    virtual void popBack() = 0;
    
    // Limpia toda la lista
    virtual void clear() = 0;

    // --- Métodos de Acceso y Estado ---

    // Devuelve el elemento en un índice dado (solo lectura)
    virtual T get(size_t index) const = 0;

    // Devuelve el tamaño actual de la lista
    virtual size_t getSize() const = 0;

    // Verifica si la lista está vacía
    virtual bool isEmpty() const = 0;

    // Imprime la lista (útil para depuración y la clase)
    virtual void print() const = 0;
};

#endif // ILIST_H
