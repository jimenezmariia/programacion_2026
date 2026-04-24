// Polimorfismo.
#include <iostream>
#include <stdlib.h>

using namespace std;

class Persona {
private:
    string nombre;
    int edad;
public:
    Persona(string, int);
    virtual void mostrar();
};

class Alumno : public Persona {
private:
    float notaFinal;
public:
    Alumno(string, int, float);
    void mostrar();
};

class Profesor : public Persona {
private:
    string materia;
public:
    Profesor(string, int, string);
    void mostrar();
};

// Implementación de métodos de Persona
Persona::Persona(string _nombre, int _edad) {
    nombre = _nombre;
    edad = _edad;
}

void Persona::mostrar() {
    cout << "Nombre: " << nombre << endl;
    cout << "Edad: " << edad << endl;
}

// Implementación de métodos de Alumno
Alumno::Alumno(string _nombre, int _edad, float _notaFinal) : Persona(_nombre, _edad) {
    notaFinal = _notaFinal;
}

void Alumno::mostrar() {
    Persona::mostrar();
    cout << "Nota Final: " << notaFinal << endl;
}

// Implementación de métodos de Profesor
Profesor::Profesor(string _nombre, int _edad, string _materia) : Persona(_nombre, _edad) {
    materia = _materia;
}

void Profesor::mostrar() {
    Persona::mostrar();
    cout << "Materia: " << materia << endl;
}

int main() {
    Persona *vector[3];

    vector[0] = new Alumno("Alejandro", 20, 18.9);
    vector[1] = new Alumno("Maria", 19, 15.5);
    vector[2] = new Profesor("Jose", 25, "Algoritmos");

    vector[0]->mostrar();
    cout << "\n";
    vector[1]->mostrar();
    cout << "\n";
    vector[2]->mostrar();

    system("pause");
    return 0;
}
