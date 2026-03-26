#ifndef CELULAR_H
#define CELULAR_H
#include <iostream>
#include <string>

using namespace std;

class Celular {
private:
    // 5 Atributos
    string marca;
    string modelo;
    int bateria;
    float precio;
    bool encendido;

public:
    // Constructor
    Celular(string _marca, string _modelo, float _precio);

    // 3 Métodos
    void encender();
    void cargar(int porcentaje);
    void mostrarInfo();
};

#endif