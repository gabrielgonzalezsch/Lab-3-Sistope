#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funciones.h"



int main(int argc, char** argv){

	int opt;
	int largo;

	char* nombreFileSubida =  (char*) malloc(sizeof(char*) * 20);
	char* nombreFileBajada =  (char*) malloc(sizeof(char*) * 20);
	char* nombreFileOrdinario =  (char*) malloc(sizeof(char*) * 20);
	int num_pisos = -1;
	int num_ascensores = -1;
	int bFLag = -1;

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


	Llamada** llamadasSubida = leerFicheroEntradaYGuardarLlamadas(nombreFileSubida);
	Llamada** llamadasBajada = leerFicheroEntradaYGuardarLlamadas(nombreFileBajada);
	Llamada** llamadasOrdinario = leerFicheroEntradaYGuardarLlamadas(nombreFileOrdinario);

	Ascensor** ascensores = inicializarAscensores(num_ascensores);

	asignarLlamadas(ascensores, llamadasSubida, llamadasBajada, llamadasOrdinario, num_ascensores, num_pisos);

	return 0;
}
