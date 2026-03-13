#include <iostream>

class Punto {
public:
    double x, y;
    Punto(double _x, double _y) : x(_x), y(_y) {
        std::cout << "[Constructor]: Punto creado en " << this << "\n";
    }
};

int main() {
    std::cout << "--- 1. Objetos y Punteros ---\n";
    // Objeto en el Stack (Pila)
    Punto p1(1.0, 2.0);
    std::cout << "Punto 1 (Stack): (" << p1.x << ", " << p1.y << ")\n";

    // Objeto en el Heap (Dinámico)
    Punto* p2 = new Punto(10.5, 20.5);
    std::cout << "Punto 2 (Heap) via puntero: (" << p2->x << ", " << p2->y << ")\n";

    delete p2; // Importante: Liberar memoria manual
    return 0;
}
