#include "empleado.h"
#include <iostream>

Empleado::Empleado() : nombre(""), id(""), salarioBase(0.0f) {}

Empleado::Empleado(std::string nombre, std::string id, float salarioBase)
    : nombre(nombre), id(id), salarioBase(salarioBase) {}

void Empleado::actualizarNombre(std::string nombre) {
    this->nombre = nombre;
}

void Empleado::actualizarId(std::string id) {
    this->id = id;
}

void Empleado::actualizarSalarioBase(float salarioBase) {
    this->salarioBase = salarioBase;
}

std::string Empleado::obtenerNombre() const {
    return nombre;
}

std::string Empleado::obtenerId() const {
    return id;
}

float Empleado::obtenerSalarioBase() const {
    return salarioBase;
}

void Empleado::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Salario base: " << salarioBase << std::endl;
}
