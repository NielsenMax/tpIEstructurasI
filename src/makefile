#esto es el makefile
CFLAGS = -Wall -Wextra -Werror -std=c99 -g
CC= gcc
main: a.out operadores.c
	$(CC) $(CFLAGS) -o main a.out operadores.c

a.out: operadores.c operadores.h
	$(CC) $(CFLAGS) operadores.c
clean: 
	rm *.out main