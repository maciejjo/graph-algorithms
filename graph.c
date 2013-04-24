#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void dfs_traversal_matrix(int **adjacency_matrix, int matrix_size, int *vertex_count,  int *vertex_array, int vertex) {
	//Dodawanie do listy odwiedzonych i zwiększenie licznika odwiedzonych
	printf("%d ", vertex);
	vertex_array[*vertex_count] = vertex;
	(*vertex_count)++;
	
	//Szukanie dzieci danego wierzchołka
	for(int i = 0; i < matrix_size; i++) {
		//Jeśli dane dziecko istnieje
		if(adjacency_matrix[vertex][i]) {
			//Wyszukaj je na liście odwiedzonych
			int found = 0;
			for(int j = 0; j < *vertex_count; j++) {
				//Jeśli znaleziono przerwij pętlę
				if(i == vertex_array[j]) {
					found = 1;
					break;
				}
			}
			//Jeśli nie znaleziono na liście odwiedzonych odwiedź wierzchołek
			if(!found) {
				dfs_traversal_matrix(adjacency_matrix, matrix_size, vertex_count, vertex_array, i);
			}
		}
	}
}


void dfs_traversal_list(list **adjacency_list_array, int matrix_size, int *vertex_count,  int *vertex_array, int vertex) {
	//Dodawanie do listy odwiedzonych i zwiększenie licznika odwiedzonych
	printf("%d ", vertex);
	vertex_array[*vertex_count] = vertex;
	(*vertex_count)++;
	
	list *pointer = adjacency_list_array[vertex];
	while(pointer != NULL) {
		int found = 0;
		for(int j = 0; j < *vertex_count; j++) {
			//Jeśli znaleziono przerwij pętlę
			if(pointer->data == vertex_array[j]) {
				found = 1;
				break;
			}
		}
		if(!found) {
			dfs_traversal_list(adjacency_list_array, matrix_size, vertex_count, vertex_array, pointer->data);
		}
		pointer = pointer->next;
	}
}

void dfs_traversal_edge_list(int **edge_list, int edge_count, int *vertex_count,  int *vertex_array, int edge) {
	//Dodawanie do listy odwiedzonych i zwiększenie licznika odwiedzonych
//	printf("%d ", edge);
	printf("Dodaje %d i %d\n", edge_list[edge][0], edge_list[edge][1]);

	vertex_array[*vertex_count] = edge_list[edge][0];
	vertex_array[*vertex_count] = edge_list[edge][1];
	(*vertex_count) += 2;	
	
	for(int i = 0; i< edge_count; i++) {
		int found = 0;
		for(int j = 0; j < *vertex_count; j++) {
			//Jeśli znaleziono przerwij pętlę
			if(edge_list[i][0] == vertex_array[j]) {
				found = 1;
				break;
			}
		}
		if(!found) {
			dfs_traversal_edge_list(edge_list, edge_count, vertex_count, vertex_array, edge_list[i][0]);
		}
		found = 0;
		for(int j = 0; j < *vertex_count; j++) {
			//Jeśli znaleziono przerwij pętlę
			if(edge_list[i][1] == vertex_array[j]) {
				found = 1;
				break;
			}
		}
		if(!found) {
			dfs_traversal_edge_list(edge_list, edge_count, vertex_count, vertex_array, edge_list[i][0]);
		}
	}
}


void mirror_adjacency_matrix(int **input_matrix, int matrix_size, int **output_matrix) {
	for(int i = 0; i<matrix_size; i++) {
		for(int j = 0; j<matrix_size; j++) {
			if(input_matrix[i][j])
			{
				output_matrix[i][j] = 1;
				output_matrix[j][i] = 1;
			}
		}
	}
}


void fill_adjacency_matrix_dfg(int **adjacency_matrix, int matrix_size, float density) {

	// Wyzerowanie macierzy
	for(int i = 0; i<matrix_size; i++) {
		for(int j = 0; j<matrix_size; j++) {
			adjacency_matrix[i][j] = 0;
		}
	}
	
	//Obliczenie ilości łuków w zależności od zagęszczenia
	int number_of_arcs = (int) ((matrix_size*(matrix_size-1)) / 2) * density;

	while(number_of_arcs) {
		//Losowanie współrzędnych w macierzy
		int x = rand() % matrix_size;
		int y = rand() % matrix_size;
		//Jeśli są różne (nie są na przekątnej)
		if(x != y)
		{	
			if(x>y) {
				if(adjacency_matrix[y][x] == 0) {
					adjacency_matrix[y][x] = 1;
					number_of_arcs--;
				}
			}
			else {
				if(adjacency_matrix[x][y] == 0) {
					adjacency_matrix[x][y] = 1;
					number_of_arcs--;
				}
			}
		}
	}
}

void adjacency_list_from_matrix(int **adjacency_matrix, int matrix_size, list **adjacency_list_array) {

	for(int i = 0; i < matrix_size; i++) {
		for(int j = 0; j< matrix_size; j++) {
			if(adjacency_matrix[i][j]) {
				add_to_list(&(adjacency_list_array[i]), j);
			}
		}
//		print_list(adjacency_list_array[i]);
	}
}


void edge_list_from_adjacency_list(list **adjacency_list_array, float density, int matrix_size, int**edge_list) {
		
	for(int i = 0; i < matrix_size; i++) {
		list *pointer = adjacency_list_array[i];
		while(pointer != NULL) {
			edge_list[i][0] = i;
			edge_list[i][1] = pointer->data;
//			printf("%d %d\n", i, pointer->data);
			pointer = pointer->next;
		}
	}
}


