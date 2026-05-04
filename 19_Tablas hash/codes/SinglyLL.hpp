#ifndef SINGLYLL_HPP
#define SINGLYLL_HPP

#include "IList.hpp"
#include "Node.hpp"
#include <iostream>
#include <stdexcept>

/**
 * @brief Implementación de una Lista Enlazada Simple (Singly Linked List).
 *
 * Utiliza nodos conectados secuencialmente. Ofrece inserción y eliminación
 * eficiente al principio de la lista (O(1)), pero acceso por índice lineal (O(N)).
 *
 * @tparam T Tipo de los elementos que almacenará la lista.
 */
template <typename T>
class SinglyLL : public IList<T> {
protected:
    /** @brief Puntero al primer nodo de la lista. */
    Node<T>* head;

public:
    /**
     * @brief Constructor por defecto. Inicializa la lista vacía.
     */
    SinglyLL() : head(nullptr) {
        this->size = 0;
    }

    /**
     * @brief Destructor. Libera la memoria de todos los nodos.
     */
    ~SinglyLL() override {
        clear();
    }

    /**
     * @brief Obtiene el puntero al nodo cabeza.
     * @return Node<T>* Puntero al primer nodo.
     */
    Node<T>* getHead() const {
        return head;
    }

    /**
     * @brief Establece un nuevo nodo como cabeza de la lista.
     * @note Este método altera la estructura y podría causar fugas de memoria 
     * si no se maneja con cuidado desde el exterior.
     * @param node Puntero al nuevo nodo cabeza.
     */
    void setHead(Node<T>* node) {
        head = node;
    }

    // ========================================================================
    // Implementación de los métodos de IList
    // ========================================================================

    void clear() override {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->getNext();
            delete current;
            current = nextNode;
        }
        head = nullptr;
        this->size = 0;
    }

    void print() const override {
        Node<T>* current = head;
        std::cout << "[";
        while (current != nullptr) {
            std::cout << current->getData();
            if (current->getNext() != nullptr) {
                std::cout << " -> ";
            }
            current = current->getNext();
        }
        std::cout << "]\n";
    }

    T get(std::size_t index) const override {
        if (index >= this->size) {
            throw std::out_of_range("Índice fuera de rango en get()");
        }
        Node<T>* current = head;
        for (std::size_t i = 0; i < index; ++i) {
            current = current->getNext();
        }
        return current->getData();
    }

    void set(std::size_t index, const T& item) override {
        if (index >= this->size) {
            throw std::out_of_range("Índice fuera de rango en set()");
        }
        Node<T>* current = head;
        for (std::size_t i = 0; i < index; ++i) {
            current = current->getNext();
        }
        current->data = item; // Acceso directo al dato público del nodo
    }

    int indexOf(const T& item) const override {
        Node<T>* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->getData() == item) {
                return index;
            }
            current = current->getNext();
            index++;
        }
        return -1; // No encontrado
    }

    void insertAt(std::size_t index, const T& item) override {
        if (index > this->size) {
            throw std::out_of_range("Índice fuera de rango en insertAt()");
        }
        if (index == 0) {
            pushFront(item);
            return;
        }

        // Llegar al nodo ANTERIOR al índice de inserción
        Node<T>* current = head;
        for (std::size_t i = 0; i < index - 1; ++i) {
            current = current->getNext();
        }

        Node<T>* newNode = new Node<T>(item, current->getNext());
        current->setNext(newNode);
        this->size++;
    }

    void removeAt(std::size_t index) override {
        if (index >= this->size) {
            throw std::out_of_range("Índice fuera de rango en removeAt()");
        }
        if (index == 0) {
            popFront();
            return;
        }

        // Llegar al nodo ANTERIOR al que queremos eliminar
        Node<T>* current = head;
        for (std::size_t i = 0; i < index - 1; ++i) {
            current = current->getNext();
        }

        Node<T>* nodeToDelete = current->getNext();
        current->setNext(nodeToDelete->getNext());
        delete nodeToDelete;
        this->size--;
    }

    void pushFront(const T& item) override {
        Node<T>* newNode = new Node<T>(item, head);
        head = newNode;
        this->size++;
    }

    void pushBack(const T& item) override {
        if (this->isEmpty()) {
            pushFront(item);
            return;
        }

        Node<T>* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(new Node<T>(item));
        this->size++;
    }

    T popFront() override {
        if (this->isEmpty()) {
            throw std::out_of_range("La lista está vacía en popFront()");
        }
        Node<T>* oldHead = head;
        T item = oldHead->getData();
        head = head->getNext();
        delete oldHead;
        this->size--;
        return item;
    }

    T popBack() override {
        if (this->isEmpty()) {
            throw std::out_of_range("La lista está vacía en popBack()");
        }
        if (this->size == 1) {
            return popFront();
        }

        // Llegar al PENÚLTIMO nodo
        Node<T>* current = head;
        while (current->getNext()->getNext() != nullptr) {
            current = current->getNext();
        }

        Node<T>* nodeToDelete = current->getNext();
        T item = nodeToDelete->getData();
        delete nodeToDelete;
        current->setNext(nullptr);
        this->size--;
        return item;
    }
};

#endif // SINGLYLL_HPP
