#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 7
#define INF 100000

int weight[MAX_VERTICES][MAX_VERTICES];
int floyd[MAX_VERTICES][MAX_VERTICES];

void shortest_path(int n)
{
	int i, j, k;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++) 
		{
			floyd[i][j] = weight[i][j];
		}
	}

	printf("-1 상태\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (floyd[i][j] == INF) printf(" | INF ");
			else printf(" |%-4d", floyd[i][j]);
		}
		printf("\n\n");
	}

	// main floyd loop
	for (k = 0; k < n; k++) // k = 경유지
	{
		printf("0부터 %d까지의 모든 정점을 이용한 최단거리\n", k);
		// i j k => i->j vs i->k + k->j
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (floyd[i][j] > floyd[i][k] + floyd[k][j]) floyd[i][j] = floyd[i][k] + floyd[k][j];

				if (floyd[i][j] == INF) printf(" | INF ");
				else printf(" |%-4d", floyd[i][j]);
			}
			printf("\n\n");
		}
	}
}

int main() {

	FILE* fp;
	fp = fopen("data1.txt", "r");
	if (fp == NULL) return 0;

	int i, j, x, y, a;

	for (i = 0; i < MAX_VERTICES; i++)
		for (j = 0; j < MAX_VERTICES; j++)
			if (i == j) weight[i][j] = 0;
			else weight[i][j] = INF;

	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d", &x, &y, &a);
		weight[x][y] = a;
		weight[y][x] = a;
	}

	shortest_path(MAX_VERTICES);


	fclose(fp);
	return 0;
}