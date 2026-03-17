#include "circulo.h"
#include <iostream>

// Constante para el cálculo del área
const double PI = 3.14159;

Circulo::Circulo(std::string nombre, double radio) : Figura(nombre) {
    this->radio = radio;
}

double Circulo::calcularArea() {
    return PI * radio * radio;
}

void Circulo::describir() {
    std::cout << "Figura: " << nombre << ", radio: " << radio << std::endl;
}

double Circulo::obtenerRadio() {
    return radio;
}