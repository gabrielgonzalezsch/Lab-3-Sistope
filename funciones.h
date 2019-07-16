#include "estructuras.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


Llamada** leerFicheroEntradaYGuardarLlamadas(char* nombre);

Ascensor** inicializarAscensores(int num_ascensores);

void asignarLlamadas(Ascensor** ascensores,Llamada** llamadasSubida,Llamada** llamadasBajada,Llamada** llamadasOrdinario);