#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funciones.h"



//Entrada: Nombre del fichero con las llamadas respectivas de los ascensores
//Funcionamiento: Funcion que guarda los llamados de los ascensores en una estrcutura
//Salida: Estructura de Llamadas
Llamada** leerFicheroEntradaYGuardarLlamadas(char* nombre, int tipo){
  // ############################################### Leer archivo Y guardar Llamados ###########################################################################
  FILE* archivo = fopen(nombre,"r");

  // Cantidad de lineas en fichero------------------------------------------------------------
  int largo=0;
  for (char c = getc(archivo); c != EOF; c = getc(archivo)){if (c == '\n'){largo = largo + 1;}}
  largo++;
  //printf("Largo fichero: %d\n\n\n",largo);
  rewind(archivo);
  //-------------------------------------------------------------------------------------------

  Llamada** llamadas = (Llamada**)malloc(sizeof(Llamada*)*largo);

  int piso_inicial,piso_destino,direccion,num_pasajeros,tiempo;
  char c1,c2,c3,c4; // Leer las comas del csv
  int puntero = 0;

  while(!feof(archivo)){

      tiempo = -1;
      piso_inicial= -1;
      piso_destino= -1;
      direccion = -1;
      num_pasajeros = -1;
      char auxCharDireccion;

      fscanf(archivo, "%d %c %d %c %d %c %c %c %d", &tiempo,&c1,&piso_inicial,&c2,&piso_destino,&c3,&auxCharDireccion,&c4,&num_pasajeros);

      if(auxCharDireccion == 85){direccion=1;}
      else{direccion=0;}
      //printf("%lf %d %d %c %d\n",tiempo,piso_inicial,piso_destino,auxCharDireccion,num_pasajeros);
      //printf("%d %d %d %d %d\n\n",tiempo,piso_inicial,piso_destino,direccion,num_pasajeros);
      llamadas[puntero] = (Llamada*)malloc(sizeof(Llamada));
      llamadas[puntero]->id = puntero/*+1000*/;
      llamadas[puntero]->piso_inicial = piso_inicial;
      llamadas[puntero]->piso_destino = piso_destino;
      llamadas[puntero]->cant_pasajeros = num_pasajeros;
      llamadas[puntero]->direccion = direccion;
      llamadas[puntero]->tiempo = tiempo;
      llamadas[puntero]->tiempo_espera = 0;
      llamadas[puntero]->atendida = 0;
      llamadas[puntero]->tipo = tipo;

      puntero++;
  }


  // Para Verificar Si se guardo Correctamente
  for (int i = 0; i < largo-1; i++) {
    printf("Llamada: %d\npiso inicial:%d\npiso destino:%d\ncantidad pasajeros:%d\nDireccion:%d\ntiempo:%d\ntiempo de Espera:%d\nLlamada atendida:%d\nTipo:%d\n\n",
    llamadas[i]->id,
    llamadas[i]->piso_inicial,
    llamadas[i]->piso_destino,
    llamadas[i]->cant_pasajeros,
    llamadas[i]->direccion,
    llamadas[i]->tiempo,
    llamadas[i]->tiempo_espera,
    llamadas[i]->atendida,
    llamadas[i]->tipo);
  }

  fclose(archivo);

  return llamadas;
}

//Entrada: Entero con el id que se le ortorgara al ascensor
//Funcionamiento: Funcion constructora de la estructura ascensor
//Salida: Una instancia de ascensor
Ascensor* consAscensor (int id){
  Ascensor* aux;

  aux->id = id;
  aux->posicion = 1;
  aux->direccion = 0;
  aux->capacidad = 20;
  aux->pasajeros = 0;
  aux->estado = 0;
  aux->fs = 0;
  aux->llamadas = (Llamada**) malloc(sizeof(Llamada*));
  aux->destinos_iniciales = (int*) malloc(sizeof(int));
  aux->destinos_finales = (int**) malloc(sizeof(int*));
  aux->tiempo_espera = 0;
  aux->tiempo_viaje = 0;
  aux->pisos_recorridos = 0;
  aux->cargando = 0;
  aux->tiempo_cargado_total = 0;
  aux->tiempo_cargado = 0;
  aux->descargando = 0;
  aux->tiempo_descargado_total = 0;
  aux->tiempo_descargado = 0;
  aux->tiempo_inactivo = 0;
  aux->llamadas_atendidas = 0;

  return aux;

}

//Entrada: Tres listas de llamadas, una por cada archivo de entrada
//Funcionamiento: Funcion que calcula el largo de las tres listas juntas
//Salida: Entero con el largo
int calcularLargoTotal(Llamada** llamadasSubida, Llamada** llamadasBajada, Llamada** llamadasOrdinario){

  int x = 0;
  while(llamadasSubida[x+1] != NULL){
    x++;
  }

  int y = 0;
  while(llamadasBajada[y+1] != NULL){
    y++;
  }

  int z = 0;
  while(llamadasOrdinario[z+1] != NULL){
    z++;
  }

  return x + y + z;
}

//Entrada: Tres listas de llamadas
//Funcionamiento: Funcion que une las tres listas de llamadas en una sola
//Salida: Una lista de llamadas con las tres iniciales dentro
Llamada** unirLlamadas(Llamada** llamadasSubida, Llamada** llamadasBajada, Llamada** llamadasOrdinario){

  int largo = calcularLargoTotal(llamadasSubida, llamadasBajada, llamadasOrdinario);

  Llamada** llamadas = (Llamada**) malloc(sizeof(Llamada*) * largo);

  int i = 0;

  int x = 0;
  while(llamadasSubida[x+1] != NULL){
    llamadas[i] = (Llamada*)malloc(sizeof(Llamada));
    llamadas[i]->id = llamadasSubida[x]->id;
    llamadas[i]->piso_inicial = llamadasSubida[x]->piso_inicial;
    llamadas[i]->piso_destino = llamadasSubida[x]->piso_destino;
    llamadas[i]->cant_pasajeros = llamadasSubida[x]->cant_pasajeros;
    llamadas[i]->direccion = llamadasSubida[x]->direccion;
    llamadas[i]->tiempo = llamadasSubida[x]->tiempo;
    llamadas[i]->tiempo_espera = llamadasSubida[x]->tiempo_espera;
    llamadas[i]->atendida = llamadasSubida[x]->atendida;
    llamadas[i]->tipo = llamadasSubida[x]->tipo;
    i++;
    x++;
  }

  int y = 0;
  while(llamadasBajada[y+1] != NULL){
    llamadas[i] = (Llamada*)malloc(sizeof(Llamada));
    llamadas[i]->id = llamadasBajada[y]->id;
    llamadas[i]->piso_inicial = llamadasBajada[y]->piso_inicial;
    llamadas[i]->piso_destino = llamadasBajada[y]->piso_destino;
    llamadas[i]->cant_pasajeros = llamadasBajada[y]->cant_pasajeros;
    llamadas[i]->direccion = llamadasBajada[y]->direccion;
    llamadas[i]->tiempo = llamadasBajada[y]->tiempo;
    llamadas[i]->tiempo_espera = llamadasBajada[y]->tiempo_espera;
    llamadas[i]->atendida = llamadasBajada[y]->atendida;
    llamadas[i]->tipo = llamadasBajada[y]->tipo;
    i++;
    y++;
  }

  int z = 0;
  while(llamadasOrdinario[z+1] != NULL){
    llamadas[i] = (Llamada*)malloc(sizeof(Llamada));
    llamadas[i]->id = llamadasOrdinario[z]->id;
    llamadas[i]->piso_inicial = llamadasOrdinario[z]->piso_inicial;
    llamadas[i]->piso_destino = llamadasOrdinario[z]->piso_destino;
    llamadas[i]->cant_pasajeros = llamadasOrdinario[z]->cant_pasajeros;
    llamadas[i]->direccion = llamadasOrdinario[z]->direccion;
    llamadas[i]->tiempo = llamadasOrdinario[z]->tiempo;
    llamadas[i]->tiempo_espera = llamadasOrdinario[z]->tiempo_espera;
    llamadas[i]->atendida = llamadasOrdinario[z]->atendida;
    llamadas[i]->tipo = llamadasOrdinario[z]->tipo;
    i++;
    z++;
  }
   return llamadas;
}

//Entrada: Lista de llamadas, largo de la lista de llamadas y el tiempo actual del programa
//Funcionamiento: Funcion que busca entre todas las llamadas si es que existe alguna en ese tiempo dado
//Salida: Si encuentra una llamada en ese tiempo, la retorna, si no, retorna nulo
Llamada* buscarLlamada(Llamada** llamadas, int largo, int tiempo){

  for (int i = 0; i < largo; i++) {
    if (llamadas[i]->tiempo == tiempo) {
      return llamadas[i];
    }
  }

  return NULL;
}

//Entrada: Una instancia de Ascensor y la llamada a agregar
//Funcionamiento: Funcion que agrega al final la llamada de entrada a la lista de llamdas interna de Ascensor
//Salida: Lista nueva de llamadas
Llamada** agregarLlamada(Ascensor* ascensor, Llamada* llamada){

  int largo = ascensor -> llamadas_atendidas + 1;
  Llamada** llamadas = (Llamada**) malloc(sizeof(Llamada*) * largo);

  printf("llamadas atendidas: %d\n", largo);
  int i = 0;
  while (i < ascensor -> llamadas_atendidas) {
    printf("i: %d\n", i);
    llamadas[i] = (Llamada*) malloc(sizeof(Llamada));
    llamadas[i]->id = ascensor -> llamadas[i] -> id;
    llamadas[i]->piso_inicial = ascensor -> llamadas[i] -> piso_inicial;
    llamadas[i]->piso_destino = ascensor -> llamadas[i] -> piso_destino;
    llamadas[i]->cant_pasajeros = ascensor -> llamadas[i] -> cant_pasajeros;
    llamadas[i]->direccion = ascensor -> llamadas[i] -> direccion;
    llamadas[i]->tiempo = ascensor -> llamadas[i] -> tiempo;
    llamadas[i]->tiempo_espera = ascensor -> llamadas[i] -> tiempo_espera;
    llamadas[i]->atendida = ascensor -> llamadas[i] -> atendida;
    llamadas[i]->tipo = ascensor -> llamadas[i] -> tipo;
    i++;
  }

  llamadas[i] = (Llamada*)malloc(sizeof(Llamada));
  llamadas[i]->id = llamada -> id;
  llamadas[i]->piso_inicial = llamada -> piso_inicial;
  llamadas[i]->piso_destino = llamada -> piso_destino;
  llamadas[i]->cant_pasajeros = llamada -> cant_pasajeros;
  llamadas[i]->direccion = llamada -> direccion;
  llamadas[i]->tiempo = llamada -> tiempo;
  llamadas[i]->tiempo_espera = llamada -> tiempo_espera;
  llamadas[i]->atendida = llamada -> atendida;
  llamadas[i]->tipo = llamada -> tipo;

  return llamadas;
}

//Entrada: Una instancia de Ascensor y la llamada a agregar
//Funcionamiento: Funcion que agrega al inicio la llamada de entrada a la lista de llamdas interna de Ascensor
//Salida: Lista nueva de llamadas
Llamada** agregarLlamadaInicio(Ascensor* ascensor, Llamada* llamada){
  Llamada** llamadas = (Llamada**) malloc(sizeof(Llamada*) * (ascensor -> llamadas_atendidas+1));

  int i = 0;

  llamadas[i] = (Llamada*)malloc(sizeof(Llamada));
  llamadas[i]->id = llamada -> id;
  llamadas[i]->piso_inicial = llamada -> piso_inicial;
  llamadas[i]->piso_destino = llamada -> piso_destino;
  llamadas[i]->cant_pasajeros = llamada -> cant_pasajeros;
  llamadas[i]->direccion = llamada -> direccion;
  llamadas[i]->tiempo = llamada -> tiempo;
  llamadas[i]->tiempo_espera = llamada -> tiempo_espera;
  llamadas[i]->atendida = llamada -> atendida;
  llamadas[i]->tipo = llamada -> tipo;
  i++;

  while (i < ascensor -> llamadas_atendidas) {
    llamadas[i] = (Llamada*) malloc(sizeof(Llamada));

    llamadas[i]->id = ascensor -> llamadas[i] -> id;
    llamadas[i]->piso_inicial = ascensor -> llamadas[i] -> piso_inicial;
    llamadas[i]->piso_destino = ascensor -> llamadas[i] -> piso_destino;
    llamadas[i]->cant_pasajeros = ascensor -> llamadas[i] -> cant_pasajeros;
    llamadas[i]->direccion = ascensor -> llamadas[i] -> direccion;
    llamadas[i]->tiempo = ascensor -> llamadas[i] -> tiempo;
    llamadas[i]->tiempo_espera = ascensor -> llamadas[i] -> tiempo_espera;
    llamadas[i]->atendida = ascensor -> llamadas[i] -> atendida;
    llamadas[i]->tipo = ascensor -> llamadas[i] -> tipo;
    i++;

  }



  return llamadas;

}

//Entrada: Lista de ascensores, la llamada a atender, el numero de pisos y el numero de ascensores
//Funcionamiento: Primer algoritmo que se debe implementar el cual busca el carro mas cercano para atender la llamada por medio del calculo de FS
//Salida: void
void nearestCar(Ascensor** ascensores, Llamada* llamada, int num_pisos, int num_ascensores){
  int fs = 1;
  int sameFloor = 0;
  int newFs;
  int indice = 0;
  int d;

  for (int i = 0; i < num_ascensores; i++) {
    d = fabs(ascensores[i] -> posicion - llamada -> piso_inicial);

    if (llamada -> cant_pasajeros > (ascensores[i] -> capacidad - ascensores[i] -> pasajeros)) {
      newFs = -1;
    }
    else if(ascensores[i] -> estado == 0){
      newFs = num_pisos + 1 - d;
    }
    else if (ascensores[i] -> direccion == 0) {
      if (llamada -> piso_inicial > ascensores[i] -> posicion) {
        newFs = 1;
      }
      else if (llamada -> piso_inicial == ascensores[i] -> posicion) {
        newFs = num_pisos + 2 - d;
        sameFloor = 1;
      }
      else if (llamada -> piso_inicial < ascensores[i] -> posicion && llamada -> direccion == ascensores[i] -> direccion) {
        newFs = num_pisos + 2 - d;
      }
      else if (llamada -> piso_inicial < ascensores[i] -> posicion && llamada -> direccion != ascensores[i] -> direccion) {
        newFs = num_pisos + 1 - d;
      }

    }
    else if (ascensores[i] -> direccion == 1) {
      if (llamada -> piso_inicial < ascensores[i] -> posicion) {
        newFs = 1;
      }
      else if (llamada -> piso_inicial == ascensores[i] -> posicion) {
        newFs = num_pisos + 2 - d;
        sameFloor = 1;
      }
      else if (llamada -> piso_inicial > ascensores[i] -> posicion && llamada -> direccion == ascensores[i] -> direccion) {
        newFs = num_pisos + 2 - d;
      }
      else if (llamada -> piso_inicial > ascensores[i] -> posicion && llamada -> direccion != ascensores[i] -> direccion) {
        newFs = num_pisos + 1 - d;
      }
    }
    else{
      newFs = 0;
    }

    ascensores[i] -> fs = newFs;

    if (newFs >= fs) {
      indice = i;
      fs = newFs;
    }

  }

  if (sameFloor == 1) {
    ascensores[indice] -> pasajeros += llamada -> cant_pasajeros;
    ascensores[indice] -> llamadas = agregarLlamadaInicio(ascensores[indice], llamada);
    ascensores[indice] -> llamadas_atendidas++;
  }
  else{
    ascensores[indice] -> pasajeros += llamada -> cant_pasajeros;
    ascensores[indice] -> llamadas = agregarLlamada(ascensores[indice], llamada);
    ascensores[indice] -> llamadas_atendidas++;
  }


}

//Entrada: Lista de llamadas, largo de la lista de llamdas, y la llamada a eliminar
//Funcionamiento: Funcion que elimina de la lista de llamdas la llamada que entra por parametro
//Salida: Nueva lista de llamadas
Llamada** eliminarLlamada(Llamada** llamadas, int largo, Llamada* llamada){

  Llamada** out = (Llamada**) malloc(sizeof(Llamada*) * (largo - 1));

  int indice = 0;
  for (int i = 0; i < largo; i++) {
    if (llamada -> id != llamadas[i] -> id) {
      out[indice] = (Llamada*) malloc(sizeof(Llamada));
      out[indice] -> id = llamadas[i] -> id;
      out[indice] -> piso_inicial = llamadas[i] -> piso_inicial;
      out[indice] -> piso_destino = llamadas[i] -> piso_destino;
      out[indice] -> cant_pasajeros = llamadas[i] -> cant_pasajeros;
      out[indice] -> direccion = llamadas[i] -> direccion;
      out[indice] -> tiempo = llamadas[i] -> tiempo;
      out[indice] -> tiempo_espera = llamadas[i] -> tiempo_espera;
      out[indice] -> atendida = llamadas[i] -> atendida;
      out[indice] -> tipo = llamadas[i] -> tipo;
      indice++;
    }
  }

  return out;
}

//Entrada: Una instancia de Ascensor y el largo de la lista de destinos finales
//Funcionamiento: Funcion que elimina la primera posicion de la lista de desintos finales
//Salida: Nueva lista de destinos finales
int** eliminarDestinoFinal(Ascensor* ascensor, int largo){
  int** out = (int**) malloc(sizeof(int*) * (largo - 1));

  int i = 1;
  int indice = 0;
  while (i < largo) {
    out[indice] = (int*) malloc(sizeof(int)*2);
    out[indice][0] = ascensor -> destinos_finales[i][0];
    out[indice][1] = ascensor -> destinos_finales[i][1];
    i++;
  }

  return out;
}

//Entrada: Una instancia de Ascensor y el largo de la lista de destinos finales
//Funcionamiento: Funcion que agrega al final un elemento a la lista de desintos finales
//Salida: Nueva lista de destinos finales
int** agregarDestinoFinal(Ascensor* ascensor, int largo){
  int** out = (int**) malloc(sizeof(int*) * largo + 1);

  int i = 0;
  while (i < largo) {
    out[i] = (int*) malloc(sizeof(int)*2);
    out[i][0] = ascensor -> destinos_finales[i][0];
    out[i][1] = ascensor -> destinos_finales[i][1];
    i++;
  }

  out[i][0] = ascensor -> llamadas[0] -> piso_destino;
  out[i][1] = ascensor -> llamadas[0] -> cant_pasajeros;

  return out;
}

//Entrada: Una instancia de Ascensor
//Funcionamiento: Funcion que calcula el largo de la lista de destinos finales
//Salida: Entero con el largo de la lista
int calcularLargoDestino(Ascensor* ascensor){
  int largoDestinos = 0;
  while(ascensor -> destinos_finales[largoDestinos+1] != NULL){
    largoDestinos++;
  }

  return largoDestinos;
}

//Entrada: Lista de llamdas
//Funcionamiento: Funcion que calcula el largo de la lista de llamadas
//Salida: Entero con el largo de la lista
int calcularLargo(Llamada** llamadas){
  int i = 0;
  while (llamadas[i+1] != NULL) {
    i++;
  }
  return i;
}

//Entrada: Una instancia de ascensor, la lista de llamdas, y el largo de la lista de llamadas
//Funcionamiento: Funcion que aumenta los contadores de tiempo segun se necesite
//Salida: void
void accion (Ascensor* ascensor, Llamada** llamadas, int largoLlamadas){

  int largoDestinos = calcularLargoDestino(ascensor);
  printf("oa\n");
  //largoLlamadas = calcularLargo(ascensor -> llamadas);
  printf("calcule largos\n");

  if (ascensor -> cargando == 1) {
    ascensor -> tiempo_cargado++;
    ascensor -> tiempo_viaje++;
    if (ascensor -> tiempo_cargado == ascensor -> tiempo_cargado_total) {
      ascensor -> cargando = 0;
      ascensor -> tiempo_cargado = 0;
    }
  }

  else if (ascensor -> descargando == 1) {
    ascensor -> tiempo_descargado++;
    ascensor -> tiempo_viaje++;
    ascensor -> pasajeros--;
    if (ascensor -> tiempo_descargado == ascensor -> tiempo_descargado_total) {
      ascensor -> descargando = 0;
      ascensor -> tiempo_descargado = 0;
      if (largoLlamadas == 0) {
        ascensor -> estado = 0;
      }
    }
  }

  else if(ascensor -> llamadas_atendidas != 0 && largoDestinos != 0){
    ascensor -> estado = 1;
    ascensor -> tiempo_cargado_total = ascensor -> llamadas[0] -> cant_pasajeros;
    if (ascensor -> llamadas[0] -> piso_inicial > ascensor -> posicion) {
      ascensor -> direccion = 1;
    }
    else if (ascensor -> llamadas[0] -> piso_inicial < ascensor -> posicion) {
      ascensor -> direccion = 0;
    }
    ascensor -> tiempo_viaje++;
    if (ascensor -> destinos_finales[0][0] == ascensor -> posicion) {
      ascensor -> descargando = 1;
      ascensor -> tiempo_descargado_total = ascensor -> destinos_finales[0][1];
      largoDestinos = calcularLargoDestino(ascensor);
      ascensor -> destinos_finales = eliminarDestinoFinal(ascensor, largoDestinos);
    }
    else if (ascensor -> posicion == ascensor -> llamadas[0] -> piso_inicial) {
      ascensor -> direccion = ascensor -> llamadas[0] -> direccion;
      largoDestinos = calcularLargoDestino(ascensor);
      ascensor -> destinos_finales = agregarDestinoFinal(ascensor, largoDestinos);
      ascensor -> cargando = 1;
      ascensor -> tiempo_espera += ascensor -> llamadas[0] -> tiempo_espera;
      largoLlamadas = calcularLargo(ascensor -> llamadas);
      ascensor -> llamadas = eliminarLlamada(ascensor -> llamadas, largoLlamadas, ascensor -> llamadas[0]);
    }
    else if(ascensor -> direccion == 1){
      ascensor -> pisos_recorridos ++;
      ascensor -> posicion++;
    }
    else if(ascensor -> direccion == 0){
      ascensor -> pisos_recorridos ++;
      ascensor -> posicion--;
    }
  }

  else if (largoLlamadas != 0) {
    if (ascensor -> llamadas[0] -> piso_inicial > ascensor -> posicion){
      ascensor -> direccion = 1;
    }
    else if (ascensor -> llamadas[0] -> piso_inicial < ascensor -> posicion) {
      ascensor -> direccion = 0;
    }
    ascensor -> estado = 1;
    ascensor -> tiempo_viaje++;
    ascensor -> tiempo_cargado_total = ascensor -> llamadas[0] -> cant_pasajeros;
    if (ascensor -> posicion == ascensor -> llamadas[0] -> piso_inicial) {
      ascensor -> direccion = ascensor -> llamadas[0] -> direccion;
      largoDestinos = calcularLargoDestino(ascensor);
      ascensor -> destinos_finales = agregarDestinoFinal(ascensor, largoDestinos);
      ascensor -> cargando = 1;
      ascensor -> tiempo_espera += ascensor -> llamadas[0] -> tiempo_espera;
      largoLlamadas = calcularLargo(ascensor -> llamadas);
      ascensor -> llamadas = eliminarLlamada(ascensor -> llamadas, largoLlamadas, ascensor -> llamadas[0]);
    }
    else if (ascensor -> direccion == 1) {
      ascensor -> posicion++;
      ascensor -> pisos_recorridos++;
    }
    else if (ascensor -> direccion == 0) {
      ascensor -> posicion--;
      ascensor -> pisos_recorridos++;
    }
  }

  else if (largoDestinos != 0) {
    ascensor -> estado = 1;
    ascensor -> tiempo_viaje++;
    if (ascensor -> destinos_finales[0][0] > ascensor -> posicion) {
      ascensor -> direccion = 1;
    }
    else if (ascensor -> destinos_finales[0][0] < ascensor -> posicion) {
      ascensor -> direccion = 0;
    }
    if (ascensor -> destinos_finales[0][0] == ascensor -> posicion) {
      ascensor -> descargando = 1;
      ascensor -> tiempo_descargado_total = ascensor -> destinos_finales[0][1];
      largoDestinos = calcularLargoDestino(ascensor);
      ascensor -> destinos_finales = eliminarDestinoFinal(ascensor, largoDestinos);
    }
    else if (ascensor -> direccion == 1) {
      ascensor -> posicion++;
      ascensor -> pisos_recorridos++;
    }
    else if (ascensor -> direccion == 0) {
      ascensor -> posicion--;
      ascensor -> pisos_recorridos++;
    }
  }

  else{
    ascensor -> estado = 0;
    ascensor -> tiempo_inactivo++;
  }


}

//Entrada: Lista de ascensores, tiempo actual y numero de ascensores
//Funcionamiento: Funcion que aumenta los tiempos de espera de los ascensores
//Salida: void
void actualizarEsperas(Ascensor** ascensores, int tiempo, int num_ascensores){
  int largoLlamadas;

  for (int i = 0; i < num_ascensores; i++) {
    largoLlamadas = calcularLargo(ascensores[i] -> llamadas);
    for (int j = 0; j < largoLlamadas; j++) {
      if (ascensores[i] -> llamadas[j] -> tiempo < tiempo && ascensores[i] -> llamadas[j] -> atendida == 0) {
        ascensores[i] -> llamadas[j] -> tiempo_espera++;
      }
    }
  }
}
