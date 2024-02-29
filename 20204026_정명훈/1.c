// 20204026 1��

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


// ���� �߰� �Լ�
void addEdge(GraphType* g, int src, int dest, int weight) {

    // ��������� ������������ ����ġ ����
    g->weight[src][dest] = weight;
}

// �ּ� �Ÿ��� ã�� �Լ�
int minDistance(int dist[], int found[], int n) {

    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++) {

        // �湮���� ���� ���� �� ���� ���� �Ÿ��� ���� ������ ã��
        if (found[v] == FALSE && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }

    }

    return min_index; // �ּ� �Ÿ��� ���� ������ �ε��� ��ȯ
}

// ���ͽ�Ʈ�� �˰���
void dijkstra(GraphType* g, int start) {

    int dist[MAX_VERTICES]; // ���� �������κ����� �Ÿ��� ������ �迭
    int found[MAX_VERTICES]; // �湮 ���θ� ������ �迭

    int total = 0;

    // �ʱ�ȭ
    for (int i = 0; i < g->n; i++) {
        dist[i] = INF; // �ʱ� �Ÿ��� ���Ѵ�� ����
        found[i] = FALSE; // �湮 ���θ� FALSE
    }

    // ���� ������ �Ÿ��� 0���� ������
    dist[start] = 0;

    // ���ͽ�Ʈ�� �ִ� ��� ���
    printf("**********���ͽ�Ʈ�� �ִ� ��� ���ϱ�**********\n\n");
    for (int count = 0; count < g->n; count++) {

        int u = minDistance(dist, found, g->n); // ���� ����� ������ ã��
        found[u] = TRUE; // �ش� ������ �湮�ߴٰ� ǥ��

        for (int v = 0; v < g->n; v++) {

            // ���� �湮���� ���� ���� �߿� �ִ� �Ÿ� ������Ʈ
            if (found[v] == FALSE && g->weight[u][v] && dist[u] != INF && dist[u] + g->weight[u][v] < dist[v]) {
                dist[v] = dist[u] + g->weight[u][v]; // �ִ� �Ÿ� ������Ʈ
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

    for (int i = 0; i < g->n; i++) {
        total += dist[i];
    }

    printf("Result Total Weight : %d\n", total);
}

int main() {
    GraphType g;

    // �׷��� �ʱ�ȭ. ����ġ�� INF�� ����
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (i == j) {
                g.weight[i][j] = 0; // �ڱ� �ڽ������� ����� ����ġ�� 0
            }
            else {
                g.weight[i][j] = INF; // �� �ܿ��� ���Ѵ�� �ʱ�ȭ
            }
        }
    }

    // ������ ������ 10��
    g.n = 10;

    // �� ���� �߰� �� ����ġ �Է�
    // 0 = A
    addEdge(&g, 0, 2, 34); 
    addEdge(&g, 0, 3, 42);
    addEdge(&g, 0, 9, 24);

    // 1 = B
    addEdge(&g, 1, 2, 42);
    addEdge(&g, 1, 4, 12);
    addEdge(&g, 1, 9, 18);

    // 2 = C
    addEdge(&g, 2, 0, 34);
    addEdge(&g, 2, 1, 42);
    addEdge(&g, 2, 3, 7);
    addEdge(&g, 2, 4, 28);
    addEdge(&g, 2, 5, 15);
    addEdge(&g, 2, 9, 61);

    // 3 = D
    addEdge(&g, 3, 0, 42);
    addEdge(&g, 3, 2, 7);
    addEdge(&g, 3, 5, 23);
    addEdge(&g, 3, 6, 12);

    // 4 = E
    addEdge(&g, 4, 1, 12);
    addEdge(&g, 4, 2, 28);
    addEdge(&g, 4, 5, 11);
    addEdge(&g, 4, 7, 47);

    // 5 = F
    addEdge(&g, 5, 2, 15);
    addEdge(&g, 5, 3, 23);
    addEdge(&g, 5, 4, 11);
    addEdge(&g, 5, 6, 38);
    addEdge(&g, 5, 7, 35);

    // 6 = G
    addEdge(&g, 6, 3, 12);
    addEdge(&g, 6, 5, 38);
    addEdge(&g, 6, 8, 14);

    // 7 = H
    addEdge(&g, 7, 4, 47);
    addEdge(&g, 7, 5, 35);
    addEdge(&g, 7, 8, 11);

    // 8 = T
    addEdge(&g, 8, 6, 14);
    addEdge(&g, 8, 7, 11);

    // 9 = S
    addEdge(&g, 9, 0, 24);
    addEdge(&g, 9, 1, 42);
   
    printf("\nDijkstra�� �ִ� ��� �˰���:\n");
    dijkstra(&g, 0);

    return 0;
}
