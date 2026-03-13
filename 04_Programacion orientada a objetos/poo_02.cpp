#include <iostream>
#include <cmath>

class Punto {
private:
    double x, y; // Datos privados (Encapsulamiento)

public:
    Punto(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    // Paso por referencia para eficiencia
    double calcularDistancia(const Punto& otro) const {
        return std::sqrt(std::pow(otro.x - this->x, 2) + std::pow(otro.y - this->y, 2));
    }

    // Getters necesarios porque los datos son privados
    double getX() const { return x; }
    double getY() const { return y; }
};

int main() {
    std::cout << "\n--- Encapsulamiento y Referencias ---\n";
    Punto a(0, 0), b(3, 4);
    // Pasamos 'b' por referencia, no se crea una copia de 'b' en el stack
    std::cout << "Distancia de A a B: " << a.calcularDistancia(b) << "\n";
    return 0;
}
