#include <iostream>
#include <vector>
#include <random>

/*
int main(){
    //1. Declaramos el vector con nombre (ej. "misNumeros")
    // Esto va crear un vector de 10 elementos todos incializados en 5
    std::vector<int> misNumeros(10, 5);

    //2. Usamos un bucle "for" para recorrer el vector
    for (int n : misNumeros) {
        std::cout << n <<  " " ;
    }
    std::cout << "\n";
    return 0;
}
*/
int main(){

    int elementos;

    //1. creamos un vector para 1o elementos
    std::vector<int> numeros;

    //2. Configuramos el generador de numeros aleatorios
    std::random_device rd; //obtiene una semilla de hardware
    std::mt19937 gen(rd());  // generador mersene twister
    std::uniform_int_distribution<> distribucion(1, 100); // Rando de 1 a 100

    std::cout << "Ingrese el numero de elementos: "; std::cin >> elementos;

    //3. llenamos el vector usando un bucle
    for (int i = 0; i < elementos; i++) {
        numeros.push_back(distribucion(gen));
    }

    //4. Imprimimos el resultado para verificar
    std::cout << "Elementos aleatorios" << "\n";
    for (int n : numeros){
        std::cout << n << " ";
    }
    return 0;
}