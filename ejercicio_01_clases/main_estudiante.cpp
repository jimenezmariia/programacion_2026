#include <iostream>
#include "estudiante.h"

int main() {
    std::cout << "---- SISTEMA DE GESTIÓN DE ESTUDIANTE ----" << std::endl << std::endl;

    //Constructor por defecto
    Estudiante estudiante1;
    std::cout << "Estudiante 1 (constructor por defecto):" <<std::endl;
    estudiante1.mostrarInformacionCompleta();
    std::cout << std::endl;

    //Actualizar Atributos
    estudiante1.actualizarNombre("María García López");
    estudiante1.actualizarCodigo("EST-2024-01");
    estudiante1.actualizarEdad(20);
    estudiante1.actualizarPromedio(9.2);
    estudiante1.actualizarActivo(true);

    //Mostrar Información
    std::cout << "Estudiante 1 después de actualizar:" << std::endl;
    estudiante1.mostrarInformacionCompleta();
    estudiante1.calcularEstadoAcademico();
    std::cout << std::endl;

    Estudiante estudiante2("Juan Pérez Martínez", "EST-2024-002",22,7.5,true);
    std::cout << "Estudiante 2 (constructor con parámetros):" << std::endl;
    estudiante2.mostrarInformacionCompleta();
    estudiante2.calcularEstadoAcademico();
    std::cout << std::endl;

    //Incrementar edad
    std::cout << "Incrementando edad del estudiante 2:" << std::endl;
    estudiante2.incrementarEdad();
    estudiante2.mostrarEdad();
    std::cout << std::endl;

    //Probar validación de promedio
    std::cout << "Intentando actualizar promedio con valor inválido:" << std::endl;
    estudiante2.actualizarPromedio(15.0);
    estudiante2.mostrarPromedio();
    std::cout << std::endl;

    return 0;
}