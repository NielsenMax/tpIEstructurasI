#define _DEFAULT_SOURCE
#include "../src/operadores.h"
#include "../src/arbolExpresiones.h"
#include "../src/alias.h"
#include "../src/interprete.h"
#include <string.h>
#include <assert.h>

int main() {
  {
    printf("TEST FUNCIONES operador.c");
    {
      printf("TESTEANDO cargar_operador...\n");
      TablaOps t = NULL;
      cargar_operador(&t, "+", 2, suma);
      assert(!strcmp(t->simbolo, "+"));
      assert(t->casilla.aridad == 2);
      assert(t->casilla.eval == suma);
      assert(!t->sig);
      cargar_operador(&t, "--", 1, opuesto);
      assert(!strcmp(t->simbolo, "--"));
      assert(t->casilla.aridad == 1);
      assert(t->casilla.eval == opuesto);
      assert(t->sig->casilla.eval == suma);
      liberar_tabla(t);
      printf("FIN DEL TESTEO cargar_operacion\n");
    }
    {
      printf("TESTEANDO buscar_simbolo...\n");
      TablaOps tabla = NULL;
      cargar_operador(&tabla, "+", 2, suma);
      cargar_operador(&tabla, "-", 2, resta);
      cargar_operador(&tabla, "--", 1, opuesto);
      cargar_operador(&tabla, "*", 2, producto);
      cargar_operador(&tabla, "/", 2, division);
      cargar_operador(&tabla, "%", 2, modulo);
      cargar_operador(&tabla, "^", 2, potencia);
      assert(buscar_simbolo(tabla, "+").aridad == 2);
      assert(buscar_simbolo(tabla, "+").eval == suma);
      assert(buscar_simbolo(tabla, "--").aridad == 1);
      assert(buscar_simbolo(tabla, "!").aridad == -1);
      liberar_tabla(tabla);
      printf("FIN DEL TESTEO buscar_simbolo\n");
    }
    printf("FIN TEST FUNCIONES operador.c\n");
  }
  {
    printf("TEST FUNCIONES arbolExpresiones.c\n");
    TablaOps tabla = NULL;
    cargar_operador(&tabla, "+", 2, suma);
    cargar_operador(&tabla, "-", 2, resta);
    cargar_operador(&tabla, "--", 1, opuesto);
    cargar_operador(&tabla, "*", 2, producto);
    cargar_operador(&tabla, "/", 2, division);
    cargar_operador(&tabla, "%", 2, modulo);
    cargar_operador(&tabla, "^", 2, potencia);
    {
      printf("TESTEANDO nuevo_ENodo...\n");
      ETree t = NULL;
      OCasilla ct;
      ct.aridad = -1;
      ct.eval = NULL;
      t = nuevo_ENodo(NULL, ct, 2);
      assert(!t->simbolo);
      assert(t->operador.aridad == -1);
      assert(!t->operador.eval);
      assert(t->tipo == 0);
      assert(t->valor == 2);
      assert(!t->Izq);
      assert(!t->Der);
      liberar_expresion(t);

      t = NULL;
      ct.aridad = 2;
      ct.eval = suma;
      t = nuevo_ENodo("+", ct, 0);
      assert(!strcmp(t->simbolo, "+"));
      assert(t->operador.aridad == 2);
      assert(t->operador.eval == suma);
      assert(t->tipo == 1);
      assert(t->valor == 0);
      assert(!t->Izq);
      assert(!t->Der);
      liberar_expresion(t);
      printf("FIN DEL TESTEO nuevo_ENodo\n");
    }
    {
      printf("TESTEANDO push...\n");
      Stack stack = NULL;
      ETree t = NULL;
      OCasilla ct;
      ct.aridad = -1;
      ct.eval = NULL;
      t = nuevo_ENodo(NULL, ct, 2);
      push(&stack, t);
      assert(stack->dato == t);
      assert(!stack->sig);

      ct.aridad = -1;
      ct.eval = NULL;
      t = nuevo_ENodo(NULL, ct, 3);
      push(&stack, t);
      assert(stack->dato == t);
      assert(stack->sig->dato->valor == 2);

      ct.aridad = 2;
      ct.eval = suma;
      t = nuevo_ENodo("+", ct, 0);
      push(&stack, t);
      assert(stack->dato == t);
      assert(stack->sig->dato->valor == 3);
      printf("FIN DEL TESTEO push\n");

      printf("TESTEANDO pop...\n");
      t = pop(&stack);
      assert(!strcmp(t->simbolo, "+"));
      liberar_expresion(t);

      t = pop(&stack);
      assert(t->valor == 3);
      liberar_expresion(t);

      t = pop(&stack);
      assert(t->valor == 2);
      liberar_expresion(t);

      assert(!stack);
      printf("FIN DEL TESTEO pop\n");
    }
    {
      printf("TESTEANDO es_num...\n");
      assert(es_num("123"));
      assert(!es_num("1a3"));
      assert(es_num("420"));
      assert(!es_num("mod"));
      printf("FIN DEL TESTEO es_num\n");
    }
    {
      printf("TESTEANDO cargar_expresion...\n");
      ETree t;
      char *aux = strdup("1 2 +");
      t = cargar_expresion(tabla, aux);
      assert(!strcmp(t->simbolo, "+"));
      assert(t->Izq->valor == 1);
      assert(t->Der->valor == 2);
      liberar_expresion(t);
      free(aux);

      aux = strdup("1 2 3 +");
      t = cargar_expresion(tabla, aux);
      assert(!t);
      free(aux);

      aux = strdup("1 $ +");
      t = cargar_expresion(tabla, aux);
      assert(!t);
      free(aux);
      printf("FIN DEL TESTEO cargar_expresion\n");
    }
    {
      printf("TESTEANDO evaluar_expresion...\n");
      ETree t;
      char *aux = strdup("1 -- 3 *");
      t = cargar_expresion(tabla, aux);
      assert(evaluar_expresion(t) == (-3));
      liberar_expresion(t);
      free(aux);

      aux = strdup("5 -- 13 + 2 * 7 +");
      t = cargar_expresion(tabla, aux);
      assert(evaluar_expresion(t) == 23);
      liberar_expresion(t);
      free(aux);

      aux = strdup("1 $ +");
      t = cargar_expresion(tabla, aux);
      assert(evaluar_expresion(t) == 0);
      free(aux);
      printf("FIN DEL TESTEO evaluar_expresion\n");
    }
    liberar_tabla(tabla);
    printf("FIN TEST FUNCIONES arbolExpresiones.c\n");
  }
  {
    printf("TEST FUNCIONES alias.c\n");
    TablaOps tabla = NULL;
    cargar_operador(&tabla, "+", 2, suma);
    cargar_operador(&tabla, "-", 2, resta);
    cargar_operador(&tabla, "--", 1, opuesto);
    cargar_operador(&tabla, "*", 2, producto);
    cargar_operador(&tabla, "/", 2, division);
    cargar_operador(&tabla, "%", 2, modulo);
    cargar_operador(&tabla, "^", 2, potencia);
    {
      printf("TESTEANDO insertar_alias...\n");
      ETree t;
      char *aux = strdup("1 -- 3 *");
      ATree a = NULL;
      t = cargar_expresion(tabla, aux);
      a = insertar_alias(t, a, "b");
      free(aux);
      aux = strdup("5 -- 13 + 2 * 7 +");
      t = cargar_expresion(tabla, aux);
      a = insertar_alias(t, a, "a");
      free(aux);
      aux = strdup("3 2 * 7 +");
      t = cargar_expresion(tabla, aux);
      a = insertar_alias(t, a, "c");
      free(aux);
      assert(!strcmp(a->alias, "b"));
      assert(!strcmp(a->Izq->alias, "a"));
      assert(!strcmp(a->Der->alias, "c"));
      assert(!a->Izq->Izq);
      assert(!a->Der->Der);
      printf("FIN DEL TESTEO insertar_alias\n");
      printf("TESTEANDO buscar_alias...\n");
      assert(!strcmp(buscar_alias(a, "a")->simbolo, "+"));
      assert(!strcmp(buscar_alias(a, "b")->simbolo, "*"));
      assert(!strcmp(buscar_alias(a, "c")->simbolo, "+"));
      assert(!buscar_alias(a, "d"));
      liberar_alias(a);
      printf("FIN DEL TESTEO buscar_alias\n");
    }
    liberar_tabla(tabla);
    printf("FIN TEST FUNCIONES alias.c\n");
  }
  {
    printf("TEST FUNCIONES interprete.c\n");
    {
      printf("TESTEANDO minusculas...\n");
      char h1[] = "HoLa MuNdO";
      minusculas(h1);
      assert(!strcmp(h1, "hola mundo"));
      char h2[] = "alejo";
      minusculas(h2);
      assert(!strcmp(h2, "alejo"));
      char h3[] = "MAXI";
      minusculas(h3);
      assert(!strcmp(h3, "maxi"));
      printf("FIN DEL TESTEO minusculas\n");
    }
    {
      printf("TESTEANDO opciones...\n");
      int fin;
      assert(opciones("imprimir a", &fin) == 1);
      assert(fin == 8);
      assert(opciones("evaluar a", &fin) == 2);
      assert(fin == 7);
      assert(opciones("a = cargar 1 2 +", &fin) == 0);
      assert(fin == 10);
      assert(opciones("hola mundo", &fin) == 3);
      printf("FIN DEL TESTEO opciones\n");
    }
    {
      printf("TESTEANDO normalizar_expresion...\n");
      char h1[] = "  hola   mundo   ";
      normalizar_expresion(h1);
      assert(!strcmp(h1, "hola mundo"));
      char h2[] = "     1    2     +    ";
      normalizar_expresion(h2);
      assert(!strcmp(h2, "1 2 +"));
      char h3[] = "1 2 3 +";
      normalizar_expresion(h3);
      assert(!strcmp(h3, "1 2 3 +"));
      printf("FIN DEL TESTEO normalizar_expresion\n");
    }
    {
      printf("TESTEANDO interpretar_alias...\n");
      TablaOps tabla = NULL;
      cargar_operador(&tabla, "+", 2, suma);
      cargar_operador(&tabla, "-", 2, resta);
      cargar_operador(&tabla, "--", 1, opuesto);
      cargar_operador(&tabla, "*", 2, producto);
      cargar_operador(&tabla, "/", 2, division);
      cargar_operador(&tabla, "%", 2, modulo);
      cargar_operador(&tabla, "^", 2, potencia);
      char *aux;
      ATree a = NULL;
      aux = strdup("b = cargar 1 -- 3 *");
      a = interpretar_alias(aux, a, tabla, 10);
      free(aux);
      assert(!strcmp(a->alias, "b"));
      aux = strdup("a = cargar 5 -- 13 + 2 * 7 +");
      a = interpretar_alias(aux, a, tabla, 10);
      free(aux);
      assert(!strcmp(a->Izq->alias, "a"));
      aux = strdup("c = cargar 3 2 * 7 +");
      a = interpretar_alias(aux, a, tabla, 10);
      free(aux);
      assert(!strcmp(a->Der->alias, "c"));
      liberar_alias(a);
      liberar_tabla(tabla);
      printf("FIN DEL TESTEO interpretar_alias\n");
    }
    printf("FIN TEST FUNCIONES interprete.c\n");
  }
  return 0;
}
