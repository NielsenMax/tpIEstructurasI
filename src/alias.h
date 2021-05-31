#ifndef __ARBOL_ALIAS_H__
#define __ARBOL_ALIAS_H__
#include "arbolExpresiones.h"


typedef struct _ANodo{
    char *alias;
    ETree arbol;
    struct _ANodo *Izq;
    struct _ANodo *Der;
} ANodo;
typedef ANodo *ATree;

void liberar_alias(ATree tree);
ATree insertar_alias(ETree operacion,ATree raiz,char *pal);

#endif // _ARBOL_ALIAS_H_