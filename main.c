#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graph.h"
#include "list.h"

int main() {
	
	srand(time(NULL));
	
	printf("Algorytmy grafowe\n\n");
	
	int number_of_vertices = 1000;
	printf("Graf ma %d wierzchołków\n", number_of_vertices);

		
	int **adjacency_matrix = (int **) malloc(number_of_vertices * sizeof(int *));
	for (int i = 0; i<number_of_vertices;i++) {
		adjacency_matrix[i] = (int *) malloc(number_of_vertices * sizeof(int));
	}

	int **adjacency_matrix_mirror = (int **) malloc(number_of_vertices * sizeof(int *));
	for (int i = 0; i<number_of_vertices;i++) {
		adjacency_matrix_mirror[i] = (int *) malloc(number_of_vertices * sizeof(int));
	}


	int connected = 0;
	while(!connected) {

		time_t start = clock();
		fill_adjacency_matrix_dfg(adjacency_matrix, number_of_vertices, 0.5);
		mirror_adjacency_matrix(adjacency_matrix, number_of_vertices, adjacency_matrix_mirror);
		time_t stop = clock();
		printf("Pomiar czasu: %.2f\n", (float) (stop - start)/CLOCKS_PER_SEC);
		
		printf("Przeszukiwanie DFS...\n");
		
		start = clock();
		int *vertex_array = (int *) malloc(sizeof(int) * number_of_vertices);
		int vertex_count = 0;
		
		for(int i = 0; i<number_of_vertices; i++) 
			vertex_array[i] = 0;
		dfs_count(adjacency_matrix_mirror, number_of_vertices, &vertex_count, vertex_array, 0);
		printf("\n");
		/*for(int i = 0; i<number_of_vertices; i++) 
			vertex_array[i] = 0;
		vertex_count = 0;
		dfs_count(adjacency_matrix, number_of_vertices, &vertex_count, vertex_array, 0);
		*/
		if(vertex_count == number_of_vertices) {
			printf("Graf jest spójny\n");
			connected = 1;
		}
		else {
			printf("Graf niespójny, ponawiam generację\n");
			free(vertex_array);
		}
		stop = clock();
		printf("Pomiar czasu: %.2f\n", (float) (stop - start)/CLOCKS_PER_SEC);
	}


	list **adjacency_list_array = (list **) malloc(number_of_vertices* sizeof(list*));
	adjacency_list_from_matrix(adjacency_matrix, number_of_vertices, adjacency_list_array);


	int **edge_list = (int **) malloc(number_of_vertices * sizeof(int *));
	for (int i = 0; i<number_of_vertices;i++) {
		edge_list[i] = (int *) malloc(2 * sizeof(int));
	}
	edge_list_from_adjacency_list(adjacency_list_array, 0.5, number_of_vertices, edge_list);


	return 0;
}

