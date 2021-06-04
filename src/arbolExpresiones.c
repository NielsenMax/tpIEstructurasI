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

ETree top(Stack stack) {

  if (stack) {
    return stack->dato;
  }
  return NULL;
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
  if (simbolo == NULL) {
    nuevoNodo->tipo = 0;
    nuevoNodo->simbolo = NULL;
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

      printf("(");
      imprimir_ETree(tree->Izq);
      if (tree->tipo == 1) {
          printf("%s", tree->simbolo);
      } else {
          printf("%i", tree->valor);
      }
      imprimir_ETree(tree->Der);
      printf(")");
    }

}

void imprimir_stack(Stack stack) {
  for (; stack; stack = stack->sig) {
    imprimir_ETree(stack->dato);
    printf("|");
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
    char* string;
    OCasilla casilla;
    Stack stack = NULL;
    ETree t = NULL;

    while ((string = strsep(&expresion, " "))) {
       casilla = buscar_simbolo(tablaOps, string);
       if(casilla.aridad != -1) {
           t = nuevo_ENodo(string, casilla, 0);
           t->Der = pop(&stack);
           if (!t->Der) {
               liberar_expresion(t);
               return NULL;
           }
           if (casilla.aridad == 2) {
               t->Izq = pop(&stack);
               if(!t->Izq) {
                   liberar_expresion(t);
                   return NULL;
               }
           }
           else
               t->Izq = NULL;
           push(&stack, t);
       } else {
           if (es_num(string)) {
               int valor = atoi(string);
               casilla.aridad = -1;
               casilla.eval = NULL;
               t = nuevo_ENodo(NULL, casilla, valor);
               push(&stack, t);
           } else {
               liberar_stack(stack);
               return NULL;
           }
       }
   }
   t = pop(&stack);
   if (stack) {
       liberar_expresion(t);
       liberar_stack(stack);
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
