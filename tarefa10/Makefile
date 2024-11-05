CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: corretor

corretor: corretor.o corretor_funcoes.o
	gcc $(CFLAGS) corretor.o corretor_funcoes.o -o corretor $(LDFLAGS)

corretor.o: corretor.c corretor_funcoes.h
	gcc $(CFLAGS) -c corretor.c $(LDFLAGS)

corretor_funcoes.o: corretor_funcoes.c corretor_funcoes.h
	gcc $(CFLAGS) -c corretor_funcoes.c $(LDFLAGS)

clean:
	rm -f corretor
