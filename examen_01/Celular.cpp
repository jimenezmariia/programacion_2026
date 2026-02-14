#include "Celular.h"
#include <iostream>

Celular::Celular() {
    marca = "";
    modelo = "";
    almacenamiento = 0;
    ram = 0;
    precio = 0.0;
}

Celular::Celular(std::string marca, std::string modelo, int almacenamiento, int ram, double precio) {
    this->marca = marca;
    this->modelo = modelo;
    this->almacenamiento = almacenamiento;
    this->ram = ram;
    this->precio = precio;
}

void Celular::actualizarMarca(std::string nuevaMarca) {
    marca = nuevaMarca;
}

void Celular::actualizarModelo(std::string nuevoModelo) {
    modelo = nuevoModelo;
}

void Celular::actualizarAlmacenamiento(int nuevoAlmacenamiento) {
    almacenamiento = nuevoAlmacenamiento;
}

void Celular::actualizarRam(int nuevaRam) {
    ram = nuevaRam;
}

void Celular::actualizarPrecio(double nuevoPrecio) {
    precio = nuevoPrecio;
}

std::string Celular::obtenerMarca() {
    return marca;
}

std::string Celular::obtenerModelo() {
    return modelo;
}

int Celular::obtenerAlmacenamiento() {
    return almacenamiento;
}

int Celular::obtenerRam() {
    return ram;
}

double Celular::obtenerPrecio() {
    return precio;
}

void Celular::mostrarMarca() {
    std::cout << "Marca: " << marca << std::endl;
}

void Celular::mostrarCodigo() {
    std::cout << "Modelo: " << modelo << std::endl;
}

void Celular::mostrarAlmacenamiento() {
    std::cout << "Almacenamiento: " << almacenamiento << "GB" << std::endl;
}

void Celular::mostrarRam() {
    std::cout << "RAM: " << ram << "GB" << std::endl;
}

void Celular::mostrarPrecio() {
    std::cout << "Precio: $" << precio << std::endl;
}

void Celular::mostrarInformacionCompleta() {
    std::cout << "Celular: " << marca << " " << modelo 
              << " | RAM: " << ram << "GB | ROM: " << almacenamiento 
              << "GB | Precio: $" << precio << std::endl;
}

void Celular::incrementarPrecio() {
    precio += 1.0;
}
