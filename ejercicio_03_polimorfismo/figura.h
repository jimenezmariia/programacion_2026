#ifndef FIGURA_H
#define FIGURA_H

#include <string>

class Figura {
protected:
    std::string nombre;

public:
    // Constructor
    Figura(std::string nombre);
    
    // Destructor virtual
    virtual ~Figura();

    // Funciones virtuales
    virtual double calcularArea() = 0;
    virtual void describir() = 0;

    // Getter
    std::string obtenerNombre();
};

#endif