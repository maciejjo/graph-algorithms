#ifndef GRAPH_H
#define GRAPH_H

void dfs_count(int **adjacency_matrix, int matrix_size, int *vertex_count, int *vertex_array, int vertex);
void fill_adjacency_matrix_dfg(int **adjacency_matrix, int matrix_size, float density);
void adjacency_list_from_matrix(int **adjacency_matrix, int matrix_size);

#endif
