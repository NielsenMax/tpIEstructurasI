CFLAGS = -Wall -Wextra -Werror -std=c99 -g
CC= gcc
VPATH = src INCLUDE 

main: main.o operadores.o arbolExpresiones.o  alias.o interprete.o
	$(CC) $(CFLAGS) -o main main.o operadores.o arbolExpresiones.o alias.o interprete.o -lm

valgrindTest: test
	valgrind --tool=memcheck --leak-check=full ./src/test

valgrind : main
	valgrind --tool=memcheck --leak-check=full ./src/main

test:  src/t.out src/operadores.c src/arbolExpresiones.c src/alias.c src/interprete.c  tests/test.c
	$(CC) $(CFLAGS) -o test t.out src/operadores.c src/arbolExpresiones.c src/alias.c src/interprete.c tests/test.c -lm


t.out:	tests/test.c src/arbolExpresiones.c src/arbolExpresiones.h src/operadores.c src/operadores.h src/alias.c src/alias.h src/interprete.c src/interprete.h 
	$(CC) $(CFLAGS) tests/test.c src/arbolExpresiones.c src/operadores.c src/alias.c src/interprete.c -lm


main.out: src/main.c interprete.o alias.o arbolExpresiones.o operadores.o
	$(CC) $(CFLAGS) src/main.c -lm

interprete.out: src/interprete.c src/interprete.h src/alias.h src/arbolExpresiones.h src/operadores.h
	$(CC) $(CFLAGS) src/interprete.c -lm

alias.out: src/alias.c src/alias.h src/arbolExpresiones.h src/operadores.h
	$(CC) $(CFLAGS) src/alias.c -lm

arbolExpresiones.out: src/arbolExpresiones.c src/arbolExpresiones.h src/operadores.h
	$(CC) $(CFLAGS) src/arbolExpresiones.c -lm
	
operadores.out: src/operadores.c src/operadores.h
	$(CC) $(CFLAGS) src/operadores.c -lm


