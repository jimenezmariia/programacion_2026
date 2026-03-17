#include "figura.h"

Figura::Figura(std::string nombre) {
    this->nombre = nombre;
}

Figura::~Figura() {

}

std::string Figura::obtenerNombre() {
    return nombre;
}