#include "operadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int suma(int *args) {
  return args[0] + args[1];
}

int resta(int *args) {
  return args[0] - args[1];
}

int opuesto(int *args) {
  return (-1) * args[0];
}

int producto(int *args) {
  return args[0] * args[1];
}

//Optamos por devolver 0 si se divide por 0
int division(int *args) {
  return args[1] == 0 ? 0 : round(args[0] / args[1]);
}

int modulo(int *args) {
  return args[0] % args[1];
}

int potencia(int *args) {
  return pow(args[0], args[1]);
}

void cargar_operador(TablaOps * tabla, char *simbolo, int aridad,
                     FuncionEvaluacion eval) {
  TablaOps nuevoNodo = malloc(sizeof(ONodo));
  nuevoNodo->simbolo = simbolo;
  nuevoNodo->casilla.aridad = aridad;
  nuevoNodo->casilla.eval = eval;
  nuevoNodo->sig = *tabla;
  *tabla = nuevoNodo;
}

void liberar_tabla(TablaOps tabla) {
  while (tabla) {
    TablaOps siguiente = tabla->sig;
    free(tabla);
    tabla = siguiente;
  }
}

OCasilla buscar_simbolo(TablaOps tabla, char *simbolo) {
  OCasilla retorno;
  retorno.aridad = -1;
  for (; tabla && retorno.aridad == -1; tabla = tabla->sig) {
    if (!strcmp(simbolo, tabla->simbolo))
      retorno = tabla->casilla;
  }
  return retorno;
}
