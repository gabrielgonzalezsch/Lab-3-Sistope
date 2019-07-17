#include "structs.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

Llamada** leerFicheroEntradaYGuardarLlamadas(char* nombre, int tipo);

Ascensor* consAscensor (int id);

int calcularLargoTotal(Llamada** llamadasSubida, Llamada** llamadasBajada, Llamada** llamadasOrdinario);

Llamada** unirLlamadas(Llamada** llamadasSubida, Llamada** llamadasBajada, Llamada** llamadasOrdinario);

Llamada* buscarLlamada(Llamada** llamadas, int largo, int tiempo);

Llamada** agregarLlamada(Ascensor* ascensor, Llamada* llamada);

Llamada** agregarLlamadaInicio(Ascensor* ascensor, Llamada* llamada);

Llamada* buscarLlamada(Llamada** llamadas, int largo, int tiempo);

void nearestCar(Ascensor** ascensores, Llamada* llamada, int num_pisos, int num_ascensores);

Llamada** eliminarLlamada(Llamada** llamadas, int largo, Llamada* llamada);

int** eliminarDestinoFinal(Ascensor* ascensor, int largo);

int** agregarDestinoFinal(Ascensor* ascensor, int largo);

int calcularLargoDestino(Ascensor* ascensor);

int calcularLargo(Llamada** llamadas);

void accion (Ascensor* ascensor, Llamada** llamadas, int largoLlamadas);

void actualizarEsperas(Ascensor** ascensores, int tiempo, int num_ascensores);
