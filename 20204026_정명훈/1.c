// 20204026 1번

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


// 간선 추가 함수
void addEdge(GraphType* g, int src, int dest, int weight) {

    // 출발지에서 도착지까지의 가중치 설정
    g->weight[src][dest] = weight;
}

// 최소 거리를 찾는 함수
int minDistance(int dist[], int found[], int n) {

    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++) {

        // 방문하지 않은 정점 중 가장 작은 거리를 가진 정점을 찾음
        if (found[v] == FALSE && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }

    }

    return min_index; // 최소 거리를 가진 정점의 인덱스 반환
}

// 다익스트라 알고리즘
void dijkstra(GraphType* g, int start) {

    int dist[MAX_VERTICES]; // 시작 정점으로부터의 거리를 저장할 배열
    int found[MAX_VERTICES]; // 방문 여부를 저장할 배열

    int total = 0;

    // 초기화
    for (int i = 0; i < g->n; i++) {
        dist[i] = INF; // 초기 거리를 무한대로 설정
        found[i] = FALSE; // 방문 여부를 FALSE
    }

    // 시작 정점의 거리를 0으로 설정함
    dist[start] = 0;

    // 다익스트라 최단 경로 출력
    printf("**********다익스트라 최단 경로 구하기**********\n\n");
    for (int count = 0; count < g->n; count++) {

        int u = minDistance(dist, found, g->n); // 가장 가까운 정점을 찾음
        found[u] = TRUE; // 해당 정점을 방문했다고 표시

        for (int v = 0; v < g->n; v++) {

            // 아직 방문하지 않은 정점 중에 최단 거리 업데이트
            if (found[v] == FALSE && g->weight[u][v] && dist[u] != INF && dist[u] + g->weight[u][v] < dist[v]) {
                dist[v] = dist[u] + g->weight[u][v]; // 최단 거리 업데이트
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

    for (int i = 0; i < g->n; i++) {
        total += dist[i];
    }

    printf("Result Total Weight : %d\n", total);
}

int main() {
    GraphType g;

    // 그래프 초기화. 가중치를 INF로 설정
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (i == j) {
                g.weight[i][j] = 0; // 자기 자신으로의 경로의 가중치는 0
            }
            else {
                g.weight[i][j] = INF; // 그 외에는 무한대로 초기화
            }
        }
    }

    // 정점의 개수는 10개
    g.n = 10;

    // 각 간선 추가 및 가중치 입력
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
   
    printf("\nDijkstra의 최단 경로 알고리즘:\n");
    dijkstra(&g, 0);

    return 0;
}
