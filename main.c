#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graph.h"
#include "list.h"

int main() {
	
	int number_of_vertices = 10;
	time_t start, stop;
	
	srand(time(NULL));
	
	printf("Algorytmy grafowe\n\n");
	
	printf("Generowanie macierzy n=%d wierzchołków...\n", number_of_vertices);

		
	//Tworzenie spójnej macierzy
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

		start = clock();
		fill_adjacency_matrix_dfg(adjacency_matrix, number_of_vertices, 0.5);
		mirror_adjacency_matrix(adjacency_matrix, number_of_vertices, adjacency_matrix_mirror);
		stop = clock();
		printf("Pomiar czasu: %.2f\n\n", (float) (stop - start)/CLOCKS_PER_SEC);
		
		printf("Sprawdzanie spójności...\n");
		
		start = clock();
		int *vertex_array = (int *) malloc(sizeof(int) * number_of_vertices);
		int vertex_count = 0;
		for(int i = 0; i<number_of_vertices; i++) 
			vertex_array[i] = 0;
		dfs_traversal_matrix(adjacency_matrix_mirror, number_of_vertices, &vertex_count, vertex_array, 0);
		printf("\n");
		if(vertex_count == number_of_vertices) {
			printf("Graf jest spójny\n");
			connected = 1;
		}
		else {
			printf("Graf niespójny, ponawiam generację\n");
			free(vertex_array);
		}
		stop = clock();
		printf("Pomiar czasu: %.2f\n\n", (float) (stop - start)/CLOCKS_PER_SEC);
	}

	
	//Tworzenie listy następników
	list **adjacency_list_array = (list **) malloc(number_of_vertices* sizeof(list*));
	adjacency_list_from_matrix(adjacency_matrix, number_of_vertices, adjacency_list_array);


	//Tworzenie listy krawędzi
	int **edge_list = (int **) malloc(number_of_vertices * sizeof(int *));
	for (int i = 0; i<number_of_vertices;i++) {
		edge_list[i] = (int *) malloc(2 * sizeof(int));
	}
	edge_list_from_adjacency_list(adjacency_list_array, 0.5, number_of_vertices, edge_list);


	//DFS dla macierzy
	printf("Sortowanie topologiczne macierzy...\n");
	
	int *vertex_array = (int *) malloc(sizeof(int) * number_of_vertices);
	int vertex_count = 0;
	for(int i = 0; i<number_of_vertices; i++) 
		vertex_array[i] = 0;

	start = clock();
	for(int i = 0; i < number_of_vertices; i++) {
		if(!vertex_array[i]) {
			dfs_traversal_matrix(adjacency_matrix, number_of_vertices, &vertex_count, vertex_array, i);
		}
	}
	stop = clock();
	printf("\n");
	printf("Pomiar czasu: %.2f\n\n", (float) (stop - start)/CLOCKS_PER_SEC);
	
	
	//DFS dla listy następników	
	printf("Sortowanie topologiczne listy następników...\n");
	
	vertex_count = 0;
	for(int i = 0; i<number_of_vertices; i++) 
		vertex_array[i] = 0;

	start = clock();
	for(int i = 0; i < number_of_vertices; i++) {
		if(!vertex_array[i]) {
			dfs_traversal_list(adjacency_list_array, number_of_vertices, &vertex_count, vertex_array, i);
		}
	}
	stop = clock();
	printf("\n");
	
/*	printf("Sortowanie topologiczne listy krawędzi...\n");
	
	int number_of_arcs = (int) ((number_of_vertices*(number_of_vertices-1)) / 2) * 0.5;
	vertex_count = 0;
	for(int i = 0; i<number_of_vertices; i++) 
		vertex_array[i] = 0;

	start = clock();
	dfs_traversal_edge_list(edge_list, number_of_arcs, &vertex_count, vertex_array, 0);	
*/

	return 0;
}

