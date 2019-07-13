all: padre

padre: main.c
	gcc main.c funciones.c -o lab3 -lm
