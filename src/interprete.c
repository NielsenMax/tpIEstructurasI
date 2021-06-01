#include "interprete.h"
#include "alias.h"
#include <ctype.h>
#include <string.h>

char *leer()
{
    char *line = NULL, *tmp = NULL;
    size_t size = 0, index = 0;
    int ch = EOF;

    while (ch) {
        ch = getchar();


        if (ch == EOF || ch == '\n')
            ch = 0;


        if (size <= index) {
            size += 1;
            tmp = realloc(line, size);
            if (!tmp) {
                free(line);
                line = NULL;
                break;
            }
            line = tmp;
        }

        
        line[index++] = ch;
    }

    return line;
}



int opciones(char *input,int *fin){
    int i,t=0;
    char temp[strlen(input)];
    temp[0]='\0';
    for(i=0;input[i];i++){
        if(temp[0] && input[i]==' ')
        {
            
            if(!strcmp(temp,"imprimir")){
               
               *fin=i;
               return 1; 
            }
            else if(!strcmp(temp,"evaluar")){
                *fin=i;
                return 2;
            }
            else{
                return 0;
            }
        }
        if(input[i]!=' '){
            temp[t]=input[i];
            t++;
            temp[t]='\0';
        }

    }
    
    if(!strcmp(temp,"imprimir")){
               
               *fin=i;
               return 1; 
            }
            else if(!strcmp(temp,"evaluar")){
                *fin=i;
                return 2;
            }
            else{
                
                return 0;
            }
}

void interpretar_IoE(char *input,int fin,ATree T,int ioe)
{
    int i,t=0,espacio=0;
    char temp[strlen(input)];
    for(i=fin;input[i];i++)
    {
        if(espacio)
        {
            temp[t]=input[i];
            t++;
        }
        else
        {
            if(input[i+1]!=' '){
                espacio=1;
            }
        }
        
    }
    temp[t]='\0';
    if(ioe==1){
        Imprimir_alias(T,temp);
    }
    else
    {
        Evaluar_alias(T,temp);
    }
    

}


void interpretar_alias(char *input,ATree T,TablaOps tabla){
    
    int i,ta=0,te=0,espacio=0,igual=0;
    int len=strlen(input);
    char tempa[len],tempe[len];
    if(input[0]!=' ')
        espacio=1;
    for(i=0;input[i];i++)
    {
        if(input[i+1]!=' '){
                espacio=1;
        }
        if(input[i+1]=='=')
        {
                igual=1;
        }
        if(espacio && !igual && input[i]!='=')
        {
            tempa[ta]=input[i];
            ta++;
        }
        else if(espacio && igual && input [i]!= '=')
        {   
            tempe[te]=input[i];
            te++;
        }
    
        
    }
    tempa[ta]='\0';
    tempe[te]='\0';
    printf("%s,%s",tempa,tempe);
    ETree t=NULL;
    liberar_expresion(t);
    cargar_expresion(&t,tabla,tempe);
    T=insertar_alias(t,T,tempa);
    
    

    
}

void interpretar(ATree T,TablaOps tabla){
  printf("ingrese linea\n:");
  char *input=leer();
  
  while (strcmp(input,"salir"))
  {
      printf("\n");
      int a,*fin=&a;      
      int menu=opciones(input,fin);
      printf("OPCION: %i\n",menu);
      if(menu){
          if(menu==1){
              
              interpretar_IoE(input,a,T,menu);
              
          }
          else{
           interpretar_IoE(input,a,T,menu);
          }
      }
      else
      {
         interpretar_alias(input,T,tabla);
      }
      free (input);      
      input=leer();
  
  }
  free(input);
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
  cargar_expresion(&t, tabla, "    5   1 + -- 13  +   2*       7+    ");
  ATree T=NULL;
  if (t) {
    Imprimir(t);
    printf("%i",evaluar_expresion(t));
  }
  T=insertar_alias(t,T,"ahola");
  T=insertar_alias(NULL,T,"hola");
  T=insertar_alias(NULL,T,"caca de vaca");
  printf("\n");
  Imprimir_alias(T,"ahola");
  printf("\n");
  Imprimir_alias(T,"hola");
  interpretar(T,tabla);
  
  liberar_tabla(tabla);
  
  liberar_alias(T);


}
