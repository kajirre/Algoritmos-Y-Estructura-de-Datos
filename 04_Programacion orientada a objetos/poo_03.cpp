#include <iostream>
#include <cmath>

// 1. PRIMERO definimos la clase base
class Punto {
private:
    double x, y;

public:
    Punto(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    // Método de cálculo de distancia (usando this y referencia)
    double calcularDistancia(const Punto& otro) const {
        return std::sqrt(std::pow(otro.x - this->x, 2) + std::pow(otro.y - this->y, 2));
    }

    void mostrar() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};

// 2. SEGUNDO definimos la clase que usa a la anterior (Composición)
class Camino {
private:
    Punto* puntos;      // Ahora el compilador ya sabe qué es 'Punto'
    int capacidad;
    int contador;

public:
    Camino(int maxPuntos) : capacidad(maxPuntos), contador(0) {
        puntos = new Punto[capacidad]; 
        std::cout << "[Camino]: Memoria reservada para " << capacidad << " puntos.\n";
    }

    ~Camino() {
        delete[] puntos;
        std::cout << "[Destructor]: Memoria del arreglo liberada.\n";
    }

    void agregarPunto(const Punto& p) {
        if (contador < capacidad) {
            puntos[contador++] = p;
        }
    }

    double calcularTrayectoTotal() {
        double total = 0;
        for (int i = 0; i < contador - 1; i++) {
            total += puntos[i].calcularDistancia(puntos[i+1]);
        }
        return total;
    }
};

int main() {
    Camino miViaje(5);
    miViaje.agregarPunto(Punto(0, 0));
    miViaje.agregarPunto(Punto(0, 10));
    miViaje.agregarPunto(Punto(10, 10));

    std::cout << "Distancia total: " << miViaje.calcularTrayectoTotal() << " unidades.\n";
    return 0;
}
