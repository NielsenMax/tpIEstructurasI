#infndef __ARBOL_ALIAS_H__
#define __ARBOL_ALIAS_H__
#include "operadores.h"
#include "arbolExpresiones.h"

typedef struct _ANodo{
    char *alias;
    struct ETree arbol;
    struct _Anodo *Izq;
    struct _Anodo *Der;
}ANodo;
typedef ANodo *ATree
void insertar_alias(ETree operacion,Atree aliases,char alias);
void Imprimir(ETree tree);
void liberar_alias(ATree tree);
ATree insertar_alias(ETree operacion,Atree raiz,char pal)