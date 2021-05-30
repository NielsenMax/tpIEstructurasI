#include "alias.h"

ATree insertar_alias(ETree operacion,Atree raiz,char pal){
    if(raiz==NULL){
        ATree nuevoNodo = malloc(sizeof(ANodo));
        nuevoNodo->alias = pal;
        nuevoNodo->arbol = operacion;
        nuevoNodo->Izq = NULL;
        nuevoNodo->Der = NULL;
        return nuevoNodo
    }
    else if(strcmp(*aliases->alias,pal)>0){
        raiz->Izq = insertar_alias(operacion,raiz->Izq,pal);
    }
    else
    {
        raiz->Der = insertar_alias(operacion,raiz->Der,pal);
    }
    return raiz;
    
  
}
Int evaluar(ETree tree,TablaOps tabla)
{
    if
    tabla->eval
}
void Imprimir(ETree tree){
    if(tree!=NULL){
        printf("(");
        Imprimir(tree->Izq);
        if(tree->simbolo){
            printf("%s",tree->simbolo);
            }
        else{
            printf("%i",tree->valor);
        }
        Imprimir(tree->Der);
        printf(")");
       }

}
void Imprimir_alias(ATree aliases,char *pal){
    if(aliases!=NULL){
        if (strcmp(aliases->alias,pal)==0)
        {
            Imprimir(aliases->arbol)
        }
        else if (strcmp(aliases->alias,pal)>0)
        {
            Imprimir_alias(aliases->Izq);
        }
        else
        {
            Imprimir_alias(aliases->Der);
        }
        
        
        

    }
}
void liberar_alias(ATree tree) {
    if(tree!=NULL){
        liberar_alias(tree->Izq);
        liberar_alias(tree->Der);
        free(tree);}

}