#define _DEFAULT_SOURCE
#include "arbolExpresiones.h"
#include "operadores.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


void push(Stack * stack, ETree dato) {
  Stack nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = *stack;
  *stack = nuevoNodo;
}

ETree pop(Stack * stack) {
  ETree retorno = NULL;
  if (*stack) {
    Stack siguiente = (*stack)->sig;
    retorno = (*stack)->dato;
    free(*stack);
    *stack = siguiente;
  }
  return retorno;
}

void liberar_expresion(ETree expresion) {
  if (expresion) {
    liberar_expresion(expresion->Izq);
    liberar_expresion(expresion->Der);
    free(expresion->simbolo);
    free(expresion);
  }
}

void liberar_stack(Stack stack) {
  while (stack != NULL) {
    Stack siguiente = NULL;
    siguiente = stack->sig;
    liberar_expresion(stack->dato);
    free(stack);
    stack = siguiente;
  }
}

ETree nuevo_ENodo(char *simbolo, OCasilla operador, int valor) {
  ETree nuevoNodo = malloc(sizeof(ENodo));
  if (simbolo == NULL) {        //el valor tipo del nodo es 0
    nuevoNodo->tipo = 0;        //si corresponde con un numero
    nuevoNodo->simbolo = NULL;  //es 1 si es para un operador
  } else {
    nuevoNodo->tipo = 1;
    nuevoNodo->simbolo = malloc(sizeof(char) * strlen(simbolo) + 1);
    strcpy(nuevoNodo->simbolo, simbolo);
  }
  nuevoNodo->operador = operador;
  nuevoNodo->valor = valor;
  nuevoNodo->Izq = NULL;
  nuevoNodo->Der = NULL;
  return nuevoNodo;
}

void imprimir_ETree(ETree tree) {
  if (tree != NULL) {
    if (tree->Izq || tree->Der)
      printf("(");
    imprimir_ETree(tree->Izq);
    if (tree->tipo == 1)
      printf("%s", tree->simbolo);
    else
      printf("%i", tree->valor);
    imprimir_ETree(tree->Der);
    if (tree->Izq || tree->Der)
      printf(")");
  }
}

int es_num(char *string) {
  int retorno = 1;
  for (int i = 0; string[i] && retorno; i++) {
    if (!isdigit(string[i]))
      retorno = 0;
  }
  return retorno;
}

ETree cargar_expresion(TablaOps tablaOps, char *expresion) {
  char *string;
  OCasilla casilla;
  Stack stack = NULL;
  ETree t = NULL;

  while ((string = strsep(&expresion, " "))) {  //string avanza por cada espacio
    casilla = buscar_simbolo(tablaOps, string); //busca si es un operador
    if (casilla.aridad != -1) { //si no es un operador tiene aridad de -1
      t = nuevo_ENodo(string, casilla, 0);      //pone el operador como nodo
      t->Der = pop(&stack);     //el top del stack es su hijo derecho
      if (!t->Der) {            //si es NULL es porque no habia nada para usar
        liberar_expresion(t);   //la expresion seria invalida
        return NULL;
      }
      if (casilla.aridad == 2) {        //comprueba si necesita hijo izquierdo
        t->Izq = pop(&stack);   //que seria el top del stack
        if (!t->Izq) {
          liberar_expresion(t); //si no hay es invalida la expresion
          return NULL;
        }
      } else
        t->Izq = NULL;          //si no necesita 2 hijos lo pone null
      push(&stack, t);          //pushea el nuevo nodo al stack
    } else {
      if (es_num(string)) {     //comprueba que el string sean solo numeros
        int valor = atoi(string);       //castea a int
        casilla.aridad = -1;    //valores predefinidos para los nodos numero
        casilla.eval = NULL;
        t = nuevo_ENodo(NULL, casilla, valor);  //crea el nodo
        push(&stack, t);        //pushea el nodo numero al stack
      } else {                  //si no eran solo ints entonces es un operador no valido
        liberar_stack(stack);   //libera el stack ya que no esta vacio
        return NULL;
      }
    }
  }
  t = pop(&stack);              //el top del stack deberia ser el arbol final
  if (stack) {                  //si no esta vacio es porque la expresion era incorrecta
    liberar_expresion(t);       //libera el top previamiente popeado
    liberar_stack(stack);       //libera el resto del stack
    return NULL;
  }
  return t;
}

int evaluar_expresion(ETree expresion) {
  int retorno = 0, temp[2];
  if (expresion) {
    if (expresion->tipo) {
      if (expresion->operador.aridad == 1) {
        temp[0] = evaluar_expresion(expresion->Der);
      } else {
        temp[0] = evaluar_expresion(expresion->Izq);
        temp[1] = evaluar_expresion(expresion->Der);
      }
      retorno = expresion->operador.eval(temp);
    } else {
      retorno = expresion->valor;
    }
  }
  return retorno;
}
