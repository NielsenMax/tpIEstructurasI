#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__
#include "alias.h"

char *leer();
int opciones(char *input,int *fin);
void interpretar_IoE(char *input,int fin,ATree T,int ioe);
void interpretar_alias(char *input,ATree T,TablaOps tabla);
void interpretar(ATree T,TablaOps tabla);
#endif // __INTERPRETE_H__