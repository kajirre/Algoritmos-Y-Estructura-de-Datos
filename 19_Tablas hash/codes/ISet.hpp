#ifndef ISET_HPP
#define ISET_HPP

#include <cstddef> // Necesario para std::size_t

/**
 * @brief Interfaz abstracta para un conjunto (Set).
 *
 * Define las operaciones básicas que cualquier implementación de un conjunto 
 * debe proveer. Utiliza plantillas (templates) para soportar cualquier tipo 
 * de dato genérico T.
 *
 * @tparam T Tipo de los elementos que almacenará el conjunto.
 */
template <typename T>
class ISet {
protected:
    /** * @brief Cantidad actual de elementos en el conjunto.
     * Marcado como 'protected' (según el diagrama con '#') para que las clases 
     * derivadas puedan acceder a él y actualizarlo.
     */
    std::size_t size = 0;

public:
    /**
     * @brief Destructor virtual por defecto.
     * Regla de oro en C++: toda clase con métodos virtuales DEBE tener un destructor virtual.
     */
    virtual ~ISet() = default;

    /**
     * @brief Obtiene la cantidad de elementos en el conjunto.
     * @return std::size_t La cantidad de elementos.
     */
    virtual std::size_t getSize() const {
        return size;
    }

    /**
     * @brief Verifica si el conjunto está vacío.
     * @return true si el conjunto no tiene elementos, false en caso contrario.
     */
    virtual bool isEmpty() const {
        return size == 0;
    }

    // ========================================================================
    // Métodos puramente virtuales a ser implementados por clases derivadas
    // ========================================================================

    /**
     * @brief Elimina todos los elementos del conjunto.
     */
    virtual void clear() = 0;

    /**
     * @brief Imprime los elementos del conjunto en un flujo de salida.
     */
    virtual void print() const = 0;

    /**
     * @brief Verifica si un elemento específico pertenece al conjunto.
     * @param item Elemento a buscar.
     * @return true si el elemento está en el conjunto, false en caso contrario.
     */
    virtual bool contains(const T& item) const = 0;

    /**
     * @brief Añade un elemento al conjunto.
     * @param item Elemento a añadir.
     * @return true si se añadió con éxito, false si el elemento ya existía.
     */
    virtual bool add(const T& item) = 0;

    /**
     * @brief Elimina un elemento del conjunto.
     * @param item Elemento a eliminar.
     * @return true si se eliminó con éxito, false si el elemento no se encontró.
     */
    virtual bool remove(const T& item) = 0;
};

#endif // ISET_HPP
