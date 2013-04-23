#ifndef GRAPH_H
#define GRAPH_H
#include "list.h"

void dfs_count(int **adjacency_matrix, int matrix_size, int *vertex_count, int *vertex_array, int vertex);
void fill_adjacency_matrix_dfg(int **adjacency_matrix, int matrix_size, float density);
void mirror_adjacency_matrix(int **input_matrix, int matrix_size, int **output_matrix);
void adjacency_list_from_matrix(int **adjacency_matrix, int matrix_size, list **adjacency_list_array);
void edge_list_from_adjacency_list(list **adjacency_list_array, float density, int matrix_size, int**edge_list);

#endif
