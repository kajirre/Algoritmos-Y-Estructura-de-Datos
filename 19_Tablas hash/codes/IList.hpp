#ifndef ILIST_HPP
#define ILIST_HPP

#include <cstddef> // Necesario para std::size_t

/**
 * @brief Interfaz abstracta para una Lista (List).
 *
 * Define las operaciones posicionales y secuenciales que cualquier 
 * implementación de lista (como arreglos dinámicos o listas enlazadas) 
 * debe proveer.
 *
 * @tparam T Tipo de los elementos que almacenará la lista.
 */
template <typename T>
class IList {
protected:
    /** * @brief Cantidad actual de elementos en la lista.
     * Protegido para el acceso directo de las clases derivadas.
     */
    std::size_t size = 0;

public:
    /**
     * @brief Destructor virtual por defecto.
     */
    virtual ~IList() = default;

    /**
     * @brief Obtiene la cantidad de elementos en la lista.
     * @return std::size_t La cantidad de elementos.
     */
    virtual std::size_t getSize() const {
        return size;
    }

    /**
     * @brief Verifica si la lista está vacía.
     * @return true si la lista no tiene elementos, false en caso contrario.
     */
    virtual bool isEmpty() const {
        return size == 0;
    }

    // ========================================================================
    // Métodos puramente virtuales a ser implementados por clases derivadas
    // ========================================================================

    /**
     * @brief Elimina todos los elementos de la lista.
     */
    virtual void clear() = 0;

    /**
     * @brief Imprime los elementos de la lista en orden.
     */
    virtual void print() const = 0;

    /**
     * @brief Obtiene el elemento en una posición específica.
     * @param index Posición del elemento a obtener (basado en 0).
     * @return T Una copia del elemento en la posición dada.
     */
    virtual T get(std::size_t index) const = 0;

    /**
     * @brief Reemplaza el elemento en una posición específica.
     * @param index Posición del elemento a modificar.
     * @param item Nuevo elemento que reemplazará al existente.
     */
    virtual void set(std::size_t index, const T& item) = 0;

    /**
     * @brief Busca la primera aparición de un elemento en la lista.
     * @param item Elemento a buscar.
     * @return int El índice del elemento si se encuentra, o -1 si no existe.
     */
    virtual int indexOf(const T& item) const = 0;

    /**
     * @brief Inserta un elemento en una posición específica, desplazando los demás.
     * @param index Posición donde se insertará el elemento.
     * @param item Elemento a insertar.
     */
    virtual void insertAt(std::size_t index, const T& item) = 0;

    /**
     * @brief Elimina el elemento en una posición específica.
     * @param index Posición del elemento a eliminar.
     */
    virtual void removeAt(std::size_t index) = 0;

    /**
     * @brief Inserta un elemento al principio de la lista.
     * @param item Elemento a insertar.
     */
    virtual void pushFront(const T& item) = 0;

    /**
     * @brief Inserta un elemento al final de la lista.
     * @param item Elemento a insertar.
     */
    virtual void pushBack(const T& item) = 0;

    /**
     * @brief Elimina y retorna el primer elemento de la lista.
     * @return T El elemento que fue eliminado.
     */
    virtual T popFront() = 0;

    /**
     * @brief Elimina y retorna el último elemento de la lista.
     * @return T El elemento que fue eliminado.
     */
    virtual T popBack() = 0;
};

#endif // ILIST_HPP
