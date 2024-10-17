CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: otimizar

otimizar: otimizar.o otimizar_funcoes.o
	gcc $(CFLAGS) otimizar.o otimizar_funcoes.o -o otimizar $(LDFLAGS)

otimizar.o: otimizar.c otimizar_funcoes.h
	gcc $(CFLAGS) -c otimizar.c $(LDFLAGS)

otimizar_funcoes.o: otimizar_funcoes.c otimizar_funcoes.h
	gcc $(CFLAGS) -c otimizar_funcoes.c $(LDFLAGS)

clean:
	rm -f otimizar
