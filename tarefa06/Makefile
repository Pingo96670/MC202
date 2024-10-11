CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cobra

cobra: cobra.o cobra_funcoes.o
	gcc $(CFLAGS) cobra.o cobra_funcoes.o -o cobra $(LDFLAGS)

cobra.o: cobra.c cobra_funcoes.h
	gcc $(CFLAGS) -c cobra.c $(LDFLAGS)

cobra_funcoes.o: cobra_funcoes.c cobra_funcoes.h
	gcc $(CFLAGS) -c cobra_funcoes.c $(LDFLAGS)

clean:
	rm -f cobra
