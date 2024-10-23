CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: cache

cache: cache.o cache_prio-queue.o cache_array.o
	gcc $(CFLAGS) cache.c cache_prio-queue.o cache_array.o -o cache $(LDFLAGS)

cache.o: cache.c cache_prio-queue.h
	gcc $(CFLAGS) -c cache.c $(LDFLAGS)

cache_prio-queue.o: cache_prio-queue.c cache_prio-queue.h
	gcc $(CFLAGS) -c cache_prio-queue.c $(LDFLAGS)

clean:
	rm -f cache
