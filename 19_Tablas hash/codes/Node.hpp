#ifndef NODE_HPP
#define NODE_HPP

/**
 * @brief Clase que representa un nodo individual en una estructura enlazada.
 *
 * Cada nodo almacena un dato genérico y un puntero hacia el siguiente
 * nodo en la secuencia.
 *
 * @tparam T Tipo de dato que almacenará el nodo.
 */
template <typename T>
class Node {
public:
    /** @brief Dato almacenado en el nodo. */
    T data;

    /** @brief Puntero al siguiente nodo en la secuencia. */
    Node<T>* next;

    /**
     * @brief Constructor principal del nodo.
     * * @param item El dato a almacenar. Pasado por referencia constante por eficiencia.
     * @param nextNode Puntero al siguiente nodo. Por defecto se inicializa en nullptr.
     */
    explicit Node(const T& item, Node<T>* nextNode = nullptr) 
        : data(item), next(nextNode) {}

    /**
     * @brief Obtiene el dato almacenado en este nodo.
     * @return T Una copia del dato.
     */
    T getData() const {
        return data;
    }

    /**
     * @brief Obtiene el puntero al siguiente nodo.
     * @return Node<T>* El puntero al siguiente nodo.
     */
    Node<T>* getNext() const {
        return next;
    }

    /**
     * @brief Establece el puntero hacia el siguiente nodo.
     * @param node Puntero que se asignará como siguiente.
     */
    void setNext(Node<T>* node) {
        next = node;
    }
};

#endif // NODE_HPP
