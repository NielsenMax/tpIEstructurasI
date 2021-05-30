#ifndef __OPERADORES_H__
#define __OPERADORES_H__

typedef int (*FuncionEvaluacion)(int *args);

typedef struct _ONodo {
    char *simbolo;
    int aridad;
    FuncionEvaluacion eval;
    struct _ONodo *sig;
} ONodo;

typedef ONodo *TablaOps;

void cargar_operador(TablaOps *tabla, char *simbolo, int aridad, FuncionEvaluacion eval);

int suma(int *args);
int resta(int *args);
int opuesto(int *args);
int division(int *args);
int modulo(int *args);
int potencia(int *args);

#endif /** __OPERADORES_H__ **/
