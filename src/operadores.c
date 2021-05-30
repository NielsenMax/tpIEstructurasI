#include "operadores.h"
#include <stdio.h>
#include <stdlib.h>

int suma(int *args) {
  return args[0] + args[1];
}

int main() {
    int A[2]={3, 4};
    printf("%i", suma(A));
  return 0;
}
