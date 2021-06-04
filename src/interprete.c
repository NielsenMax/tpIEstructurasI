#define _DEFAULT_SOURCE
#include "interprete.h"
#include "alias.h"
#include <ctype.h>
#include <string.h>

char *leer() {
  char *line = NULL, *tmp = NULL;
  size_t size = 0, index = 0;
  int ch = EOF;
  while (ch) {
    ch = getchar();             //Cargamos un caracter por teclado
    if (ch == EOF || ch == '\n')        //Si es un '\n' lo colocamos en 0
      ch = 0;
    if (size <= index) {
      //Si el tamaño que usamos es mas chico que el largo de la input
      size += 15;               //Sumamos al tamaño
      tmp = realloc(line, size);        //Realocamos memoria con el nuevo tamaño
      if (!tmp) {
        //Si tmp es NULL luego de realocar liberamos la memoria
        free(line);
        line = NULL;
        break;
      }
      line = tmp;
    }
    line[index++] = ch;         //Añadimos el caracter
  }
  return line;
}

void minusculas(char *palabra) {
  for (; *palabra; ++palabra)
    *palabra = tolower(*palabra);
}

int opciones(char *input, int *fin) {
  int i, t = 0, igual = 0;
  char temp[strlen(input)];
  temp[0] = '\0';
  for (i = 0; input[i]; i++) {
    //Revisamos que tenemos cargado en temp cuando nos encontramos un espacio
    if (temp[0] && (input[i] == ' ' || isdigit(input[i]))) {
      if (!strcmp(temp, "imprimir") && !igual) {
        //fin nos va a indicar donde termina la palabra clave
        *fin = i;
        return 1;
      } else if (!strcmp(temp, "evaluar") && !igual) {
        *fin = i;
        return 2;
      } else if (igual && !strcmp(temp, "cargar")) {
        *fin = i;
        return 0;
      }
    }
    //Agregamos los caracteres si no son espacios ni iguales
    if (input[i] != ' ' && input[i] != '=') {
      temp[t] = input[i];
      t++;
      temp[t] = '\0';
    } else if (input[i] == '=') {
      //Si encontramos un igual reseteamos temp y marcamos la flag 'igual'
      temp[0] = '\0';
      t = 0;
      igual = 1;
    }
  }
  return 3;
}

void normalizar_expresion(char *string) {
  int space = 0;                //1 si se encuentra un espacio 0 si es cualquier otro caracter
  int k = 0;                    //apunta a la siguiente posicion libre
  for (int i = 0; string[i]; i++) {
//Elimina los espacios al inicio
    while (k == 0 && string[i] && string[i] == ' ')
      i++;
    if (string[i] == ' ') {
      if (!space)               //Venimos de un caracter y encontramos espacio
      {
//Guardamos el espacio y marccamos la flag
        string[k++] = string[i];
        space = 1;
      }
    } else {
//Guardamos el caraccter si no es un espacio y marcamos la flag
      string[k++] = string[i];
      space = 0;
    }
  }
  if (string[k - 1] == ' ')     //Elimina los espacios finales
    string[--k] = '\0';
  else
    string[k] = '\0';
}


void interpretar_IoE(char *input, int posClave, ATree T, int ioe) {
  char *alias;
  //Nos posicionamos despues de la palabra clave del comando
  alias = input + posClave;
  //Normalizamos la expresion y realizamos la impresion o evaluacion
  normalizar_expresion(alias);
  if (ioe == 1) {
    imprimir_alias(T, alias);
    printf("\n");
  } else {
    evaluar_alias(T, alias);
    printf("\n");
  }
}

ATree interpretar_alias(char *input, ATree T, TablaOps tabla, int posClave) {
  int valid = 1;
  char *alias;
  alias = strsep(&input, "=");  //Separamos la input en dos por el primer '='
  posClave = posClave - strlen(alias);
  //Avanza hasta luego de la palabra clave 'cargar'
  input = input + posClave - 1;
  normalizar_expresion(alias);
  normalizar_expresion(input);
  if (isdigit(alias[0]))        //Revisa que el alias no empieze en un numero
    valid = 0;
  else {
    //Revisa que el alias solo contenga caracteres alfanumericos
    for (int i = 1; alias[i]; i++) {
      if (!isalnum(alias[i]))
        valid = 0;
    }
  }
  if (valid) {
    ETree t = NULL;
    liberar_expresion(t);
    t = cargar_expresion(tabla, input);
    if (t) {
      T = insertar_alias(t, T, alias);
      printf("Se cargo la expresion con exito\n");
    } else {
      printf("La expresion o el alias que se quiere cargar es invalida\n");
    }
  } else {
    printf("El alias es invalido\n");
  }
  return T;
}

void interpretar(ATree T, TablaOps tabla) {
  printf("ingrese un comando: \n:");
  printf(">");
  char *input = leer();
  minusculas(input);
  while (strcmp(input, "salir")) {
    printf("\n");
    int posClave, *fin = &posClave;
    int menu = opciones(input, fin);
    if (menu) {
      if (menu == 1 || menu == 2)
        interpretar_IoE(input, posClave, T, menu);
      else
        printf("el ingreso es invalido\n");
    } else {
      T = interpretar_alias(input, T, tabla, posClave);
    }
    free(input);
    printf(">");
    input = leer();
  }
  free(input);
  liberar_alias(T);
}

void presentacion() {
  char c = 'a';
  while (c != '\n') {
    system("clear");
    printf("\nModo de uso del programa:\n");
    printf("\nEl programa contiene tres funciones que son las siguientes:\n");
    printf
        ("ALIAS = EXPR : asocia una expresion aritmetica escrita de manera postfija a el alias deseado.\n");
    printf
        ("Imprimir ALIAS : Imprime la expresion aritmetica asociada a dicho alias.\n");
    printf
        ("Evaluar ALIAS : Imprime en pantalla el resultado de calcular la expresion aritmetica asociada al alias\n");
    printf("Para salir del programa debe escribir 'salir'\n ");
    printf
        ("\nNOTAS:\n-- No se distinguen mayusculas de minusculas\n--Los espacios antes del primer caracter son ignorados.\n--Se considera ALIAS a todo lo escrito antes del igual");
    printf
        ("--Los alias solo pueden contener caracteres alfanumericos y no pueden empezar con un numero\n");
    printf
        ("--Todo lo escrito despues de la palabra clave 'cargar' es considerado expresion aritmetica\n");

    printf("\nPRESIONE ENTER PARA CONTINUAR\n");
    c = getchar();
  }
  system("clear");

}
