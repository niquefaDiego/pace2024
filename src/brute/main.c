#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


/// ------------ Start of Input Parsing ------------

#define n_nodes (1+n0+n1)
int n0, n1, n_edges;
int *edge_a, *edge_b;

void read_input() {
	char line[100];
	do {
		scanf("%99[^\n]", line);
		getchar();
	} while (line[0] == 'c');

	sscanf(line, "p ocr %d %d %d", &n0, &n1, &n_edges);
	edge_a = (int*) malloc(n_edges * sizeof(int));
	edge_b = (int*) malloc(n_edges * sizeof(int));
	for (int i = 0; i < n_edges; ++i) {
		scanf("%d %d", edge_a+i, edge_b+i);
	}
}

/// ------------- End of Input Parsing -------------

/// --------- Start of Binary Indexed Tree ---------

int *bit;
int bit_size;

void build_bit (int size) {
	bit_size = size;
	bit = (int*) malloc(bit_size * sizeof(int));
	memset(bit, 0, bit_size * sizeof(int));
}

void update_bit(int i, int to_add) {
	for (; i < bit_size; i += i&-i)
		bit[i] += to_add;
}

int query_bit(int i) {
	int ans = 0;
	for (; i; i -= i&-i) ans += bit[i];
	return ans;
}

/// ---------- End of Binary Indexed Tree ----------

/// ----------- Start of DAG from B to A -----------

int *deg; // Degree of each node in B (from n0+1 to n0+n1)
int **edges_from_b; // DAG with edges from B to A

void build_dag_from_b_to_a() {
	deg = (int*) malloc(n_nodes * sizeof(int));
	for (int i = 0; i < n_edges; i++)
		deg[edge_b[i]]++;

	edges_from_b = (int**) malloc(n_nodes * sizeof(int*));
	for (int i = n0+1; i <= n0+n1; i++)
		edges_from_b[i] = (int*) malloc(deg[i] * sizeof(int));

	int *cur_index = (int*) malloc(n_nodes * sizeof(int));
	memset(cur_index, 0, sizeof(int) * n_nodes);
	for (int i = 0; i < n_edges; i++)
		edges_from_b[edge_b[i]][cur_index[edge_b[i]]++] = edge_a[i];
	free(cur_index);
}

/// ------------ End of DAG from B to A ------------


/// ------------- Start of brute force  ------------

int *order;
int *best_order;
int best_score = INT_MAX; // how many intersections in the best order

void go(int i, int score) {
	if (i < 0) {
		if (score < best_score) {
			best_score = score;
			memcpy(best_order, order, n1 * sizeof(int));
		}
		return;
	}

	int tmp;
	for (int j = i; j >= 0; j--) {
		// swap order[i] and order[j]
		tmp = order[i];
		order[i] = order[j];
		order[j] = tmp;

		// count inversions
		int node_b = order[i];
		int new_intersections = 0;
		for (int k = 0; k < deg[node_b]; ++k)
			new_intersections += query_bit(edges_from_b[node_b][k]-1);

		for (int k = 0; k < deg[node_b]; ++k)
			update_bit(edges_from_b[node_b][k], 1);

		go(i-1, score + new_intersections);

		for (int k = 0; k < deg[node_b]; ++k)
			update_bit(edges_from_b[node_b][k], -1);
	}
}

void find_best_order() {
	order = (int*) malloc(n1 * sizeof(int));
	best_order = (int*) malloc(n1 * sizeof(int));
	for (int i = 0; i < n1; i++)
		order[i] = n0+i+1;

	build_bit(n0+1);
	go(n1-1, 0);
}

/// ------------- End of brute force  ------------


int main()
{
	read_input();
	build_dag_from_b_to_a();
	find_best_order();

	for (int i = 0; i < n1; i++)
		printf("%d\n", best_order[i]);

	return 0;
}