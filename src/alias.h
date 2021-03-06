#ifndef __ARBOL_ALIAS_H__
#define __ARBOL_ALIAS_H__
#include "arbolExpresiones.h"
/*
Para relacionar cada alias con la expresion ingresada utilizamos
un arbol de busqueda binario, cada nodo contiene
el alias, el arbol de expresion aritmetica, un puntero al
hijo izquierdo y un puntero al hijo derecho.
Para realizar las busquedas dentro del arbol utilizamos el
alias ordenando el arbol en orden alfabetico.
(El arbol no esta balanceado)
*/
typedef struct _ANodo {
  char *alias;
  ETree arbol;
  struct _ANodo *Izq;
  struct _ANodo *Der;
} ANodo;
typedef ANodo *ATree;

/*
liberar_alias :: ATree -> ()
Definicion: Toma como parametro un Arbol de alias y
libera la memoria de cada nodo.
*/
void liberar_alias(ATree tree);

/*
insertar_alias :: ETree -> ATree -> (*char) -> ATree
Definicion: Toma como parametro un Arbol de expresion aritmetica,
un Arbol de alias, y una string y añade un nuevo nodo
al Arbol de alias con los datos dados en los parametros.
*/
ATree insertar_alias(ETree operacion, ATree raiz, char *pal);

/*
buscar_alias :: ATree -> (*char) -> ETree
Definicion: Toma como parametro un Arbol de Alias y un string,
devuelve el Arbol de expresiones aritmeticas asociado
a dicho alias
*/
ETree buscar_alias(ATree aliases, char *pal);

/*
imprimir_alias :: ATree -> (*char) -> ()
Definicion: Toma como parametro un Arbol de alias y una string e
imprime el Arbol de expresiones aritmeticas asociado a
alias.
*/
void imprimir_alias(ATree aliases, char *pal);

/*
evaluar_alias :: ATree -> (*char) -> ()
Definicion: Toma como parametro un Arbol de alias y una string y
devuelve la evaluacion de la expresion aritmetica
asociada a dicha string.
*/
void evaluar_alias(ATree aliases, char *pal);

#endif                          // _ARBOL_ALIAS_H_
