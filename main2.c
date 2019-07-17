
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funciones2.h"




int main(int argc, char** argv){

	int opt;
	int largo;

	char* nombreFileSubida =  (char*) malloc(sizeof(char*) * 20);
	char* nombreFileBajada =  (char*) malloc(sizeof(char*) * 20);
	char* nombreFileOrdinario =  (char*) malloc(sizeof(char*) * 20);
	int num_pisos = -1;
	int num_ascensores = -1;
	int bFLag = -1;
  int tiempo = 0;

	FILE* arcS;
	FILE* arcB;
	FILE* arcO;

	//getopt
	while ((opt = getopt(argc, argv, ":u:d:o:n:e:b:x")) != -1){

	switch (opt){
		case 'u':
		strcpy(nombreFileSubida, argv[2]);
		arcS = fopen(nombreFileSubida,"r");
		if(arcS == NULL){printf("parametro de entrada en -u '%s' no existe\n",nombreFileSubida);exit(1);}
		fclose(arcS);
		printf("||archivoTraficoSubida.csv---||: %s\n", nombreFileSubida);
		break;
		case 'd':
		strcpy(nombreFileBajada, argv[4]);
		arcB = fopen(nombreFileBajada,"r");
		if(arcB == NULL){printf("parametro de entrada en -d '%s' no existe\n",nombreFileBajada);exit(1);}
		fclose(arcB);
		printf("||archivoTraficoBajada.csv---||: %s\n", nombreFileBajada);
		break;
		case 'o':
		strcpy(nombreFileOrdinario, argv[6]);
		arcO = fopen(nombreFileOrdinario,"r");
		if(arcO == NULL){printf("parametro de entrada en -o '%s' no existe\n",nombreFileOrdinario);exit(1);}
		fclose(arcO);
		printf("||archivoTraficoOrdinario.csv||: %s\n", nombreFileOrdinario);
		break;
		case 'n':
		if(atoi(argv[8])>0){
			num_pisos = atoi(argv[8]);
			printf("||numero de pisos------------||: %d\n", num_pisos);
		}else{
			printf("El valor ingresado en \"numero de pisos\" es invalido\n");
			exit(1);
		}break;
		case 'e':
		if (atoi(argv[10]) > 0){
			num_ascensores = atoi(argv[10]);
			printf("||numero de ascensores-------||: %d\n", num_ascensores);
		}else{
			printf("El valor ingresado en \"numero de ascensores\" es invalido\n");
			exit(1);
		}
		break;
		case 'b':
		bFLag = atoi(argv[12]);
		printf("||bandera--------------------||: %d\n", bFLag);
		break;
		case ':':
		printf("option needs a value\n");
		break;
		case '?':
		printf("unknown option: %c\n", optopt);
		break;
	}
	}
	// Este for captura los elementos extra del argumento
	for(optind = 13; optind < argc; optind++){
		printf("||extra arguments------------||: %s\n", argv[optind]);
	}
	printf("\n");


	//Se leen los archivos de entrada
	Llamada** llamadasSubida = leerFicheroEntradaYGuardarLlamadas(nombreFileSubida,1);
	Llamada** llamadasBajada = leerFicheroEntradaYGuardarLlamadas(nombreFileBajada,2);
	Llamada** llamadasOrdinario = leerFicheroEntradaYGuardarLlamadas(nombreFileOrdinario,3);

	//Se unen los 3 archivos en una lista de llamadas
  Llamada** llamadas = unirLlamadas(llamadasSubida, llamadasBajada, llamadasOrdinario);

	//Se calcular el largo de la lista
  int largoTotal = calcularLargoTotal(llamadasSubida, llamadasBajada, llamadasOrdinario);

	//Se crea he inicializa la lista de ascensores
  Ascensor** ascensores = (Ascensor**) malloc(sizeof(Ascensor*)*num_ascensores);

  for (int i = 0; i < num_ascensores; i++) {
    printf("num_ascensores: %d, %d\n",num_ascensores, i);
    ascensores[i] = (Ascensor*) malloc(sizeof(Ascensor));
    ascensores[i] = consAscensor(i+1);
  }

	//Se itera sobre la lista de llamdas
  Llamada* aux;
  while (largoTotal > 0) {
    aux = buscarLlamada(llamadas, largoTotal, tiempo);
    if (aux != NULL) {
			printf("vuelta: %d\n", largoTotal);
			//algoritmo 1
      nearestCar(ascensores, aux, num_pisos, num_ascensores);
			//Eliminar la llamada ya atendida
      llamadas = eliminarLlamada(llamadas, largoTotal, aux);
    }
    for (int i = 0; i < num_ascensores; i++) {
			printf("accionando %d\n", i);
			//Actualiza los datos del ascensor
      accion(ascensores[i], llamadas, largoTotal);
    }
    tiempo++;
		//Actualiza los estados de espera de los demas ascensores
		actualizarEsperas(ascensores,  tiempo,  num_ascensores);
    largoTotal--;
  }


	return 0;
}
