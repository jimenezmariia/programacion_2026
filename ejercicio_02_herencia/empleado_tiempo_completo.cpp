#include "empleado_tiempo_completo.h"
#include <iostream>

EmpleadoTiempoCompleto::EmpleadoTiempoCompleto() 
    : Empleado(), horasSemanales(0), bono(0.0f) {}

EmpleadoTiempoCompleto::EmpleadoTiempoCompleto(std::string nombre, std::string id, float salarioBase, 
                                               int horasSemanales, float bono)
    : Empleado(nombre, id, salarioBase), horasSemanales(horasSemanales), bono(bono) {}

void EmpleadoTiempoCompleto::actualizarHorasSemanales(int horasSemanales) {
    this->horasSemanales = horasSemanales;
}

void EmpleadoTiempoCompleto::actualizarBono(float bono) {
    this->bono = bono;
}

int EmpleadoTiempoCompleto::obtenerHorasSemanales() const {
    return horasSemanales;
}

float EmpleadoTiempoCompleto::obtenerBono() const {
    return bono;
}

void EmpleadoTiempoCompleto::mostrarInformacion() const {
    Empleado::mostrarInformacion();
    std::cout << "Horas semanales: " << horasSemanales << std::endl;
    std::cout << "Bono: " << bono << std::endl;
}

float EmpleadoTiempoCompleto::calcularSalarioTotal() const {
    return salarioBase + bono;
}
