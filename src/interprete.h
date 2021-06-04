#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__
#include "alias.h"
/*
leer :: () -> (*Char)
Definicion: Permite el ingreso de un array dinamicamente. El tamaño del buffer para los reallocs es editable.
*/
char *leer();

/*
opciones :: (* Char) -> (* Int) -> ()
Definicon: Toma un string y un puntero a un int como parametros, el string representa la input que se realizo por teclado y
el puntero a int almacena el valor donde terminan las palabras claves dentro de la input, para poder utilizarlo despues.
Devuelve:
-0 Si el comando ingresado hace referencia a un alias y una expresion para caragar
-1 Si el comando es imprimir
-2 Si el comando es evaluar
-3 Si el input no concuerda con ningun comando y por lo tanto es invalido
*/
int opciones(char *input,int *fin);

/*
minusculas :: (* Char) -> ()
Definicion: Toma un string. Transforma todo los caracteres de la string a minuscula.
*/
void minusculas(char *palabra);

/*
normalizar_expresion :: (* Char) -> ()
Definicion: Toma un string. La normaliza quitando todos los espacios demas entre palabras al inicio y al final.
*/
void normalizar_expresion(char *string);

/*
interpretar_IoE :: (* Char) -> Int -> ATree -> Int -> ()
Definicion: Toma un string, un puntero a int, un arbol de alias y un int. El string representa el input que se realizo,
el primer int(fin) almacena el lugar en la string de la input donde finaliza la palabra clave del comando, y el segundo int(IoE)
representa cual de las opciones devolvio la funcion opciones.
Imprime o evalua el alias dependiendo de la input dada.
*/
void interpretar_IoE(char *input,int fin,ATree T,int ioe);

/*
interpretar_alias :: (* Char) -> ATree -> TablaOps -> Int -> ATree
Definicion: Toma un string, un arbol de alias, la tabla de operadores y un int. El string representa el input que se realizo y
el valor int almacena el lugar en la string de la input donde finaliza la palabra clave del comando.
Analiza el input y separa el alias de la expresion y almacena los datos en el arbol de alias.
La expresion la almacena como un arbol de expresion aritmetica
*/
ATree interpretar_alias(char *input,ATree T,TablaOps tabla,int fin);

/*
interpretar :: ATree -> TablaOps
Definicion: Toma como parametro la tabla de operadores y realiza el loop principal del programa para poder ingresar comandos.
*/
void interpretar(ATree T,TablaOps tabla);


/*
presentacion :: () -> ()
Definicion: Imprime una explicacion sobre el uso del programa
*/
void presentacion();
#endif // __INTERPRETE_H__
