#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP

#include "IList.hpp"
#include <iostream>
#include <stdexcept> // Necesario para std::out_of_range

/**
 * @brief Implementación de una Lista utilizando un arreglo dinámico.
 *
 * Los elementos se almacenan en bloques de memoria contigua, lo que permite
 * acceso rápido por índice (O(1)). Cuando el arreglo se llena, su capacidad
 * se expande automáticamente.
 *
 * @tparam T Tipo de los elementos que almacenará el arreglo.
 */
template <typename T>
class DynamicArray : public IList<T> {
protected:
    /** @brief Capacidad máxima actual del arreglo antes de necesitar redimensionar. */
    std::size_t capacity;

    /** @brief Puntero al arreglo dinámico subyacente. */
    T* arr;

public:
    /**
     * @brief Constructor por defecto.
     * @param initialCapacity Capacidad inicial del arreglo (por defecto 10).
     */
    DynamicArray(std::size_t initialCapacity = 10) : capacity(initialCapacity) {
        if (capacity == 0) capacity = 1; // Evitamos capacidad 0 para poder multiplicar al redimensionar
        arr = new T[capacity];
        this->size = 0; // Heredado de IList
    }

    /**
     * @brief Destructor. Libera la memoria dinámica del arreglo.
     */
    ~DynamicArray() override {
        delete[] arr;
    }

    /**
     * @brief Obtiene la capacidad actual del arreglo.
     * @return std::size_t La capacidad.
     */
    std::size_t getCapacity() const {
        return capacity;
    }

    /**
     * @brief Redimensiona el arreglo dinámico, duplicando su capacidad.
     */
    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        
        // Copiar los elementos al nuevo arreglo
        for (std::size_t i = 0; i < this->size; ++i) {
            newArr[i] = arr[i];
        }
        
        // Liberar la memoria del arreglo viejo y reasignar el puntero
        delete[] arr;
        arr = newArr;
    }

    // ========================================================================
    // Implementación de los métodos de IList
    // ========================================================================

    void clear() override {
        // No destruimos la memoria, simplemente reiniciamos el contador.
        // Los datos antiguos serán sobrescritos en futuras inserciones.
        this->size = 0;
    }

    void print() const override {
        std::cout << "[";
        for (std::size_t i = 0; i < this->size; ++i) {
            std::cout << arr[i] << (i < this->size - 1 ? ", " : "");
        }
        std::cout << "]\n";
    }

    T get(std::size_t index) const override {
        if (index >= this->size) {
            throw std::out_of_range("Índice fuera de rango en get()");
        }
        return arr[index];
    }

    void set(std::size_t index, const T& item) override {
        if (index >= this->size) {
            throw std::out_of_range("Índice fuera de rango en set()");
        }
        arr[index] = item;
    }

    int indexOf(const T& item) const override {
        for (std::size_t i = 0; i < this->size; ++i) {
            if (arr[i] == item) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void insertAt(std::size_t index, const T& item) override {
        if (index > this->size) {
            throw std::out_of_range("Índice fuera de rango en insertAt()");
        }
        if (this->size == capacity) {
            resize();
        }
        // Desplazar elementos hacia la derecha para hacer espacio
        for (std::size_t i = this->size; i > index; --i) {
            arr[i] = arr[i - 1];
        }
        arr[index] = item;
        this->size++;
    }

    void removeAt(std::size_t index) override {
        if (index >= this->size) {
            throw std::out_of_range("Índice fuera de rango en removeAt()");
        }
        // Desplazar elementos hacia la izquierda para cubrir el hueco
        for (std::size_t i = index; i < this->size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        this->size--;
    }

    void pushFront(const T& item) override {
        insertAt(0, item);
    }

    void pushBack(const T& item) override {
        if (this->size == capacity) {
            resize();
        }
        arr[this->size++] = item; // Más eficiente que llamar a insertAt(this->size, item)
    }

    T popFront() override {
        if (this->isEmpty()) {
            throw std::out_of_range("La lista está vacía en popFront()");
        }
        T item = arr[0];
        removeAt(0);
        return item;
    }

    T popBack() override {
        if (this->isEmpty()) {
            throw std::out_of_range("La lista está vacía en popBack()");
        }
        // Retornamos el último y simplemente reducimos el tamaño
        return arr[--this->size];
    }
};

#endif // DYNAMICARRAY_HPP
