#include "arbolExpresiones.h"
#include "operadores.h"

//#include <stdlib.h>
//#include <stdio.h>
#include <ctype.h>
#include <string.h>

void push(Stack * stack, ETree dato) {
  Stack nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = *stack;
  *stack = nuevoNodo;
  printf("PUSH");
}

ETree top(Stack stack) {

  if (stack) {
    return stack->dato;
  }
  return NULL;
}

void pop(Stack * stack) {
  if (*stack) {
    Stack siguiente = (*stack)->sig;
    printf("POP\n");
    //     liberar_expresion((*stack)->dato);
    free(*stack);
    *stack = siguiente;
}
}
void liberar_expresion(ETree expresion) {
  if (expresion) {
      printf("Free en expresion\n");
      if(expresion->Izq)
    liberar_expresion(expresion->Izq);
      if(expresion->Der)
    liberar_expresion(expresion->Der);
    if(expresion->simbolo){free(expresion->simbolo);}
    free(expresion);
  }
}
void liberar_stack(Stack stack) {
  while (stack != NULL) {
      Stack siguiente = NULL;
      if(stack->sig)
          siguiente = stack->sig;
      printf("le 47\n");
      if (stack->dato)
          liberar_expresion(stack->dato);
    free(stack);
    stack = siguiente;
      // pop(&stack);
  }
}

ETree nuevo_ENodo(char *simbolo, OCasilla operador, int valor) {
  ETree nuevoNodo = malloc(sizeof(ENodo));
  if (simbolo == NULL) {
    nuevoNodo->tipo = 0;
    nuevoNodo->simbolo = NULL;
  } else {
    nuevoNodo->tipo = 1;
    nuevoNodo->simbolo = malloc(sizeof(char) * strlen(simbolo)+1);
    strcpy(nuevoNodo->simbolo, simbolo);
  }
  nuevoNodo->operador = operador;
  nuevoNodo->valor = valor;
  nuevoNodo->Izq = NULL;
  nuevoNodo->Der = NULL;
  return nuevoNodo;
}

void Imprimir(ETree tree) {

  if (tree != NULL) {
    if (tree->Izq && tree->Der)
    {
      printf("(");

    }

    Imprimir(tree->Izq);
    if (tree->tipo == 1) {
      printf("%s", tree->simbolo);

    } else {
      printf("%i", tree->valor);

    }
    Imprimir(tree->Der);
    if (!tree->Der && !tree->Izq )
    {

      printf(")");

    }
  }

}

void imprimir_stack(Stack stack) {
  for (; stack; stack = stack->sig) {

    Imprimir(stack->dato);
    printf("|");
  }
}

void cargar_expresion(ETree * arbol, TablaOps tablaOps, char *expresion) {
  Stack stack = NULL;
  int valor = 0, largoOp = 0, operadorNoExistente = 0,i=0, cantStack = 0;
  char operador[100];
  ETree t;
  OCasilla ct, casilla;
  for (i=0;expresion[i] == ' '; i++) {}
  for (; expresion[i] && !operadorNoExistente; i++) {
          if (isdigit(expresion[i])) {
        valor = valor * 10 + (expresion[i] - '0');
        largoOp = 0;
          }
      else {
          if(!largoOp){
      casilla.aridad = -1;
      casilla.eval = NULL;
      t = nuevo_ENodo(NULL, ct, valor);
      push(&stack, t);
      cantStack++;
      valor = 0;
          }
      for (;expresion[i] == ' '; i++) {}
      if (isdigit(expresion[i])||!expresion[i])
          i--;
      else {
        for (largoOp = 0; expresion[i] != ' ' && expresion[i]; i++) {
          operador[largoOp] = expresion[i];
          largoOp++;
        }
        if (expresion[i] == '\0')
          i--;
        operador[largoOp] = '\0';
        casilla = buscar_simbolo(tablaOps, operador);
        if (casilla.aridad != -1) {
          t = nuevo_ENodo(operador, casilla, 0);
           if (casilla.aridad == 2) {
            t->Der = top(stack);
            printf("pop 144\n");
            pop(&stack);
            cantStack--;
            t->Izq = top(stack);
            printf("pop 148\n");
            pop(&stack);
            cantStack--;
          } else {
            t->Der = top(stack);
            printf("pop 153\n");
            pop(&stack);
            cantStack--;
            t->Izq = NULL;
          }
          // printf("\n%s", t->Izq->simbolo);
          push(&stack, t);
          cantStack++;
          //printf("|%s|", stack->dato->simbolo);
        } else {
          operadorNoExistente = 1;
        }
      }
      }
    }
  imprimir_stack(stack);
  if (operadorNoExistente) {
    t = NULL;
    printf("ls 172\n");
    liberar_stack(stack);
  } else {
    t = top(stack);
    printf("pop 174\n");
    pop(&stack);
    cantStack--;
  }
  if (stack)
  {
    t = NULL;
    printf("ls 183\n");
    liberar_stack(stack);
    //for(;cantStack;cantStack--)
    //   pop(&stack);
    printf("STACK: ");
    imprimir_stack(stack);


  }




  Imprimir(t);


  *arbol = t;
  liberar_stack(stack);
}



int evaluar_expresion(ETree expresion) {
    int retorno = 0, temp[2];
    if(expresion){
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
