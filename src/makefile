#esto es el makefile
CFLAGS = -Wall -Wextra -Werror -std=c99 -g
CC= gcc
main: a.out operadores.c arbolExpresiones.c alias.c interprete.c
	$(CC) $(CFLAGS) -o main a.out operadores.c arbolExpresiones.c alias.c interprete.c -lm

a.out: arbolExpresiones.c arbolExpresiones.h operadores.c operadores.h alias.c alias.h interprete.c interprete.h
	$(CC) $(CFLAGS) arbolExpresiones.c operadores.c alias.c interprete.c -lm
clean: 
	rm *.out main