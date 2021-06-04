#ifndef __ARBOL_EXPRESION_H__
#define __ARBOL_EXPRESION_H__
#include "operadores.h"

/*
Para representar las expresiones ingresadas como Arboles de expresiones aritmeticas utilizamos un arbol binario(Ya que los
operadores a utilizar son de aridad maxima 2). Dentro de cada nodo del arbol vamos a tener:
-Tipo: 1 si es un simbolo o 0 si es un numero lo que vamos a almacenar en dicho nodo
-Simbolo: Una cadena de caracteres que representa el operador
-Operador: Del tipo Ocasilla contiene la aridad y la funcion evaluacion del operador
-Valor: Representa el numero que se quiera guardar de la operacion
-Hijos izquierdo y derecho.
*/
typedef struct _ENodo {
    int tipo;
    char *simbolo;
    OCasilla operador;
    int valor;
    struct _ENodo *Izq;
    struct _ENodo *Der;
} ENodo;

/*
Utilizamos esto para facilitar la lectura del codigo, represetamos un puntero a ENodo  como ETree 
*/
typedef ENodo *ETree;

/*
Definimos un stack que nos va a servir para prosecar las expresiones ingresadas.
Dentro de cada nodo del stack tenemos un Arbol de expresiones aritmeticas y un puntero al siguiente nodo
*/
typedef struct _SNodo {
    ETree dato;
    struct _SNodo *sig;
} SNodo;

typedef SNodo *Stack;

/*
Definicion: Toma como parametros un Stack y un Arbol de expresion aritmetica y añade un nuevo nodo al stack con 
dicho arbol como dato
*/
void push(Stack *stack, ETree dato);
/*
Definicion: Toma como parametro un Stack y devuelve el arbol de expresion aritmetica que almacenaba el primer nodo
y lo libera
*/
ETree pop(Stack *stack);

/*
Definicion: Toma como parametro un Stack y libera la memoria del mismo
*/
void liberar_stack(Stack stack);

/*
Definicion: Toma como parametros un Arbol de expresion aritmetica, la tabla de operadores y una string que representa
una expresion aritmetica.
Devuelve un arbol de expresion aritmetica formado a partir de la expresion dada


NOSE Q ONDA ESTO SI LE TENEMOS Q PASAR COMO PARAMETRO t SI AL FINAL DEVUELVE ALGO DSP FIJATE
*/
ETree cargar_expresion2(ETree t, TablaOps tablaOps, char *expresion);


void cargar_expresion(ETree *arbol, TablaOps tablaOps, char *expresion);

/*
Definicion: Toma como parametro un arbol de expresion aritmetica y libera la memoria del mismo
*/
void liberar_expresion(ETree arbol);
/*
Definicion: Toma un arbol de expresion aritmetica y lo imprime en pantalla
*/
int evaluar_expresion(ETree expresion);

/*
Definicion: Toma un arbol de expresion aritmetica y imprime el resultado de resolver la operacion que representa
*/
void Imprimir(ETree tree);

#endif // __ARBOL_EXPRESION_H__
