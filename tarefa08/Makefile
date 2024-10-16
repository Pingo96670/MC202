CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cidades

cidades: cidades.o cidades_funcoes.o
	gcc $(CFLAGS) cidades.o cidades_funcoes.o -o cidades $(LDFLAGS)

cidades.o: cidades.c cidades_funcoes.h
	gcc $(CFLAGS) -c cidades.c $(LDFLAGS)

cidades_funcoes.o: cidades_funcoes.c cidades_funcoes.h
	gcc $(CFLAGS) -c cidades_funcoes.c $(LDFLAGS)

clean:
	rm -f cidades
