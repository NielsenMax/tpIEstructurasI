#include "arbolExpresiones.h"
#include "operadores.h"
//#include <stdlib.h>
//#include <stdio.h>
#include <ctype.h>

void push(Stack *stack, ETree dato) {
    Stack nuevoNodo = malloc(sizeof(SNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = *stack;
    *stack = nuevoNodo;
}

ETree top(Stack stack) {
    if (stack) {
        printf("devolvi:%s\n", stack->dato->simbolo);
        return stack->dato;
    }
    return NULL;
}

void pop(Stack *stack) {
    ETree retorno = NULL;
    if (*stack) {
        Stack siguiente = (*stack)->sig;
        retorno = (*stack)->dato;
        //liberar_expresion((*stack)->dato);
        free(*stack);
        *stack = siguiente;
    }
    //return retorno
}

void liberar_stack(Stack stack) {
    while (stack) {
        Stack siguiente = stack->sig;
        liberar_expresion(stack->dato);
        free(stack);
        stack = siguiente;
    }
}

ETree nuevo_ENodo(char *simbolo, OCasilla operador, int valor ) {
    ETree nuevoNodo = malloc(sizeof(ENodo));
    if(simbolo == NULL)
        nuevoNodo->tipo = 0;
        else
            nuevoNodo->tipo = 1;
    nuevoNodo->simbolo = simbolo;
    nuevoNodo->operador = operador;
    nuevoNodo->valor = valor;
    nuevoNodo->Izq = NULL;
    nuevoNodo->Der = NULL;
    return nuevoNodo;
}

void Imprimir(ETree tree){
    if(tree!=NULL){
        printf("(");
        Imprimir(tree->Izq);
        if(tree->tipo == 1){
            printf("%s",tree->simbolo);
            }
        else{
            printf("%i",tree->valor);
        }
        Imprimir(tree->Der);
        printf(")");
       }

}

void imprimir_stack(Stack stack){
 printf("\nEMpieza");
    for(;stack;stack = stack->sig){

            Imprimir(stack->dato);
            printf("\n");
    }
}

void cargar_expresion(ETree *arbol, TablaOps tablaOps, char *expresion) {
    Stack stack = NULL;
    int valor = 0, largoOp = 0, operadorNoExistente = 0;
    char operador[100];
    ETree t, t1, t2;
    OCasilla ct, casilla;
    for (int i = 0; expresion[i] && !operadorNoExistente; i++) {
        //printf("%c", expresion[i]);
        if (expresion[i] == ' ') {
            //printf("%i", valor);
            ct.aridad = -1;
            ct.eval = NULL;
            t = nuevo_ENodo(NULL, ct, valor);

            push(&stack, t);
            imprimir_stack(stack);
            //printf("!%i!", stack->dato->valor);
            valor = 0;
        } else {
        if (isdigit(expresion[i]))
            valor = valor * 10 + (expresion[i] - '0');
            else {
                operador[0] = '\0';
                for(largoOp = 0; expresion[i] != ' ' && expresion[i]; i++) {
                    operador[largoOp] = expresion[i];
                    largoOp++;
                }
                if(expresion[i] == '\0') i--;
                operador[largoOp] = '\0';
                casilla = buscar_simbolo(tablaOps, operador);
                printf("%s, %i\n", operador, casilla.aridad);
                if (casilla.aridad != -1) {


                    t = nuevo_ENodo(operador, casilla, 0);
                    if (casilla.aridad == 2){
                        t->Der = top(stack);
                        pop(&stack);
                        t->Izq = top(stack);
                        pop(&stack);
                    }else {
                        t->Izq = top(stack);
                        pop(&stack);
                        t->Der = NULL;
                    }

                    // printf("\n%s", t->Izq->simbolo);
                    push(&stack, t);
                    printf("\n segundo");
                    imprimir_stack(stack);
                    //printf("|%s|", stack->dato->simbolo);
                } else {
                    operadorNoExistente = 1;
                }
            }
        }
    }
    printf("op=%i\n", operadorNoExistente);
    //imprimir_stack(stack);
    if (operadorNoExistente) {
        t = NULL;
        liberar_stack(stack);
    } else {
        t = top(stack);
    pop(&stack);
    }
    printf("hola\n");
     Imprimir(t);
    *arbol = t;
}

void liberar_expresion(ETree expresion) {
    if (expresion) {
        liberar_expresion(expresion->Izq);
        liberar_expresion(expresion->Der);
        free(expresion);
    }
}





int main() {
    TablaOps tabla = NULL;
    cargar_operador(&tabla, "+", 2, suma);
    cargar_operador(&tabla, "-", 2, resta);
    cargar_operador(&tabla, "--", 1, opuesto);
    cargar_operador(&tabla, "*", 2, producto);
    cargar_operador(&tabla, "/", 2, division);
    cargar_operador(&tabla, "%", 2, modulo);
    cargar_operador(&tabla, "^", 2, potencia);
    ETree t = NULL;
    liberar_expresion(t);
    cargar_expresion(&t, tabla, "5 -- 13 + 2 * 7 +");
    if(t){
        printf("\nMIRAR:%s", t->Izq->Izq->simbolo);
        Imprimir(t);
    }
    liberar_tabla(tabla);
}
