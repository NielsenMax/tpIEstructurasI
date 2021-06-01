#include "../src/operadores.h"
#include <string.h>
#include <assert.h>

int main() {
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
    return 0;
}
