CC = gcc
CFLAGS = -Wall -std=gnu99 -o2 -pedantic

graph-algorithms: main.c list.c
	$(CC) $(CFLAGS) main.c list.c -o graph-algorithms
