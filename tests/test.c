#include "../src/operadores.h"
#include "../src/arbolExpresiones.h"
#include <string.h>
#include <assert.h>

int main() {
    {
    printf("TEST FUNCIONES operador.c");
    {
        printf("TESTEANDO cargar_operador...\n");
        TablaOps t = NULL, t2 = NULL;
        cargar_operador(&t, "+", 2, suma);
        assert(!strcmp(t->simbolo, "+"));
        assert(t->casilla.aridad == 2);
        assert(t->casilla.eval == suma);
        assert(!t->sig);
        cargar_operador(&t, "--", 1, opuesto);
        assert (!strcmp(t->simbolo, "--"));
        assert (t->casilla.aridad == 1);
        assert (t->casilla.eval == opuesto);
        assert (t->sig->casilla.eval == suma);
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
            printf("FIN DEL TESTEO push\n");
        }
        liberar_tabla(tabla);
    }
    return 0;
}
