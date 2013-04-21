#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list.h"

void bfs_count(int **neighbour_matrix, int *connected, int *vertice_count, int number_of_vertices, int vertice);

int main() {
	time_t start = clock();
	printf("Algorytmy grafowe\n");
	
	int number_of_vertices = 100;

	printf("Graf ma %d wierzchołków\n", number_of_vertices);
	
	int **neighbour_matrix = (int **) malloc(number_of_vertices * sizeof(int *));
	for (int i = 0; i<number_of_vertices;i++) {
		neighbour_matrix[i] = (int *) malloc(number_of_vertices * sizeof(int));
	}

	for(int i = 0; i<number_of_vertices; i++) {
		for(int j = 0; j<number_of_vertices; j++) {
			neighbour_matrix[i][j] = 0;
		}
	}
	int number_of_arcs = (number_of_vertices*(number_of_vertices-1))/4;
	printf("Należy wygenerować %d łuków\n", number_of_arcs);
	srand(time(NULL));
	while(number_of_arcs) {
		int x = rand() % number_of_vertices;
		int y = rand() % number_of_vertices;
		if(x != y)
		{
			if(x>y) {
				int tmp = x;
				x = y;
				y = tmp;
			}
			if(neighbour_matrix[x][y] == 0) {
				neighbour_matrix[x][y] = 1;
				number_of_arcs--;
			}
		}
	}
	time_t stop = clock();
	printf("Pomiar czasu: %.2f\n", (float) (stop - start)/CLOCKS_PER_SEC);
	
	printf("Przeszukiwanie BFS\n");
	int *connected = (int *) malloc(sizeof(int) * number_of_vertices);
	int bfs_counter = 0;
	bfs_count(neighbour_matrix, connected, &bfs_counter, number_of_vertices, 0);

	if(bfs_counter == number_of_vertices) {
		printf("Graf jest spójny\n");
	}

	return 0;
}

void bfs_count(int **neighbour_matrix, int *connected, int *vertice_count, int number_of_vertices, int vertice) {
	
	connected[(*vertice_count)++] = vertice;

	list *list_of_children = NULL;
	for(int i = 0; i < number_of_vertices; i++) {
		if(neighbour_matrix[vertice][i]) {
			add_to_list(&list_of_children, i);
		}
	}
	
	while(list_of_children != NULL)
	{	
		int found = 0;
		for(int i = 0; i < *vertice_count; i++) {
			if(list_of_children->data == connected[i]) {
				found = 1;
				break;
			}
			if(!found) {
				bfs_count(neighbour_matrix, connected, vertice_count, number_of_vertices, list_of_children->data);
			}
		}
		pop_from_list(&list_of_children);
	}	
	print_list(list_of_children);
}
