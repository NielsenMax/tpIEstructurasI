#include "interprete.h"
#include "alias.h"
#include <ctype.h>
#include <string.h>

char *leer() {
  char *line = NULL, *tmp = NULL;
  size_t size = 0, index = 0;
  int ch = EOF;

  while (ch) {
    ch = getchar();


    if (ch == EOF || ch == '\n')
      ch = 0;


    if (size <= index) {
      size += 15;
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

void minusculas(char *palabra) {
  for (; *palabra; ++palabra)
    *palabra = tolower(*palabra);


}



int opciones(char *input, int *fin) {
  int i, t = 0, igual = 0;
  char temp[strlen(input)];
  temp[0] = '\0';
  for (i = 0; input[i]; i++) {
    if (temp[0] && input[i] == ' ') {

      if (!strcmp(temp, "imprimir")) {

        *fin = i;
        return 1;
      } else if (!strcmp(temp, "evaluar")) {
        *fin = i;
        return 2;
      } else if (igual && !strcmp(temp, "cargar")) {
        *fin = i;
        return 0;
      }
    }
    if (input[i] != ' ' && input[i] != '=') {
      temp[t] = input[i];
      t++;
      temp[t] = '\0';
    } else if (input[i] == '=') {
      temp[0] = '\0';
      t = 0;
      igual = 1;
    }

  }

  return 3;
}

void interpretar_IoE(char *input, int fin, ATree T, int ioe) {
  int i, t = 0, espacio = 0;
  char temp[strlen(input)];
  for (i = fin; input[i]; i++) {
    if (espacio) {
      temp[t] = input[i];
      t++;
    } else {
      if (input[i + 1] != ' ') {
        espacio = 1;
      }
    }

  }
  temp[t] = '\0';
  if (ioe == 1) {
    imprimir_alias(T, temp);
    printf("\n");
  } else {
    Evaluar_alias(T, temp);
    printf("\n");
  }


}

void normalizar_expresion(char *string) {
    // space is 1 when a space character is found and
    // 0 when any non-space character is found
    int space = 0;

    // `k` points to the next free position
    int k = 0;

    // iterate through the characters of the string
    for (int i = 0; string[i]; i++)
    {
        // handle leading spaces in the string
        while (k == 0 && string[i] && string[i] == ' ') {
            i++;
        }

        // if the current character is a space
        if (string[i] == ' ')
        {
            // if the flag was 0 earlier, i.e., the first occurrence of a
            // space after a word
            if (!space)
            {
                // copy current char (whitespace) at the next free index
                // and set the flag
                string[k++] = string[i];
                space = 1;
            }
        }
        // if the current character is a punctuation mark
        /**else if (ispunct(string[i]))
        {
            // if the last assigned character was a space, overwrite it
            // with the current character
            if (k > 0 && string[k-1] == ' ') {
                string[k-1] = string[i];
            }
            else {
                // copy the current character at the next free index
                string[k++] = string[i];
            }
            space = 0;
            }**/
        else {
            // copy the current character at the next free index
            string[k++] = string[i];
            space = 0;
        }
    }

    if (string[k - 1] == ' ')
        string[--k] = '\0';
    else
    string[k] = '\0';
}


ATree interpretar_alias(char *input, ATree T, TablaOps tabla, int fin) {

  int i, ta = 0, te = 0, espacio = 0, valid = 1, flag = 0;
  int len = strlen(input);
  char tempa[len], tempe[len];


  if (input[0] != ' ')
    espacio = 1;
  tempa[0] = '\0';
  for (i = 0; input[i] != '=' && !isdigit(tempa[0]); i++) {
    if (input[i] != ' ') {
      espacio = 1;
    }
    if (espacio) {
      tempa[ta] = input[i];
      ta++;
    }
  }
  if (isdigit(tempa[0])) {
    valid = 0;
  }
  if (tempa[ta - 1] == ' ') {
    tempa[ta - 1] = '\0';
  } else {
    tempa[ta] = '\0';
  }

  for (i = fin; input[i] && valid; i++) {
    if (!isalpha(input[i])) {
      if (isdigit(input[i])) {
        flag = 1;
      }
      tempe[te] = input[i];
      te++;
    } else {

      valid = 0;
    }


  }

  tempe[te] = '\0';
  if (valid && flag) {
      //printf("%s,%s", tempa, tempe);
    ETree t = NULL;
    liberar_expresion(t);
    normalizar_expresion(tempe);
   t= cargar_expresion(tabla, tempe);
    if (t){

        //   ATree temp = T;
        T = insertar_alias(t, T, tempa);
        //    liberar_alias(temp);
        //free(temp);
    }
  } else {
    printf("la expresion o el alias que se quiere cargar es invalida");
  }

  return T;


}

void interpretar(ATree T, TablaOps tabla) {
  printf("ingrese un comando: \n:");
  char *input = leer();
  minusculas(input);
  while (strcmp(input, "salir")) {
    printf("\n");
    int a, *fin = &a;
    int menu = opciones(input, fin);
    //printf("OPCION: %i\n", menu);
    if (menu) {
      if (menu == 1) {

        interpretar_IoE(input, a, T, menu);

      } else if (menu == 2) {
        interpretar_IoE(input, a, T, menu);
      } else {
        printf("el ingreso es invalido");
      }

    } else {
//        ATree temp = T;
      T = interpretar_alias(input, T, tabla, a);
      //    liberar_alias(temp);

    }
    free(input);
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
        ("Immprimir ALIAS : Imprime la expresion aritmetica asociada a dicho alias.\n");
    printf
        ("Evaluar ALIAS : Imprime en pantalla el resultado de calcular la expresion aritmetica asociada al alias\n");
    printf("Para salir del programa debe escribir 'salir'\n ");
    printf
        ("\nNOTAS:\n-- No se distinguen mayusculas de minusculas\n--Los espacios antes del primer caracter son ignorados.\n--Se considera ALIAS a todo lo escrito antes del igual");
    printf
        (" pero se puede separar el alias de el '=' con un solo espacio y este va a ser ignorado. Para hacer mas clara la input\n");
    printf
        ("--Los alias pueden ser varias palabras o contener espacios al final pero el espacio inmediatamente anterior al igual es ignorado\n");
    printf
        ("--Todo lo escrito despues de la palabra clave 'cargar' es considerado expresion aritmetica\n");

    printf("\nPRESIONE ENTER PARA CONTINUAR\n");
    c = getchar();
  }
  system("clear");

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
  // ETree t = NULL;
  // liberar_expresion(t);
  //cargar_expresion(&t, tabla, "    5   1 + -- 13  +   2*       7+    ");
  ATree T = NULL;
  //if (t) {
  //  Imprimir(t);
  //  printf("%i",evaluar_expresion(t));
  //}
  // T=insertar_alias(t,T,"ahola");

  // printf("\n");
  // Imprimir_alias(T,"ahola");
  //printf("\n");
  //Imprimir_alias(T,"hola");
  presentacion();
  interpretar(T, tabla);


  liberar_tabla(tabla);

  //liberar_alias(T);


}
