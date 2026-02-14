
#ifndef CELULAR_H
#define CELULAR_H

#include <string>

class Celular {
private:
  std::string marca;
  std::string modelo;
  int almacenamiento;
  int ram;
  double precio;

public:
  Celular();
  Celular (std::string marca, std::string modelo, int almacenamiento, int ram, double precio);

  void actualizarMarca(std::string nuevaMarca);
  void actualizarModelo(std::string nuevoModelo);
  void actualizarAlmacenamiento(int nuevoAlmacenamiento)
  void actualizarRam(int nuevaRam);
  void actualizarPrecio(double nuevoPrecio);

  std::string obtenerMarca();
  std::string obtenerModelo();
  int obtenerAlmacenamiento();
  int obtenerRam();
  double obtenerPrecio();

  void mostrarMarca();
  void mostrarCodigo();
  void mostrarAlmacenamiento();
  void mostrarRam();
  void mostrarPrecio();
  void mostrarInformacionCompleta();

  void incrementarPrecio();
    
};
#endif
