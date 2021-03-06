#include "interprete.h"


int main() {
  TablaOps tabla = NULL;
  cargar_operador(&tabla, "+", 2, suma);
  cargar_operador(&tabla, "-", 2, resta);
  cargar_operador(&tabla, "--", 1, opuesto);
  cargar_operador(&tabla, "*", 2, producto);
  cargar_operador(&tabla, "/", 2, division);
  cargar_operador(&tabla, "%", 2, modulo);
  cargar_operador(&tabla, "^", 2, potencia);
  ATree T = NULL;
  presentacion();
  interpretar(T, tabla);
  liberar_tabla(tabla);
}
