#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funciones.h"



//Entrada: Nombre del fichero con las llamadas respectivas de los ascensores
//Funcionamiento: Funciona que guarda los llamados de los ascensores en una estrcutura;
//Salida: Estructura de Llamadas
Llamada** leerFicheroEntradaYGuardarLlamadas(char* nombre){
  // ############################################### Leer archivo Y guardar Llamados ###########################################################################
  FILE* archivo = fopen(nombre,"r");

  // Cantidad de lineas en fichero------------------------------------------------------------
  int largo=0;
  for (char c = getc(archivo); c != EOF; c = getc(archivo)){if (c == '\n'){largo = largo + 1;}}
  largo++;
  printf("Largo fichero: %d\n\n\n",largo);
  rewind(archivo);
  //-------------------------------------------------------------------------------------------

  Llamada** llamadas = (Llamada**)malloc(sizeof(Llamada*)*largo);

  double tiempo;
  int piso_inicial,piso_destino,direccion,num_pasajeros;
  char c1,c2,c3,c4; // Leer las comas del csv
  int puntero=0;

  while(!feof(archivo)){

      tiempo = -1;
      piso_inicial= -1;
      piso_destino= -1;
      direccion = -1;
      num_pasajeros = -1;
      char auxCharDireccion;

      fscanf(archivo, "%lf %c %d %c %d %c %c %c %d", &tiempo,&c1,&piso_inicial,&c2,&piso_destino,&c3,&auxCharDireccion,&c4,&num_pasajeros);

      if(auxCharDireccion == 85){direccion=1;}
      else{direccion=0;}
      //printf("%lf %d %d %c %d\n",tiempo,piso_inicial,piso_destino,auxCharDireccion,num_pasajeros);
      //printf("%lf %d %d %d %d\n\n",tiempo,piso_inicial,piso_destino,direccion,num_pasajeros);
      llamadas[puntero] = (Llamada*)malloc(sizeof(Llamada));
      llamadas[puntero]->id = puntero/*+1000*/;
      llamadas[puntero]->tiempoLlamada = tiempo;
      llamadas[puntero]->piso_inicial = piso_inicial;
      llamadas[puntero]->piso_destino = piso_destino;
      llamadas[puntero]->direccion = direccion;
      llamadas[puntero]->num_pasajeros = num_pasajeros;
      llamadas[puntero]->tiempoDeEspera = 0;
      llamadas[puntero]->atendidaBandera = 0;

      puntero++;
  }

  // Para Verificar Si se guardo Correctamente
  for (int i = 0; i < largo; i++) {
    printf("Llamada: %d\ntiempo:%lf\npiso Inicial:%d\npiso Destino:%d\nDireccion:%d\nPasajeros:%d\ntiempo de Espera:%lf\nLlamada atendida:%d\n\n",
    llamadas[i]->id,
    llamadas[i]->tiempoLlamada,
    llamadas[i]->piso_inicial,
    llamadas[i]->piso_destino,
    llamadas[i]->direccion,
    llamadas[i]->num_pasajeros,
    llamadas[i]->tiempoDeEspera,
    llamadas[i]->atendidaBandera);
  }

  fclose(archivo);

  return llamadas;
}

Ascensor** inicializarAscensores(int num_ascensores){

	Ascensor** ascensores = (Ascensor**) malloc(sizeof(Ascensor*) * num_ascensores);

	for(int i = 0; i < num_ascensores; i++){
		ascensores[i]->id = i;
		ascensores[i]->piso_actual = 1;
		ascensores[i]->direccion = 1;
		ascensores[i]->capacidad_pasajeros = 20;
		ascensores[i]->cantidad_pasajeros = 0;
		ascensores[i]->estado = 0;
		ascensores[i]->fs = 0.0;
		ascensores[i]->llamadas = (int*) malloc(sizeof(int));
		ascensores[i]->destinos_Iniciales = (int*) malloc(sizeof(int));
		ascensores[i]->destinos_Finales = (int*) malloc(sizeof(int));
		ascensores[i]->tiempoDeEspera = 0.0;
		ascensores[i]->tiempoDeViaje = 0.0;
		ascensores[i]->pisos_recorridos = 0;
		ascensores[i]->carga_de_pasajeros = -1;
		ascensores[i]->tiempoDeCargaPasajeros = 0.0;
		ascensores[i]->tiempoDeDescargaPasajeros = 0.0;
		ascensores[i]->tiempoInactivo = 0.0;
		ascensores[i]->cant_llamadas_atendidas = 0;
		ascensores[i]->sector = 0;
	}

	return ascensores;
}

void calcularFS(Ascensor** ascensores, int num_ascensores, Llamada* llamada, int num_pisos){
  int d = -1;

  for (int i = 0; i < num_ascensores; i++){

    d = (fabs(ascensores[i] -> piso_actual - llamada -> piso_inicial));

    if (llamada -> num_pasajeros > (ascensores[i] -> capacidad_pasajeros - ascensores[i] -> cantidad_pasajeros)) {
      ascensores[i] -> fs = -1;
    }

    else if(ascensores[i] -> estado == 0){
      ascensores[i] -> fs = num_pisos + 1 - d;
    }

    else if ((ascensores[i]-> direccion == llamada -> direccion) && ((ascensores[i] -> piso_actual > llamada -> piso_inicial && ascensores[i]-> direccion == 0) || (ascensores[i]->piso_actual < llamada -> piso_inicial && ascensores[i]-> direccion == 1))){
      ascensores[i] -> fs = num_pisos + 2 - d;
    }

    else if ((ascensores[i]-> direccion != llamada -> direccion) && ((ascensores[i] -> piso_actual > llamada -> piso_inicial && ascensores[i]-> direccion == 0) || (ascensores[i]->piso_actual < llamada -> piso_inicial && ascensores[i]-> direccion == 1))){
      ascensores[i] -> fs = num_pisos + 1 - d;
    }

    else if ((ascensores[i]->piso_actual > llamada -> piso_inicial && ascensores[i] -> direccion == 1) || (ascensores[i] -> piso_actual < llamada -> piso_inicial && ascensores[i]-> direccion == 0)){
      ascensores[i] -> fs = 1;
    }

    else{
      ascensores[i] -> fs = 0;
    }
  }
}

int buscarIndice(Ascensor** ascensores, int num_ascensores){
  int indice = -1;
  int max = -1;
  for (int i = 0; i < num_ascensores; i++) {
    if (max < ascensores[i] -> fs) {
      max = ascensores[i] -> fs;
      indice = i;
    }
  }
}

void moverAscensor(Ascensor* ascensor, Llamada** llamadas){

}

void asignarLlamadas(Ascensor** ascensores,Llamada** llamadasSubida, Llamada** llamadasBajada, Llamada** llamadasOrdinario, int num_ascensores, int num_pisos){

  // calcular el largo de cada lista de llamadas
	int largoSubida = 0;
	while(llamadasSubida[largoSubida+1] != NULL){
		largoSubida++;
	}

	int largoBajada = 0;
	while(llamadasBajada[largoBajada+1] != NULL){
		largoBajada++;
	}

	int largoOrdinario = 0;
	while(llamadasOrdinario[largoOrdinario+1] != NULL){
		largoOrdinario++;
	}

	printf("largo total de los subida: %d\n", largoSubida);
  printf("largo total de los bajada: %d\n", largoBajada);
  printf("largo total de los ordinario: %d\n", largoOrdinario);


  int indice;
  for (int i = 0; i < largoSubida; i++) {

    calcularFS(ascensores, num_ascensores, llamadasSubida[i], num_pisos);

    indice = -1;

    printf("Vuelta %d\n", i);
    for (int j = 0; j < num_ascensores; j++) {

      printf("Ascensor %d\nFS: %f\n", j, ascensores[j] -> fs);
    }

    indice = buscarIndice(ascensores, num_ascensores);

  }




}
