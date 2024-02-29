#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
	int n; // of vertex
	int adj_max[MAX_VERTICES][MAX_VERTICES];
}GraphType;

void graph_init(GraphType* g)
{
	int row, col;
	g->n = 0;

	for (row = 0; row < MAX_VERTICES; row++) {
		for (col = 0; col < MAX_VERTICES; col++) {
			g->adj_max[row][col] = 0;
		}
	}
}

void insert_vertex(GraphType* g, int v)
{
	if ((g->n) + 1 > MAX_VERTICES) {
		printf("정점 개수 초과\n");
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end)
{
	if ((start >= g->n) || (end >= g->n)) {
		printf("정점 개수 초과\n");
		return;
	}
	g->adj_max[start][end] = 1;
	g->adj_max[end][start] = 1;
}

// queue codes for bfs

// end

void bfs(GraphType* g, int v)
{

}

int main() {
	FILE* fp;
	fp = fopen("data02.txt", "r");
	if (fp == NULL) exit(1);

	GraphType g;
	char cmd;
	int v1, v2;

	while (!feof(fp)) {
		fscanf(fp, "%c", &cmd);
		switch (cmd)
		{
		case 'v':
			fscanf(fp, "%d", &v1);
			insert_vertex(&g, v1);
			break;
		case 'e':
			fscanf(fp, "%d %d", &v1, &v2);
			insert_edge(&g, v1, v2);
			break;
		default:
			break;
		} // end of switch
	} // end of while

	printf("breath first search : ");
	bfs(&g, 0);

	fclose(fp);
	return 0;
}