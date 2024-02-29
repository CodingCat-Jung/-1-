#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000L
#define TRUE 1
#define FALSE 0

typedef struct {
	int u;
	int v;
	int key;
}element;

int weight[MAX_VERTICES][MAX_VERTICES];
int selected[MAX_VERTICES];
int dist[MAX_VERTICES];

int get_min_vertex(int n)
{
	int v, i;

	for (i = 0; i < n; i++) {
		if (!selected[i]) {
			v = i;
			break;
		}
	}

	for (i = 0; i < n; i++) {
		if (!selected[i] && (dist[i] < dist[v])) {
			v = i;
		}
	}

	return v;
}

void prim(int s, int n)
{
	int i;
	int u, v;
	for (i = 0; i < n; i++) {
		dist[i] = INF;
		selected[i] = FALSE;
	}

	dist[s] = 0; // {0, INF, INF, INF, ....}

	// prim main loop starts
	for (i = 0; i < n; i++) {
		u = get_min_vertex(n);
		selected[u] = TRUE;

		if (dist[u] == INF) return;

		printf("%d ", u);

		// distance array update
		for (v = 0; v < n; v++) {
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v])
					dist[v] = weight[u][v];
		}
	}
}

int main() {
	FILE* fp;
	fp = fopen("data3.txt", "r");
	if (fp == NULL) return 0;

	element e;
	int max = 0;
	int i, j;

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &e.u, &e.v, &e.key);
		if (e.v > max) 
			max = e.v;
	}

	max += 1;
	rewind(fp);

	for (i = 0; i < max; i++) {
		for (j = 0; j < max; j++) {
			if (i == j)
				weight[i][j] = 0;
			else
				weight[i][j] = INF;
		}
	}

	while(!feof(fp)) {
		fscanf(fp, "%d %d %d", &e.u, &e.v, &e.key);
		weight[e.u][e.v] = e.key;
		weight[e.v][e.u] = e.key;
	}

	prim(0, max);
	fclose(fp);

	return 0;
}