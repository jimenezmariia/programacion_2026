#ifndef CIRCULO_H
#define CIRCULO_H

#include "figura.h"

class Circulo : public Figura {
private:
    double radio;

public:
    Circulo(std::string nombre, double radio);

    double calcularArea() override;
    void describir() override;

    double obtenerRadio();
};

#endif