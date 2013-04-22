CC = gcc
CFLAGS = -Wall -std=gnu99 -o2 -pedantic

graph-algorithms: main.c graph.c
	$(CC) $(CFLAGS) main.c graph.c list.c -o graph-algorithms
