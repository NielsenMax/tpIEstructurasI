#include "alias.h"
#include "arbolExpresiones.h"
#include <ctype.h>
#include <string.h>

ATree insertar_alias(ETree operacion, ATree raiz, char *pal) {
  if (raiz == NULL) {
    ATree nuevoNodo = malloc(sizeof(ANodo));
    nuevoNodo->alias = malloc(sizeof(char) * strlen(pal) + 1);
    strcpy(nuevoNodo->alias, pal);
    nuevoNodo->arbol = operacion;
    nuevoNodo->Izq = NULL;
    nuevoNodo->Der = NULL;
    return nuevoNodo;
  } else if (strcmp(raiz->alias, pal) > 0) {
    raiz->Izq = insertar_alias(operacion, raiz->Izq, pal);
  } else {
    raiz->Der = insertar_alias(operacion, raiz->Der, pal);
  }
  return raiz;
}

ETree buscar_alias(ATree aliases, char *pal) {
  if (aliases == NULL) {
    return NULL;
  } else if (strcmp(aliases->alias, pal) == 0) {
    return (aliases->arbol);
  } else if (strcmp(aliases->alias, pal) > 0) {
    return buscar_alias(aliases->Izq, pal);
  } else {
    return buscar_alias(aliases->Der, pal);
  }
}

void imprimir_alias(ATree aliases, char *pal) {
  ETree t = NULL;
  t = buscar_alias(aliases, pal);
  if (t) {
    imprimir_ETree(t);
  } else {
    printf("El alias no esta cargado, no se puede imprimir");
  }
}

void evaluar_alias(ATree aliases, char *pal) {
  ETree t = NULL;
  t = buscar_alias(aliases, pal);
  if (t) {
    printf("\nEVALUAR: %i\n", evaluar_expresion(t));
  } else {
    printf("El alias no esta cargado, no se puede evaluar");
  }
}

void liberar_alias(ATree tree) {
  if (tree != NULL) {
    liberar_alias(tree->Izq);
    liberar_alias(tree->Der);
    liberar_expresion(tree->arbol);
    free(tree->alias);
    free(tree);
  }
}
