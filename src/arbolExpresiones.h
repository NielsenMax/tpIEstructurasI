#ifndef __ARBOL_EXPRESION_H__
#define __ARBOL_EXPRESION_H__
#include "operadores.h"

/*
Para representar las expresiones ingresadas
como Arboles de expresiones aritmeticas utilizamos un arbol binario(Ya que los
operadores a utilizar son de aridad maxima 2).
Dentro de cada nodo del arbol vamos a tener:
-Tipo: 1 si es un operador
-Tipo:  0 si es un numero
-Simbolo: Una cadena de caracteres que representa el operador
-Operador: Del tipo OCasilla contiene la aridad y la funcion evaluadora
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
Utilizamos esto para facilitar la lectura del codigo,
represetamos un puntero a ENodo  como ETree
*/
typedef ENodo *ETree;

/*
Definimos un stack que nos va a servir para procesar las expresiones ingresadas.
Dentro de cada nodo del stack tenemos un Arbol de expresiones aritmeticas
y un puntero al siguiente nodo
*/
typedef struct _SNodo {
  ETree dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *Stack;

/*
push :: (*Stack) -> ETree -> ()
Definicion: Toma como parametros un Stack y un Arbol de expresion aritmetica
añade un nuevo nodo al stack con dicho arbol como dato
*/
void push(Stack * stack, ETree dato);
/*
pop :: (*Stack) -> ETree
Definicion: Toma como parametro un Stack y
devuelve el arbol de expresion aritmetica
que almacenaba el primer nodo y libera el nodo del stack
*/
ETree pop(Stack * stack);

/*
liberar_stack :: Stack -> ()
Definicion: Toma como parametro un Stack y libera la memoria del mismo
*/
void liberar_stack(Stack stack);

/*
cargar_expresion :: TablaOps -> (*char) -> ETree
Definicion: Toma como parametros la tabla de operadores
y una string que representa una expresion aritmetica.
Devuelve un arbol de expresion aritmetica formado a partir de la expresion dada

Para construir el arbol de expresion aritmetica usamos un stack.
Avanzamos por cada substring delimitado por espacios y comprobamos:
>Si el string es un numero lo pusheamos al stack como un nodo tipo 0
>Si el string es un operador popeamos del stack la cantidad de nodos
 que tenga como ariadad. Ponemos al primero como hijo derecho y
 al segundo como hijo izquierdo, luego lo pusheamos al stack al nodo resultante.
El nodo que quede en el top del stack corresponde a la expresion parseada

Casos de expresiones incorrectas:
>El string es un operador no valido (no esta en la tabla de operadores):
  -Liberamos el stack
  -Devolvemos NULL
>La aridad del operador es mayor que la cantidad de nodos del stack:
  -Liberamos el nodo operador
  -No necesitamos liberar el stack ya que esta vacio
  -Devolvemos NULL
>El stack contiene nodos luego de terminar de leer la expresion:
  -Liberamos la expresion resultante
  -Liberamos el stack
  -Devolvemos NULL
*/
ETree cargar_expresion(TablaOps tablaOps, char *expresion);


/*
liberar_expresion :: ETree -> ()
Definicion: Toma como parametro un arbol de expresion aritmetica
y libera la memoria del mismo
*/
void liberar_expresion(ETree arbol);

/*
evaluar_expresion :: ETree -> int
Definicion: Toma un arbol de expresion aritmetica y
imprime el resultado de resolver la operacion que representa.

Para hacer esto realizamos:
>Si es un nodo de un numero devolvemos el valor
>Si es un nodo de un operador:
  >Evaluamos el arbol derecho
  >Si la ariadad es 2, evaluamos el arbol izquierdo
  >Aplicamos la funcion del operador al arbol izquierdo (si es posible)
   y al derecho
  >Devolvemos el resultado
*/
int evaluar_expresion(ETree expresion);


/*
imprimir_ETree :: ETree -> ()
Definicion: Toma un arbol de expresion aritmetica y lo imprime en pantalla
*/
void imprimir_ETree(ETree tree);

/*
nuevo_ENodo :: (*char) -> OCasilla -> int -> ETree
Definicion: Toma un puntero a char, un operador del tipo OCasilla
y un valor int. Crea un nuevo nodo del tipo ENodo, siendo del tipo 0
si es un numero y del tipo 1 si es un operador
*/
ETree nuevo_ENodo(char *simbolo, OCasilla operador, int valor);
/*
es_num :: (*char) -> int
Definicion: Toma un puntero a char y devuelve 1 si todos sus caracteres
son digitos.
*/
int es_num(char *string);

#endif                          // __ARBOL_EXPRESION_H__
