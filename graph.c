#include <stdlib.h>
#include <stdio.h>

void dfs_count(int **adjacency_matrix, int matrix_size, int *vertex_count,  int *vertex_array, int vertex) {
	
	//Dodawanie do listy odwiedzonych i zwiększenie licznika odwiedzonych
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
				dfs_count(adjacency_matrix, matrix_size, vertex_count, vertex_array, i);
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
	printf("Należy wygenerować %d łuków\n", number_of_arcs);

	while(number_of_arcs) {
		//Losowanie współrzędnych w macierzy
		int x = rand() % matrix_size;
		int y = rand() % matrix_size;
		//Jeśli są różne (nie są na przekątnej)
		if(x != y)
		{	
			//Jeśli x>y to zamieniamy współrzędne żeby być w górnym trójkącie
			if(x>y) {
				int tmp = x;
				x = y;
				y = tmp;
			}
			
			//Jeśli w danym miejscu nie ma jeszcze jedynki
			if(adjacency_matrix[x][y] == 0) {
				adjacency_matrix[x][y] = 1;
				number_of_arcs--;
			}
		}
	}
}
