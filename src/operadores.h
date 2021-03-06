#ifndef __OPERADORES_H__
#define __OPERADORES_H__
#include <stdlib.h>
#include <stdio.h>

typedef int (*FuncionEvaluacion)(int *args);
/*
Cada operador lo representamos como una casilla de una tabla
que contiene a todos los operadores cargados.
Para representar esta tabla utilizamos una lista enlazada.
Cada casilla contiene la aridad del operador y su funcion evaluacion
*/
typedef struct _OCasilla {
  int aridad;
  FuncionEvaluacion eval;
} OCasilla;
/*
Dentro de cada nodo de la tabla almacenamos el simbolo que representa al
operador, la casilla q contiene la aridad y funcion
evaluacion y un puntero al siguiente elemento
*/
typedef struct _ONodo {
  char *simbolo;
  OCasilla casilla;
  struct _ONodo *sig;
} ONodo;
/*
Utilizamos esto para facilitar la lectura del codigo,
represetamos un puntero a ONodo como TablaOps
*/
typedef ONodo *TablaOps;

/*
cargar_operador :: (*TablaOps) -> (*char) -> int -> ()
Definicion: Toma como parametros la tabla de operadores, un string,
un int y una funcion. El String representa el simbolo,
el int la aridad y el puntero a funcion la funcion evaluacion
de un operador que se va a agregar a la tabla.
*/
void cargar_operador(TablaOps * tabla, char *simbolo, int aridad,
                     FuncionEvaluacion eval);
/*
buscar_simbolo :: TablaOps -> (*char) -> OCasilla
Definicion: Toma como parametros la tabla de operadores y un string.
El string representa el simbolo de un operador.
Revisa la tabla en busca de dicho operador y si lo encuentra lo devuelve.
Si no lo encuntra devuelve un operador con aridad -1
y su puntero a la funcion evaluadora es null
*/
OCasilla buscar_simbolo(TablaOps tabla, char *simbolo);

/*
liberar_tabla :: TablaOps -> ()
Definicion: libera la memoria de la tabla de operadores
*/
void liberar_tabla(TablaOps tabla);
/*
Funciones de evaluacion de los operadores.
*/
int suma(int *args);
int resta(int *args);
int opuesto(int *args);
int producto(int *args);
int division(int *args);
int modulo(int *args);
int potencia(int *args);

#endif /** __OPERADORES_H__ **/
