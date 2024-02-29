// Dijkstra 알고리즘
// 가중치 인접행렬 출력하고 최단 경로 각 단계별로 출력

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF 100000
#define TRUE 1
#define FALSE 0

// 그래프의 정보를 저장하는 구조체 정의 
typedef struct GraphType {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES]; // 간선의 가중치 저장
} GraphType;

// 인접 행렬 출력 함수
void printMatrix(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            // INF 값은 '*'로 표시, 그 외의 값은 가중치 출력
            if (g->weight[i][j] == INF) printf("* ");
            else printf("%d ", g->weight[i][j]);
        }
        printf("\n");
    }
}

// 간선 추가 함수
void addEdge(GraphType* g, int src, int dest, int weight) {
    g->weight[src][dest] = weight;
}

// 최소 거리를 찾는 함수
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

// 다익스트라 알고리즘
void dijkstra(GraphType* g, int start) {
    int dist[MAX_VERTICES];
    int found[MAX_VERTICES]; // 방문 여부

    // 초기화
    for (int i = 0; i < g->n; i++) {
        dist[i] = INF;
        found[i] = FALSE;
    }

    // 시작 정점의 거리를 0으로 설정함
    dist[start] = 0;

    // 가중치 인접 행렬 출력
    printf("**********가중치 인접 행렬**********\n\n");
    printMatrix(g);
    printf("\n");

    // 다익스트라 최단 경로 출력
    printf("**********다익스트라 최단 경로 구하기**********\n\n");
    for (int count = 0; count < g->n; count++) {
        int u = minDistance(dist, found, g->n);
        found[u] = TRUE;

        for (int v = 0; v < g->n; v++) {
            if (found[v] == FALSE && g->weight[u][v] && dist[u] != INF && dist[u] + g->weight[u][v] < dist[v]) {
                dist[v] = dist[u] + g->weight[u][v];
            }
        }

        // 최단 경로 정보 출력
        printf("%d단계 : S={", count);
        for (int i = 0; i < g->n; i++) {
            if (found[i] == TRUE) {
                printf(" %c", i + 'A'); // 정점을 문자로 변환하여 출력
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

    // 그래프 초기화. 가중치를 INF로 설정
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (i == j) {
                g.weight[i][j] = 0; // 자기 자신으로의 경로의 가중치는 0
            }
            else {
                g.weight[i][j] = INF;
            }
        }
    }

    // 파일에서 데이터를 읽어와 가중치 업데이트
    g.n = 0; // 정점의 개수 초기화
    int x, y, a;
    while (fscanf(file, "%d %d %d", &x, &y, &a) == 3) {
        addEdge(&g, x, y, a);
        if (x > g.n) g.n = x;
        if (y > g.n) g.n = y;
    }
    g.n++; // 최대 정점 번호에서 1을 더하여 정점의 개수 계산

    fclose(file);

    printf("\nDijkstra의 최단 경로 알고리즘:\n");
    dijkstra(&g, 0);

    return 0;
}
