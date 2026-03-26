#include "Celular.h"

// Constructor: Inicializa valores básicos
Celular::Celular(string _marca, string _modelo, float _precio) {
    marca = _marca;
    modelo = _modelo;
    precio = _precio;
    bateria = 50;     // Inicia con 50% por defecto
    encendido = false; // Inicia apagado
}

void Celular::encender() {
    encendido = true;
    cout << "El celular " << modelo << " se ha encendido." << endl;
}

void Celular::cargar(int porcentaje) {
    bateria += porcentaje;
    if (bateria > 100) bateria = 100;
    cout << "Cargando... Bateria actual: " << bateria << "%" << endl;
}

void Celular::mostrarInfo() {
    cout << "Marca: " << marca << " | Modelo: " << modelo << " | Precio: $" << precio << endl;
}