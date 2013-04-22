#include <stdlib.h>

void dfs_count(int **adjacency_matrix, int matrix_size, int *vertex_count,  int *vertex_array, int vertex) {
	
	vertex_array[*vertex_count] = vertex;
	(*vertex_count)++;

	for(int i = 0; i < matrix_size; i++) {
		if(adjacency_matrix[vertex][i]) {
			int found = 0;
			for(int j = 0; j < *vertex_count; j++) {
				if(i == vertex_array[j]) {
					found = 1;
					break;
				}
			}
			if(!found) {
				dfs_count(adjacency_matrix, matrix_size, vertex_count, vertex_array, i);
			}
		}
	}
}

void fill_adjacency_matrix_dfg(int **adjacency_matrix, int matrix_size, float density) {

	for(int i = 0; i<matrix_size; i++) {
		for(int j = 0; j<matrix_size; j++) {
			adjacency_matrix[i][j] = 0;
		}
	}

	int number_of_arcs = (int) ((matrix_size*(matrix_size-1)) / 2) * density;
	//printf("Należy wygenerować %d łuków\n", number_of_arcs);
	while(number_of_arcs) {
		int x = rand() % matrix_size;
		int y = rand() % matrix_size;
		if(x != y)
		{
			if(x>y) {
				int tmp = x;
				x = y;
				y = tmp;
			}
			if(adjacency_matrix[x][y] == 0) {
				adjacency_matrix[x][y] = 1;
				number_of_arcs--;
			}
		}
	}
}
