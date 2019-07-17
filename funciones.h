#include "estructuras.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


Llamada** leerFicheroEntradaYGuardarLlamadas(char* nombre);

Ascensor** inicializarAscensores(int num_ascensores);

void calcularFS(Ascensor** ascensores, int num_ascensores, Llamada* llamada, int num_pisos);

int buscarIndice(Ascensor** ascensores, int num_ascensores);

void asignarLlamadas(Ascensor** ascensores,Llamada** llamadasSubida,Llamada** llamadasBajada,Llamada** llamadasOrdinario, int num_ascensores, int num_pisos);
