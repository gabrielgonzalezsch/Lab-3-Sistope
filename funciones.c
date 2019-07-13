#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funciones.h"


void leerArchivo(char* nombre){
  // ############################################### Leer archivo Y Mandar Visibilidades ###########################################################################
  FILE* archivo = fopen(nombre,"r");
  int cont = 0;
  double u,v,real,imag,ruido;
  int disco;
  int posicion;
  char c1,c2,c3,c4;
  // Aqui se lee el archivo guardando cada linea en el atributo dato de cada hebra
  while(!feof(archivo))
  {

      u = 0;
      v = 0;
      real = 0;
      imag = 0;
      ruido = 0;

      fscanf(archivo, "%lf %c %lf %c %lf %c %lf %c %lf", &u,&c1,&v,&c2,&real,&c3,&imag,&c4,&ruido);
      //printf("%lf %lf %lf %lf %lf\n", u,v,real,imag,ruido);


  }

  fclose(archivo);
}
