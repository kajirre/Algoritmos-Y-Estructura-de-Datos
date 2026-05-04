#ifndef LINEARHASHTABLE_HPP
#define LINEARHASHTABLE_HPP

#include "ISet.hpp"
#include "DynamicArray.hpp"
#include <iostream>
#include <functional> // Necesario para std::hash

/**
 * @brief Enum fuertemente tipado para gestionar el estado de cada ranura (slot) en la tabla.
 */
enum class SlotStatus {
    EMPTY,    
    OCCUPIED, 
    DELETED   
};

/**
 * @brief Sobrecarga del operador << para permitir que std::cout imprima un SlotStatus.
 * Esto es necesario porque DynamicArray<SlotStatus> intentará compilar su método virtual print().
 * Se usa 'inline' para evitar errores de definición múltiple si se incluye en varios archivos.
 */
inline std::ostream& operator<<(std::ostream& os, const SlotStatus& status) {
    switch (status) {
        case SlotStatus::EMPTY:    os << "EMPTY"; break;
        case SlotStatus::OCCUPIED: os << "OCCUPIED"; break;
        case SlotStatus::DELETED:  os << "DELETED"; break;
    }
    return os;
}

/**
 * @brief Tabla Hash de direccionamiento abierto mediante Sondeo Lineal (Linear Probing).
 *
 * Mantiene consistencia con ChainedHashTable utilizando el método de 
 * hashing Multiply-Shift (W, Z, D) para la dispersión de claves.
 *
 * @tparam T Tipo de los elementos que almacenará el conjunto.
 */
template <typename T>
class LinearHashTable : public ISet<T> {
private:
    /** @brief Puntero al arreglo dinámico que almacena los datos reales. */
    DynamicArray<T>* table;

    /** @brief Puntero al arreglo dinámico paralelo que almacena el estado de cada ranura. */
    DynamicArray<SlotStatus>* status;

    /** @brief Tamaño de palabra de la máquina en bits (usualmente 32). */
    int W;

    /** @brief Constante multiplicativa impar para dispersar las claves (Constante de Knuth). */
    unsigned int Z;

    /** @brief Potencia de 2 que determina el tamaño de la tabla (Capacidad = 2^D). */
    int D;

    /**
     * @brief Convierte cualquier tipo de dato genérico T a un entero sin signo.
     * @param item Elemento a convertir.
     * @return unsigned int Representación entera base generada por std::hash.
     */
    unsigned int convertToInt(const T& item) const {
        std::size_t hashValue = std::hash<T>{}(item);
        return static_cast<unsigned int>(hashValue);
    }

    /**
     * @brief Función de dispersión consistente usando el método Multiply-Shift.
     * @param item Elemento a evaluar.
     * @return int Índice calculado dentro de los límites de la tabla.
     */
    int hash(const T& item) const {
        unsigned int k = convertToInt(item);
        unsigned int result = (Z * k) >> (W - D);
        return static_cast<int>(result);
    }

public:
    /**
     * @brief Constructor principal. Inicializa la tabla utilizando potencias de 2.
     * @param bitsD Potencia para el tamaño inicial de la tabla (por defecto 4 -> 16 ranuras).
     * @param oddZ Número impar grande para el hash (por defecto la Constante de Knuth).
     */
    LinearHashTable(int bitsD = 4, unsigned int oddZ = 2654435769U) 
        : W(32), Z(oddZ), D(bitsD) {
        
        int capacity = 1 << D; // 2^D
        table = new DynamicArray<T>(capacity);
        status = new DynamicArray<SlotStatus>(capacity);

        // Inicializamos las estructuras subyacentes
        for (int i = 0; i < capacity; ++i) {
            table->pushBack(T{}); // Inserción de valor por defecto según el tipo T
            status->pushBack(SlotStatus::EMPTY);
        }
        this->size = 0;
    }

    /**
     * @brief Destructor. Libera la memoria de los arreglos dinámicos paralelos.
     */
    ~LinearHashTable() override {
        delete table;
        delete status;
    }

    /**
     * @brief Inserta un elemento manejando colisiones mediante sondeo lineal.
     * * Si encuentra una Lápida (DELETED) durante la búsqueda, recicla esa posición
     * para optimizar la memoria y acortar futuras cadenas de búsqueda.
     * * @param item Elemento a insertar.
     * @return true si se insertó con éxito, false si ya existía o la tabla está llena.
     */
    bool insert(const T& item) {
        int capacity = 1 << D;
        // Al no tener rehashing dinámico, prevenimos la inserción si se alcanza el límite
        if (this->size == static_cast<std::size_t>(capacity)) {
            return false;
        }

        int startIdx = hash(item);
        int idx = startIdx;
        int firstDeleted = -1; // Rastreador para reciclar la primera Lápida encontrada

        do {
            SlotStatus currentStatus = status->get(idx);

            if (currentStatus == SlotStatus::EMPTY) {
                // Fin de cadena. Insertamos en el primer DELETED si lo vimos, si no, aquí.
                int targetIdx = (firstDeleted != -1) ? firstDeleted : idx;
                table->set(targetIdx, item);
                status->set(targetIdx, SlotStatus::OCCUPIED);
                this->size++;
                return true;

            } else if (currentStatus == SlotStatus::OCCUPIED) {
                // Comprobamos duplicados (Propiedad Set)
                if (table->get(idx) == item) {
                    return false; 
                }

            } else if (currentStatus == SlotStatus::DELETED) {
                // Registramos la primera Lápida para usarla después si el elemento no es duplicado
                if (firstDeleted == -1) {
                    firstDeleted = idx;
                }
            }

            // Sondeo lineal: avanzamos al siguiente índice de forma circular
            idx = (idx + 1) % capacity;

        } while (idx != startIdx); 

        // Caso extremo: dimos la vuelta entera y estaba llena de Lápidas y ocupados (sin EMPTY)
        if (firstDeleted != -1) {
            table->set(firstDeleted, item);
            status->set(firstDeleted, SlotStatus::OCCUPIED);
            this->size++;
            return true;
        }

        return false;
    }

    // ========================================================================
    // Implementación de los métodos puramente virtuales de ISet
    // ========================================================================

    /**
     * @brief Añade un elemento a la tabla. Interfaz wrapper para insert().
     * @param item Elemento a añadir.
     * @return true si se añadió, false de lo contrario.
     */
    bool add(const T& item) override {
        return insert(item);
    }

    /**
     * @brief Elimina un elemento de la tabla.
     * * No borra el dato físicamente, sino que actualiza su estado a DELETED 
     * para no romper la cadena de búsqueda (Lápida).
     * * @param item Elemento a eliminar.
     * @return true si se encontró y eliminó, false si no existe.
     */
    bool remove(const T& item) override {
        int capacity = 1 << D;
        int startIdx = hash(item);
        int idx = startIdx;

        do {
            SlotStatus currentStatus = status->get(idx);

            if (currentStatus == SlotStatus::EMPTY) {
                return false; // El elemento definitivamente no está en esta cadena
            } else if (currentStatus == SlotStatus::OCCUPIED) {
                if (table->get(idx) == item) {
                    status->set(idx, SlotStatus::DELETED); // Colocamos la Lápida
                    this->size--;
                    return true;
                }
            }
            
            idx = (idx + 1) % capacity;

        } while (idx != startIdx);

        return false;
    }

    /**
     * @brief Verifica si un elemento existe dentro de la tabla.
     * @param item Elemento a buscar.
     * @return true si el elemento está presente, false en caso contrario.
     */
    bool contains(const T& item) const override {
        int capacity = 1 << D;
        int startIdx = hash(item);
        int idx = startIdx;

        do {
            SlotStatus currentStatus = status->get(idx);

            if (currentStatus == SlotStatus::EMPTY) {
                return false; // Fin de cadena, el elemento no existe
            } else if (currentStatus == SlotStatus::OCCUPIED) {
                if (table->get(idx) == item) {
                    return true;
                }
            }
            // Si es DELETED, seguimos sondeando
            idx = (idx + 1) % capacity;

        } while (idx != startIdx);

        return false;
    }

    /**
     * @brief Reinicia la tabla a su estado inicial.
     * Cambia todos los estados a EMPTY de forma lógica (O(N)).
     */
    void clear() override {
        int capacity = 1 << D;
        for (int i = 0; i < capacity; ++i) {
            status->set(i, SlotStatus::EMPTY);
        }
        this->size = 0;
    }

    /**
     * @brief Imprime el estado interno de la tabla en la consola.
     * Muestra las ranuras vacías, las ocupadas y las que contienen Lápidas.
     */
    void print() const override {
        int capacity = 1 << D;
        std::cout << "--- Tabla Hash (Sondeo Lineal) ---\n";
        for (int i = 0; i < capacity; ++i) {
            std::cout << "[" << i << "] ";
            SlotStatus currentStatus = status->get(i);
            
            if (currentStatus == SlotStatus::EMPTY) {
                std::cout << "(Vacio)\n";
            } else if (currentStatus == SlotStatus::DELETED) {
                std::cout << "(Borrado/Lapida)\n";
            } else {
                std::cout << table->get(i) << "\n";
            }
        }
    }
};

#endif // LINEARHASHTABLE_HPP
