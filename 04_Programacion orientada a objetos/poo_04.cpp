#include <iostream>
#include <cmath>

// 1. EL MOLDE: Clase Punto
class Punto {
private:
    double x, y;
public:
    Punto(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    double calcularDistancia(const Punto& otro) const {
        // Explicación de 'this': Mi X vs la X del otro punto
        return std::sqrt(std::pow(otro.x - this->x, 2) + std::pow(otro.y - this->y, 2));
    }

    void mostrar() const { std::cout << "(" << x << ", " << y << ")"; }
};

// 2. LA ESTRUCTURA: Clase Camino (Gestión de Memoria Dinámica)
class Camino {
protected:
    Punto* puntos;
    int capacidad;
    int contador;

public:
    Camino(int n) : capacidad(n), contador(0) {
        puntos = new Punto[capacidad]; // Reserva en el HEAP
        std::cout << "\n[MEMORIA]: Se han reservado " << capacidad * sizeof(Punto) 
                  << " bytes para " << capacidad << " puntos.\n";
    }

    virtual ~Camino() {
        delete[] puntos; // Limpieza del HEAP
        std::cout << "[MEMORIA]: Destructor ejecutado. Memoria del arreglo liberada.\n";
    }

    void agregarPunto(Punto p) {
        if (contador < capacidad) {
            puntos[contador] = p;
            std::cout << "[OBJETO]: Punto " << contador << " guardado en el arreglo.\n";
            contador++;
        }
    }

    double obtenerLongitud() const {
        double total = 0;
        for (int i = 0; i < contador - 1; i++) {
            total += puntos[i].calcularDistancia(puntos[i+1]);
        }
        return total;
    }
};

// 3. LA ESPECIALIZACIÓN: Clase CaminoFisico (Herencia)
class CaminoFisico : public Camino {
public:
    // Reutiliza el constructor del padre
    CaminoFisico(int n) : Camino(n) {}

    void mostrarAnalisis(double fuerzaN) {
        double dist = obtenerLongitud(); // Uso de método heredado
        std::cout << "\n--- ANALISIS FISICO DEL TRAYECTO ---\n";
        std::cout << "Distancia total recorrida: " << dist << " metros.\n";
        std::cout << "Trabajo realizado (F=" << fuerzaN << "N): " << dist * fuerzaN << " Joules.\n";
        std::cout << "------------------------------------\n";
    }
};

// 4. EJECUCIÓN PEDAGÓGICA
int main() {
    std::cout << ">>> INICIO DE LA CLASE DE POO <<<\n";

    // Creamos un camino con capacidad para 20 puntos, pero usaremos 3
    CaminoFisico* miTrayecto = new CaminoFisico(20);

    miTrayecto->agregarPunto(Punto(0, 0));
    miTrayecto->agregarPunto(Punto(3, 0));
    miTrayecto->agregarPunto(Punto(3, 4));

    // Mostramos la potencia de la herencia y el cálculo
    miTrayecto->mostrarAnalisis(10.5);

    // Al borrar el puntero, se dispara la cadena de destructores
    delete miTrayecto; 

    std::cout << "\n>>> FIN DE LA CLASE: Memoria limpia <<<\n";
    return 0;
}
