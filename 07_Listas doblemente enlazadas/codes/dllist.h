#ifndef DLLIST_H
#define DLLIST_H

#include "ilist.h"
#include <stdexcept>
#include <iostream>
#include <utility> // Necesario para std::exchange y std::move

// --- Estructura del Nodo ---
template <typename T>
struct DNode {
    T data;
    DNode* prev;
    DNode* next;

    // Constructor por defecto (para el Dummy)
    DNode() : prev(nullptr), next(nullptr) {}

    // Constructor copia
    DNode(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    
    // Constructor movimiento (Opcional, pero recomendado para T complejos)
    DNode(T&& val) : data(std::move(val)), prev(nullptr), next(nullptr) {}
};

/**
 * Lista Doblemente Enlazada Circular con Nodo Centinela (Dummy).
 * Implementa IList y Semántica de Movimiento completa.
 */
template <typename T>
class DLList : public IList<T> {
private:
    DNode<T>* dummy; // Nodo centinela
    size_t size;

    // Método auxiliar para localizar nodos
    DNode<T>* getNode(size_t index) const {
        if (index < 0 || index >= size) return nullptr;

        DNode<T>* curr;
        if (index < size / 2) {
            curr = dummy->next;
            for (size_t i = 0; i < index; ++i) curr = curr->next;
        } else {
            curr = dummy->prev;
            for (size_t i = size - 1; i > index; --i) curr = curr->prev;
        }
        return curr;
    }

    void init() {
        dummy = new DNode<T>();
        dummy->next = dummy;
        dummy->prev = dummy;
        size = 0;
    }

public:
    // ==========================================
    // 1. Constructores y Destructores
    // ==========================================

    DLList() { init(); }

    virtual ~DLList() {
        // Importante verificar dummy por si el objeto fue movido (moved-from state)
        if (dummy) {
            clear();
            delete dummy;
        }
    }

    // --- Constructor de Copia (Deep Copy) ---
    DLList(const DLList& other) {
        init();
        for (auto it = other.begin(); it != other.end(); ++it) {
            pushBack(*it);
        }
    }

    // Constructor por Movimiento (Move Constructor)
    // Usa std::exchange para "robar" los punteros y dejar al otro en nullptr/0
    DLList(DLList&& other) noexcept 
        : dummy(std::exchange(other.dummy, nullptr)), 
          size(std::exchange(other.size, 0)) {
    }

    // Operador de Asignación por Movimiento (Move Assignment)
    DLList& operator=(DLList&& other) noexcept {
        if (this != &other) {
            // 1. Liberar recursos propios
            if (dummy) {
                clear();
                delete dummy;
            }

            // 2. Robar recursos del otro
            dummy = std::exchange(other.dummy, nullptr);
            size = std::exchange(other.size, 0);
        }
        return *this;
    }

    // ==========================================
    // 2. Iteradores Bidireccionales
    // ==========================================
    
    class Iterator {
    private:
        DNode<T>* curr;
    public:
        // Rasgos (Traits) para compatibilidad con STL
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(DNode<T>* ptr) : curr(ptr) {}

        T& operator*() { return curr->data; }
        DNode<T>* getNode() { return curr; } 

        Iterator& operator++() { // ++it
            curr = curr->next;
            return *this;
        }

        Iterator operator++(int) { // it++
            Iterator temp = *this;
            curr = curr->next;
            return temp;
        }

        Iterator& operator--() { // --it
            curr = curr->prev;
            return *this;
        }

        bool operator!=(const Iterator& other) const { return curr != other.curr; }
        bool operator==(const Iterator& other) const { return curr == other.curr; }
    };

    Iterator begin() const { return Iterator(dummy ? dummy->next : nullptr); }
    Iterator end() const { return Iterator(dummy); }

    // ==========================================
    // 3. Implementación de IList
    // ==========================================

    void pushBack(const T& item) override {
        if (!dummy) init(); 
        DNode<T>* newNode = new DNode<T>(item);
        DNode<T>* tail = dummy->prev; 

        newNode->next = dummy;
        newNode->prev = tail;
        tail->next = newNode;
        dummy->prev = newNode;
        size++;
    }

    void pushFront(const T& item) override {
        if (!dummy) init();
        DNode<T>* newNode = new DNode<T>(item);
        DNode<T>* head = dummy->next;

        newNode->prev = dummy;
        newNode->next = head;
        head->prev = newNode;
        dummy->next = newNode;
        size++;
    }

    void insertAt(size_t index, const T& item) override {
        if (index > size) throw std::out_of_range("Indice fuera de rango"); // index puede ser igual a size
        if (index == size) { pushBack(item); return; }
        if (index == 0) { pushFront(item); return; }

        DNode<T>* current = getNode(index);
        DNode<T>* prevNode = current->prev;
        DNode<T>* newNode = new DNode<T>(item);

        newNode->prev = prevNode;
        newNode->next = current;
        prevNode->next = newNode;
        current->prev = newNode;
        size++;
    }

    void removeAt(size_t index) override {
        if (index >= size) throw std::out_of_range("Indice fuera de rango");
        DNode<T>* toDelete = getNode(index);
        
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        delete toDelete;
        size--;
    }

    void popFront() override { if (!isEmpty()) removeAt(0); }
    void popBack() override { if (!isEmpty()) removeAt(size - 1); }

    void clear() override {
        if (!dummy) return;
        while (size > 0) popFront();
    }

    T get(size_t index) const override {
        DNode<T>* node = getNode(index);
        if (!node) throw std::out_of_range("Indice fuera de rango");
        return node->data;
    }

    size_t getSize() const override { return size; }
    bool isEmpty() const override { return size == 0; }

    void print() const override {
        if (!dummy || size == 0) {
            std::cout << "[]" << std::endl;
            return;
        }
        DNode<T>* curr = dummy->next;
        std::cout << "[ ";
        while (curr != dummy) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << "]" << std::endl;
    }
};

#endif // DLLIST_H
