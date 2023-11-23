#include <stdio.h>
#include <stdlib.h>

int n0, n1, n_edges;
int *edge_a, *edge_b;

void read_input() {
	char line[100];
	do { scanf("%99[^\n]", line); getchar(); }
	while (line[0] == 'c');
	sscanf(line, "p ocr %d %d %d", &n0, &n1, &n_edges);
	edge_a = (int*) malloc(n_edges * sizeof(int));
	edge_b = (int*) malloc(n_edges * sizeof(int));
	for (int i = 0; i < n_edges; ++i)
		scanf("%d %d", edge_a+i, edge_b+i);
}

int main()
{
	read_input();
	for (int i = 0; i < n1; i++) {
		printf("%d\n", n0+1+i);
	}
	return 0;
}