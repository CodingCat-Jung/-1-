// Dijkstra �˰���
// ����ġ ������� ����ϰ� �ִ� ��� �� �ܰ躰�� ���

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF 100000
#define TRUE 1
#define FALSE 0

// �׷����� ������ �����ϴ� ����ü ���� 
typedef struct GraphType {
    int n; // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES]; // ������ ����ġ ����
} GraphType;

// ���� ��� ��� �Լ�
void printMatrix(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            // INF ���� '*'�� ǥ��, �� ���� ���� ����ġ ���
            if (g->weight[i][j] == INF) printf("* ");
            else printf("%d ", g->weight[i][j]);
        }
        printf("\n");
    }
}

// ���� �߰� �Լ�
void addEdge(GraphType* g, int src, int dest, int weight) {
    g->weight[src][dest] = weight;
}

// �ּ� �Ÿ��� ã�� �Լ�
int minDistance(int dist[], int found[], int n) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++) {
        if (found[v] == FALSE && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// ���ͽ�Ʈ�� �˰���
void dijkstra(GraphType* g, int start) {
    int dist[MAX_VERTICES];
    int found[MAX_VERTICES]; // �湮 ����

    // �ʱ�ȭ
    for (int i = 0; i < g->n; i++) {
        dist[i] = INF;
        found[i] = FALSE;
    }

    // ���� ������ �Ÿ��� 0���� ������
    dist[start] = 0;

    // ����ġ ���� ��� ���
    printf("**********����ġ ���� ���**********\n\n");
    printMatrix(g);
    printf("\n");

    // ���ͽ�Ʈ�� �ִ� ��� ���
    printf("**********���ͽ�Ʈ�� �ִ� ��� ���ϱ�**********\n\n");
    for (int count = 0; count < g->n; count++) {
        int u = minDistance(dist, found, g->n);
        found[u] = TRUE;

        for (int v = 0; v < g->n; v++) {
            if (found[v] == FALSE && g->weight[u][v] && dist[u] != INF && dist[u] + g->weight[u][v] < dist[v]) {
                dist[v] = dist[u] + g->weight[u][v];
            }
        }

        // �ִ� ��� ���� ���
        printf("%d�ܰ� : S={", count);
        for (int i = 0; i < g->n; i++) {
            if (found[i] == TRUE) {
                printf(" %c", i + 'A'); // ������ ���ڷ� ��ȯ�Ͽ� ���
            }
        }
        printf(" } distance: {");
        for (int i = 0; i < g->n; i++) {
            if (dist[i] == INF) {
                printf(" *");
            }
            else {
                printf(" %d", dist[i]);
            }
        }
        printf(" }\n");
        printf("----------------------\n");
    }
}

int main() {
    GraphType g;
    FILE* file = fopen("data2.txt", "r");
    if (file == NULL) {
        printf("Error\n");
        return -1;
    }

    // �׷��� �ʱ�ȭ. ����ġ�� INF�� ����
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (i == j) {
                g.weight[i][j] = 0; // �ڱ� �ڽ������� ����� ����ġ�� 0
            }
            else {
                g.weight[i][j] = INF;
            }
        }
    }

    // ���Ͽ��� �����͸� �о�� ����ġ ������Ʈ
    g.n = 0; // ������ ���� �ʱ�ȭ
    int x, y, a;
    while (fscanf(file, "%d %d %d", &x, &y, &a) == 3) {
        addEdge(&g, x, y, a);
        if (x > g.n) g.n = x;
        if (y > g.n) g.n = y;
    }
    g.n++; // �ִ� ���� ��ȣ���� 1�� ���Ͽ� ������ ���� ���

    fclose(file);

    printf("\nDijkstra�� �ִ� ��� �˰���:\n");
    dijkstra(&g, 0);

    return 0;
}
