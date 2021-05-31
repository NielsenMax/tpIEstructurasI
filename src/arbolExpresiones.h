#ifndef __ARBOL_EXPRESION_H__
#define __ARBOL_EXPRESION_H__
#include "operadores.h"


typedef struct _ENodo {
    int tipo;
    char *simbolo;
    OCasilla operador;
    int valor;
    struct _ENodo *Izq;
    struct _ENodo *Der;
} ENodo;

typedef ENodo *ETree;

typedef struct _SNodo {
    ETree dato;
    struct _SNodo *sig;
} SNodo;

typedef SNodo *Stack;

void push(Stack *stack, ETree dato);

void pop(Stack *stack);

void liberar_stack(Stack stack);

void cargar_expresion(ETree *arbol, TablaOps tablaOps, char *expresion);

void liberar_expresion(ETree arbol);

int evaluar_expresion(ETree expresion);
void Imprimir(ETree tree);

#endif // __ARBOL_EXPRESION_H__
