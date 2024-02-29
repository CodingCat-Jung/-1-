#define _CRT_SECURE_NO_WARNINGS
#include <Stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF 100000
#define TRUE 1
#define FALSE 0

typedef struct GraphType {
	int n; // number of vertex
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int distance[MAX_VERTICES]; // weight of start vertex A to remaining vertices
int found[MAX_VERTICES]; // visited vertices

void print_status(GraphType* g)
{
	static int step = 1;
	printf("STEP %d : ", step++);
	printf("distance: ");

	for (int i = 0; i < g->n; i++)
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);

	printf("\n");
	printf("found: ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);

	printf("\n\n");
}

int choose(int distance[], int n, int found[])
{
	int i;
	int min, minpos;

	min = INT_MAX;
	minpos = -1;

	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
void shortest_path(GraphType* g, int start)
{
	int i, u, w;

	// init
	for (i = 0; i < g->n; i++) {
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}

	found[start] = TRUE;
	distance[start] = 0;

	// main dijkstra loop
	// start = v 
	// v->w vs v->u + u->w
	// distance[w] vs distance[w] + weight[u][w]
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);  // try to find minimun weight vertex from distance array
		found[u] = TRUE;

		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
	}
}
int main()
{
	GraphType g;
	FILE* fp;
	int x, y, a;
	fp = fopen("data1.txt", "r");

	// init
	for (int i = 0; i < MAX_VERTICES; i++)
		for (int j = 0; j < MAX_VERTICES; j++)
			if (i == j)
				g.weight[i][j] = INF;
			else
				g.weight[i][j] = INF;

	// #of vertices
	g.n = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &x, &y, &a);
		if (x > g.n)
			g.n = x;
		if (y > g.n)
			g.n = y;
	}
	g.n++;

	rewind(fp);

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &x, &y, &a);
		g.weight[x][y] = a;
		g.weight[y][x] = a; // undirected graph handling
	}

	printf("start vertex : 0\n");
	shortest_path(&g, 0);

	fclose(fp);
	return 0;
}