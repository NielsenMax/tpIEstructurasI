#include "alias.h"
#include "arbolExpresiones.h"

#include <ctype.h>
#include <string.h>

ATree insertar_alias(ETree operacion,ATree raiz,char *pal){

    if(raiz==NULL){
        ATree nuevoNodo = malloc(sizeof(ANodo));
        nuevoNodo->alias = malloc(sizeof(char) * strlen(pal)+1);
        strcpy(nuevoNodo->alias,pal);
        nuevoNodo->arbol = operacion;
        nuevoNodo->Izq = NULL;
        nuevoNodo->Der = NULL;
        return nuevoNodo;
    }
    else if(strcmp(raiz->alias,pal)>0){
        raiz->Izq = insertar_alias(operacion,raiz->Izq,pal);
    }
    else
    {
        raiz->Der = insertar_alias(operacion,raiz->Der,pal);
    }
    return raiz;



}


void Imprimir_alias(ATree aliases,char *pal){
    if(aliases!=NULL){
        if (strcmp(aliases->alias,pal)==0)
        {
            Imprimir(aliases->arbol);
        }
        else if (strcmp(aliases->alias,pal)>0)
        {
            Imprimir_alias(aliases->Izq,pal);
        }
        else
        {
            Imprimir_alias(aliases->Der,pal);
        }




    }
}
void liberar_alias(ATree tree) {
    if(tree!=NULL){

        liberar_alias(tree->Izq);
        liberar_alias(tree->Der);
        free(tree->alias);
        free(tree);}

}
int main(){
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
  cargar_expresion(&t, tabla, "5 1 + -- 13+ 2*       7+");
  ATree T=NULL;
  if (t) {
    Imprimir(t);
    T=insertar_alias(t,T,"hola");
    T=insertar_alias(t,T,"ahola");
    Imprimir_alias(T,"ahola");
    printf("%i", evaluar_expresion(t));
  }
  liberar_tabla(tabla);
  liberar_expresion(t);
  liberar_alias(T);


}
