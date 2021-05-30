#include "operadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int suma(int *args) {
  return args[0] + args[1];
}

int resta(int *args) {
    return args[0] - args[1];
}

int opuesto(int *args) {
    return (-1) * args[0];
}

int division(int *args) {
    return round(args[0] / args[1]);
}

int modulo(int *args) {
    return args[0] % args[1];
}

int potencia(int *args) {
    return pow(args[0], args[1]);
}

void cargar_operador(TablaOps *tabla, char *simbolo, int aridad, FuncionEvaluacion eval) {
    TablaOps nuevoNodo = malloc(sizeof(ONodo));
    nuevoNodo->simbolo = simbolo;
    nuevoNodo->aridad = aridad;
    nuevoNodo->eval = eval;
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



int main() {
    TablaOps tabla = NULL;
    cargar_operador(&tabla, "+", 2, suma);
    printf("%i", tabla->eval((int[2]) {3 ,4}));
    liberar_tabla(tabla);
    return 0;
}
