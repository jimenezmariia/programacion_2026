#include <iostream>
#include "figura.h"
#include "circulo.h"
#include "rectangulo.h"

int main() {
    std::cout << "=== Sistema de Figuras Geométricas (Polimorfismo) ===" << std::endl;
    std::cout << std::endl;

    // Punteros a la clase base que apuntan a objetos derivados
    Figura* f1 = new Circulo("Círculo", 5.0);
    Figura* f2 = new Rectangulo("Rectángulo", 4.0, 6.0);

    std::cout << "--- Figura 1 (Círculo) ---" << std::endl;
    f1->describir();
    std::cout << "Área: " << f1->calcularArea() << std::endl;
    std::cout << std::endl;

    std::cout << "--- Figura 2 (Rectángulo) ---" << std::endl;
    f2->describir();
    std::cout << "Área: " << f2->calcularArea() << std::endl;
    std::cout << std::endl;

    // Polimorfismo
    std::cout << "--- Tratamiento uniforme con Figura* ---" << std::endl;
    Figura* figuras[] = { f1, f2 };
    for (int i = 0; i < 2; i++) {
        figuras[i]->describir();
        std::cout << "Área: " << figuras[i]->calcularArea() << std::endl;
    }

    // Liberamos la memoria dinámica
    delete f1;
    delete f2;

    return 0;
}