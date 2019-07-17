#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>


//Estructura de las llamadas de ascensores
typedef struct Llamada{
  int id;
  int piso_inicial;
  int piso_destino;
  int cant_pasajeros;
  int direccion; // 0: bajada, 1: subida
  int tiempo;
  int tiempo_espera;
  int atendida;
  int tipo; // 1: subida, 2: bajada, 3: ordinario
} Llamada;

//Estructura de los ascensores
typedef struct Ascensor{
  int id;
  int posicion;
  int direccion; // 0: bajada, 1: subida
  int capacidad;
  int pasajeros;
  int estado;
  int fs;
  Llamada** llamadas;
  int* destinos_iniciales;
  int** destinos_finales;
  int tiempo_espera;
  int tiempo_viaje;
  int pisos_recorridos;
  int cargando;
  int tiempo_cargado_total;
  int tiempo_cargado;
  int descargando;
  int tiempo_descargado_total;
  int tiempo_descargado;
  int tiempo_inactivo;
  int llamadas_atendidas;
} Ascensor;
