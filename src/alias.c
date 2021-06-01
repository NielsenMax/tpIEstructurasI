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

ETree Buscar_alias(ATree aliases,char *pal){
    int no=1;
    if(aliases==NULL){
        return NULL;
    }
    else if (strcmp(aliases->alias,pal)==0)
        {
            return(aliases->arbol);
            no=0;
        }
    else if (strcmp(aliases->alias,pal)>0)
        {            
            return Buscar_alias(aliases->Izq,pal);
            no=0;
        }
    else
        {           
            return Buscar_alias(aliases->Der,pal);
            no=0;
        }    

    if(no){
        printf("\n no se encontro el alias\n");        
    }
}

void Imprimir_alias(ATree aliases,char *pal){
    Imprimir(Buscar_alias(aliases,pal));
}

void Evaluar_alias(ATree aliases,char *pal){
    printf("\nEVALUAR: %i\n",evaluar_expresion(Buscar_alias(aliases,pal)));
}
void liberar_alias(ATree tree) {
    if(tree!=NULL){

        liberar_alias(tree->Izq);
        liberar_alias(tree->Der);
        liberar_expresion(tree->arbol);
        free(tree->alias);
        free(tree);}

}



