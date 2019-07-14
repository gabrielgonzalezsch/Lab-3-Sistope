#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>


typedef struct Llamada{

  int id;
  double tiempoLlamada;
  int piso_inicial;
  int piso_destino;
  int direccion;
  int num_pasajeros;
  double tiempoDeEspera;
  int atendidaBandera;  // Si fue atendida la llamada o no;

} Llamada;

typedef struct Ascensor{

  int id;
  int piso_actual; // piso actual en el que se encuentra el ascensor
  int direccion; // Si el ascensor se dirige '0' abajo o '1' arriba
  int capacidad_pasajeros; // Capacidad total de pasajeros que entran en el ascensor
  int cantidad_pasajeros; //  Cantidad de pasajeros actual en el ascensor
  int estado;   // si se encuentra inactivo '0' o activo '1'
  double FS; // Variable de valor que influye en el llamado(Figure of suitability)
  int* llamadas; // Arreglo de numeros con las llamadas
  int* destinos_Iniciales;
  int* destinos_Finales;
  double tiempoDeEspera;
  double tiempoDeViaje;
  int* pisos_recorridos;
  int Carga_de_pasajeros;  // Descargando '0' , Cargando '1'
  double tiempoDeCargaPasajeros;
  double tiempoDeDescargaPasajeros;
  double tiempoInactivo;
  int cant_llamadas_atendidas;
  int sector;

} Ascensor;
