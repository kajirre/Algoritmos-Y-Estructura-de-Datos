#ifndef CHAINEDHASHTABLE_HPP
#define CHAINEDHASHTABLE_HPP

#include "ISet.hpp"
#include "DynamicArray.hpp"
#include "SinglyLL.hpp"
#include <iostream>
#include <functional> // Necesario para std::hash

/**
 * @brief Tabla Hash que maneja colisiones utilizando encadenamiento (Listas Enlazadas).
 *
 * Implementa la interfaz ISet. Los elementos se distribuyen en "cubetas" (buckets)
 * calculados mediante una función Hash. Si hay colisiones, se enlazan en una lista.
 *
 * @tparam T Tipo de los elementos que almacenará el conjunto.
 */
template <typename T>
class ChainedHashTable : public ISet<T> {
private:
    /** * @brief Arreglo dinámico que actúa como tabla. 
     * Almacenamos punteros a SinglyLL para evitar problemas de copia de memoria.
     */
    DynamicArray<SinglyLL<T>*> table;

    /** @brief Tamaño de palabra de la máquina en bits (usualmente 32 o 64). */
    int W;

    /** @brief Número impar aleatorio para dispersar las claves en el hashing MAD. */
    int Z;

    /** @brief Potencia de 2 que determina el tamaño de la tabla (Capacidad = 2^D). */
    int D;

    /**
     * @brief Convierte cualquier tipo de dato T a un entero sin signo.
     * @param item Elemento a convertir.
     * @return unsigned int La representación entera del elemento.
     */
    unsigned int convertToInt(const T& item) const {
        // std::hash es la herramienta estándar en C++11/17 para obtener hashes base
        std::size_t hashValue = std::hash<T>{}(item);
        return static_cast<unsigned int>(hashValue);
    }

    /**
     * @brief Función de dispersión utilizando el método de multiplicación por bits.
     * @param item Elemento a hashear.
     * @return int Índice de la cubeta (bucket) donde pertenece el elemento.
     */
    int hash(const T& item) const {
        unsigned int k = convertToInt(item);
        // Prevenir desbordamiento (overflow) no definido operando con enteros sin signo
        unsigned int result = (static_cast<unsigned int>(Z) * k) >> (W - D);
        return static_cast<int>(result);
    }

public:
    /**
     * @brief Constructor de la tabla hash.
     * @param bitsD Potencia para el tamaño inicial de la tabla (por defecto 4 -> 16 cubetas).
     * @param oddZ Número impar para la función hash (por defecto 33).
     */
    ChainedHashTable(int bitsD = 4, int oddZ = 33) : W(32), Z(oddZ), D(bitsD) {
        int capacity = 1 << D; // 2^D
        for (int i = 0; i < capacity; ++i) {
            // Inicializamos cada cubeta con una lista enlazada vacía
            table.pushBack(new SinglyLL<T>());
        }
        this->size = 0;
    }

    /**
     * @brief Destructor. Libera las listas asignadas dinámicamente.
     */
    ~ChainedHashTable() override {
        int capacity = 1 << D;
        for (int i = 0; i < capacity; ++i) {
            delete table.get(i);
        }
    }

    /**
     * @brief Inserta un elemento en la tabla. 
     * @param item Elemento a insertar.
     * @return true si se insertó, false si ya existía (es un Set).
     */
    bool insert(const T& item) {
        int idx = hash(item);
        SinglyLL<T>* list = table.get(idx);
        
        // Al ser un Set, no permitimos duplicados
        if (list->indexOf(item) != -1) {
            return false;
        }
        
        list->pushFront(item); // O(1) inserción
        this->size++;
        return true;
    }

    // ========================================================================
    // Implementación de los métodos puramente virtuales de ISet
    // ========================================================================

    /**
     * @brief Alias para cumplir con la interfaz ISet, utiliza insert() por debajo.
     */
    bool add(const T& item) override {
        return insert(item);
    }

    bool remove(const T& item) override {
        int idx = hash(item);
        SinglyLL<T>* list = table.get(idx);
        
        int listIdx = list->indexOf(item);
        if (listIdx == -1) {
            return false; // El elemento no está en la tabla
        }
        
        list->removeAt(static_cast<std::size_t>(listIdx));
        this->size--;
        return true;
    }

    bool contains(const T& item) const override {
        int idx = hash(item);
        SinglyLL<T>* list = table.get(idx);
        return list->indexOf(item) != -1;
    }

    void clear() override {
        int capacity = 1 << D;
        for (int i = 0; i < capacity; ++i) {
            table.get(i)->clear();
        }
        this->size = 0;
    }

    void print() const override {
        int capacity = 1 << D;
        std::cout << "--- Tabla Hash ---" << "\n";
        for (int i = 0; i < capacity; ++i) {
            std::cout << "Cubeta " << i << ": ";
            table.get(i)->print();
        }
    }
};

#endif // CHAINEDHASHTABLE_HPP
