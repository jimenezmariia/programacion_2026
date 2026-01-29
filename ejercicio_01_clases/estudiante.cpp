#include <iostream>
#include "estudiante.h"

// Constructor por defecto
Estudiante::Estudiante() {
    nombre = "";
    codigo = "";
    edad = 0;
    promedio = 0.0;
    activo = false;
}

// Constructor con parametros
Estudiante::Estudiante(std::string nombre, std::string codigo, int edad, float promedio, bool activo) {
    this->nombre = nombre;
    this->codigo = codigo;
    this->edad = edad;
    this->activo = activo;
    actualizarPromedio(promedio);
}

// Setters
void Estudiante::actualizarNombre(std::string nuevoNombre) { nombre = nuevoNombre; }
void Estudiante::actualizarCodigo(std::string nuevoCodigo) { codigo = nuevoCodigo; }
void Estudiante::actualizarEdad(int nuevaEdad) { edad = nuevaEdad; }

void Estudiante::actualizarPromedio(float nuevoPromedio) {
    if (nuevoPromedio >= 0 && nuevoPromedio <= 10) {
        promedio = nuevoPromedio;
    } else {
        std::cout << "Error. El promedio debe estar entre 0.0 y 10.0 " << std::endl;
    }
}

void Estudiante::actualizarActivo(bool nuevoEstado) { activo = nuevoEstado; }

// Getters
std::string Estudiante::obtenerNombre() { return nombre; }
std::string Estudiante::obtenerCodigo() { return codigo; }
int Estudiante::obtenerEdad() { return edad; }
float Estudiante::obtenerPromedio() { return promedio; }
bool Estudiante::obtenerActivo() { return activo; }

// Visualización
void Estudiante::mostrarNombre() { std::cout << "Nombre: " << nombre << std::endl; }
void Estudiante::mostrarCodigo() { std::cout << "Código: " << codigo << std::endl; }
void Estudiante::mostrarEdad() { std::cout << "Edad: " << edad << " años" << std::endl; }
void Estudiante::mostrarPromedio() { std::cout << "Promedio: " << promedio << std::endl; }
void Estudiante::mostrarActivo() {
    if (activo) {
        std::cout << "Estado: Activo" << std::endl;
    } else {
        std::cout << "Estado: Inactivo" << std::endl;
    }
}

void Estudiante::mostrarInformacionCompleta() {
    mostrarNombre();
    mostrarCodigo();
    mostrarEdad();
    mostrarPromedio();
    mostrarActivo();
}

// Utilidad
void Estudiante::incrementarEdad() {
    edad++;
}

void Estudiante::calcularEstadoAcademico() {
    if (promedio >= 9.0 && promedio <= 10) {
        std::cout << "Estado académico: Excelente" << std::endl;
    } else if (promedio >= 8.0 && promedio < 9.0) {
        std::cout << "Estado académico: Muy bueno" << std::endl;
    } else if (promedio >= 7.0 && promedio < 8.0) {
        std::cout << "Estado académico: Bueno" << std::endl;
    } else if (promedio >= 6.0 && promedio < 7.0) {
        std::cout << "Estado académico: Regular" << std::endl;
    } else {
        std::cout << "Estado académico: Necesita mejorar" << std::endl;
    }
}