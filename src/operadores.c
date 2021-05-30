#include "operadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int suma(int *args) {
  return args[0] + args[1];
}

int resta(int *args) {
    return args[0] - args[1];
}

int opuesto(int *args) {
    return (-1) * args[0];
}

int division(int *args) {
    return round(args[0] / args[1]);
}

int modulo(int *args) {
    return args[0] % args[1];
}

int potencia(int *args) {
    return pow(args[0], args[1]);
}
