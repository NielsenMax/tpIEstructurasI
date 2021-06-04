#esto es el makefile
CFLAGS = -Wall -Wextra -Werror -std=c99 -g
CC= gcc


test:  t.out operadores.c arbolExpresiones.c alias.c interprete.c  ../tests/test.c
	$(CC) $(CFLAGS) -o test t.out operadores.c arbolExpresiones.c alias.c interprete.c ../tests/test.c -lm


t.out:	../tests/test.c arbolExpresiones.c arbolExpresiones.h operadores.c operadores.h alias.c alias.h interprete.c interprete.h 
	$(CC) $(CFLAGS) ../tests/test.c arbolExpresiones.c operadores.c alias.c interprete.c -lm


main: main.o operadores.o arbolExpresiones.o  alias.o interprete.o
	$(CC) $(CFLAGS) -o main main.o operadores.o arbolExpresiones.o alias.o interprete.o -lm

main.out: main.c interprete.o alias.o arbolExpresiones.o operadores.o
	$(CC) $(CFLAGS) main.c -lm

interprete.out: interprete.c interprete.h alias.h arbolExpresiones.h operadores.h
	$(CC) $(CFLAGS) interprete.c -lm

alias.out: alias.c alias.h arbolExpresiones.h operadores.h
	$(CC) $(CFLAGS) alias.c -lm

arbolExpresiones.out: arbolExpresiones.c arbolExpresiones.h operadores.h
	$(CC) $(CFLAGS) arbolExpresiones.c -lm
	
operadores.out: operadores.c operadores.h
	$(CC) $(CFLAGS) operadores.c -lm


clean: 
	rm *.out main