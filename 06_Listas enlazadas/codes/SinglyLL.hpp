#ifndef SINGLY_HPP
#define SINGLY_HPP

#include <iostream>
#include <utility>	// Para usar std::move
#include <stdexcept>    // Para excepciones

// Estructura de Nodo
template <typename T>
struct Node {
    T data;
    Node* next;

    // 1. Constructor por Copia (El clásico)
    // Se usa cuando pasas una variable que quieres conservar (l-value)
    Node(const T& value) : data(value), next(nullptr) {}

    // 2. Constructor por Movimiento (La optimización)
    // Se usa cuando pasas un temporal (r-value) o usas std::move()
    Node(T&& value) : data(std::move(value)), next(nullptr) {}
};



template <typename T>
class SinglyLL {
private:
    Node<T>* head; // Puntero al primer nodo
    int size;      // Contador de elementos

public:
    // Constructor
    SinglyLL() {
        head = nullptr; // La lista inicia vacía
        size = 0;
    }

    // Move Constructor
    // Al usar 'noexcept', permitimos que contenedores como std::vector
    // usen esta optimización automáticamente al redimensionarse.
    SinglyLL(SinglyLL&& other) noexcept {
        // 1. Robo de recursos (Punteros y contadores)
        this->head = other.head;
        this->size = other.size;

        // 2. Anulación de la fuente (Para evitar doble liberación)
        other.head = nullptr;
        other.size = 0;
    }

    // Destructor (Esqueleto inicial)
    ~SinglyLL() {
        clear();
    }

    // Limpieza de memoria O(n)
    void clear() {
        while (head != nullptr) {
            popFront();
        }
    }

    // Método de acceso (Getter)
    int getSize() const {
        return size;
    }
    
    // Método para verificar si está vacía
    bool isEmpty() const {
        return head == nullptr;
    }
    
    // --- METODOS DE INSERCION ---

    // Insercion al inicio
    void pushFront(T value) {
         // 1. Crear nodo (Invoca al constructor optimizado)
         Node<T>* newNode = new Node<T>(std::move(value));

         // 2. Conectar el nuevo nodo al antiguo frente
         newNode->next = head;

         // 3. Actualizar la "etiqueta" head
         head = newNode;

         // 4. Actualizar contabilidad
         size++;
    }


    // Insersion al final
    void pushBack(T value) {
        Node<T>* newNode = new Node<T>(std::move(value));

        // CASO 1: Lista vacía
        if (head == nullptr) {
            head = newNode;
            size++;
            return;
        }

        // CASO 2: Lista con elementos (Recorrido O(n))
        Node<T>* current = head;
    
        // Avanzamos hasta que current->next sea NULL (el último nodo)
        while (current->next != nullptr) {
            current = current->next;
        }

        // "Cableamos" el último nodo al nuevo
        current->next = newNode;
        size++;
    }


    // Inserción Arbitraria
    void insertAt(int index, T value) {
        // 1. Validación de límites
        if (index < 0 || index > size) {
            throw std::out_of_range("Indice fuera de rango");
        }

        // 2. Optimización: Inserción al inicio
        if (index == 0) {
            pushFront(std::move(value));
            return;
        }

        // 3. Optimización: Inserción al final
        if (index == size) {
            pushBack(std::move(value));
            return;
        }

        // 4. Lógica General: Buscar el nodo PREVIO (index - 1)
        Node<T>* newNode = new Node<T>(std::move(value));
        Node<T>* current = head;

        // Ciclo para llegar justo antes de la posición deseada
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }

        // 5. El "Baile de Punteros" (El orden importa)
        newNode->next = current->next; // El nuevo apunta al siguiente del actual
        current->next = newNode;       // El actual apunta al nuevo
        // Actualizacion de tamano
        size++;
    }

    // --- METODOS DE ELIMINACION ---

    // Eliminar al inicio
    void popFront() {
        if (head == nullptr) return; // Nada que borrar

        Node<T>* temp = head; // Respaldar para no perderlo
        head = head->next;    // Avanzar head
        delete temp;          // Liberar memoria del viejo head
        size--;
    }

    // Eliminar al final
    void popBack() {
        if (head == nullptr) return;

        if (head->next == nullptr) { // Solo hay un elemento
            delete head;
            head = nullptr;
            size--;
            return;
        }

        // Buscar el penúltimo
        Node<T>* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }

        delete temp->next; // Borrar el último
        temp->next = nullptr; // El penúltimo ahora es el último
        size--;
    }

    // Eliminar en índice arbitrario
    void removeAt(int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Indice invalido");

        if (index == 0) { popFront(); return; }

        // Buscar el nodo PREVIO
        Node<T>* temp = head;
        for(int i=0; i<index-1; ++i) temp = temp->next;

        Node<T>* toDelete = temp->next; // El nodo a matar
        temp->next = toDelete->next;    // Puenteo
        delete toDelete;                // Liberación
        size--;
    }

    // UTILIDAD PARA VER RESULTADOS
    void print() const {
        Node<T>* current = head;
        std::cout << "[HEAD] -> ";
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};


#endif // SINGLY_HPP

