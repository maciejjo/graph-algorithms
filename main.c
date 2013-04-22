#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graph.h"


int main() {
	
	srand(time(NULL));
	
	printf("Algorytmy grafowe\n");
	
	int number_of_vertices = 100;
	printf("Graf ma %d wierzchołków\n", number_of_vertices);

		
	int **adjacency_matrix = (int **) malloc(number_of_vertices * sizeof(int *));
	for (int i = 0; i<number_of_vertices;i++) {
		adjacency_matrix[i] = (int *) malloc(number_of_vertices * sizeof(int));
	}

	int connected = 0;
	while(!connected) {

		time_t start = clock();
		fill_adjacency_matrix_dfg(adjacency_matrix, number_of_vertices, 0.5);
		time_t stop = clock();
		printf("Pomiar czasu: %.2f\n", (float) (stop - start)/CLOCKS_PER_SEC);
		
		printf("Przeszukiwanie DFS...\n");
			int *vertex_array = (int *) malloc(sizeof(int) * number_of_vertices);
			int vertex_count = 0;
			dfs_count(adjacency_matrix, number_of_vertices, &vertex_count, vertex_array, 0);
			if(vertex_count == number_of_vertices) {
				printf("Graf jest spójny\n");
				connected = 1;
			}
			else
				printf("Graf niespójny, ponawiam generację\n");
			free(vertex_array);
	}

	return 0;
}

