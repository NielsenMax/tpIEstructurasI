#ifndef __OPERADORES_H__
#define __OPERADORES_H__
#include <stdlib.h>
#include <stdio.h>

typedef int (*FuncionEvaluacion)(int *args);

typedef struct _OCasilla {
    int aridad;
    FuncionEvaluacion eval;
} OCasilla;

typedef struct _ONodo {
    char *simbolo;
    OCasilla casilla;
    struct _ONodo *sig;
} ONodo;

typedef ONodo *TablaOps;

void cargar_operador(TablaOps *tabla, char *simbolo, int aridad, FuncionEvaluacion eval);

OCasilla buscar_simbolo(TablaOps tabla, char *simbolo);

void liberar_tabla(TablaOps tabla);

int suma(int *args);
int resta(int *args);
int opuesto(int *args);
int producto(int *args);
int division(int *args);
int modulo(int *args);
int potencia(int *args);

#endif /** __OPERADORES_H__ **/
