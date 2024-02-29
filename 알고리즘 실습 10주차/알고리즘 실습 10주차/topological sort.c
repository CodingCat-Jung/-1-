// �׷��� ���� ���� ���α׷�
// ���⼺�ִ� �׷����� ���� ���� ������
// ����Ŭ�� ���� �׷����� ���� ���� ������
// DAG = Directed Acyclic Graph

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int n;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;

// graph codes 
// init(), insert_vertex(), insert_edges()

void graph_init(GraphType* g)
{
	g->n = 0;

	for (int i = 0; i < MAX_VERTICES; i++) {
		g->adj_list[i] = NULL;
	}
}

void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) return;
	g->n++;
}

// u -> v
void insert_edge(GraphType* g, int u, int v)
{
	GraphNode* node;

	if (u >= g->n || v >= g->n) return;

	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

// stack codes
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

void init(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)
{
	if (is_full(s)) return;
	else
		s->stack[++(s->top)] = item;
}

element pop(StackType* s)
{
	if (is_empty(s)) exit(1);
	else
		return s->stack[(s->top)--];
}

element peek(StackType* s)
{
	if (is_empty(s)) exit(1);
	else
		return s->stack[s->top];
}


// topological sort

void topo_sort(GraphType* g)
{
	StackType s;
	int i, u, w;
	GraphNode* node;

	// 1. �־��� �׷��� g�� ���ؼ� �� ������ ���� ������ ���

	// int_in_degree[g->n]
	int* in_degree = (int*)malloc(sizeof(int) * g->n); // ������ ������ �𸣱� ������ ���� �迭
	for (i = 0; i < g->n; i++) in_degree[i] = 0;

	// ���Ḯ��Ʈ�� ǥ���Ǿ� �ִ� �׷��� g
	// ex) adj_list[0] -> 2 -> 3 -> NULL
	for (i = 0; i < g->n; i++) {
		node = g->adj_list[i]; // ��� ��带 ����Ʈ

		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}

	// 2. ���� ������ 0�� ������ ���ÿ� �ִ´�

	init(&s);
	for (i = 0; i < g->n; i++) {
		if (in_degree[i] == 0)
			push(&s, i);
	}

	// 3. ���ÿ��� ���� ������ 0�� ���� 1���� ������. ==>> �������� 1�� Ž�� �Ϸ�

	while (!is_empty(&s)) {
		w = pop(&s);
		printf("%d ", w);


		// 4��.
		node = g->adj_list[w]; // w���� ���� ������ �����ϱ� ����

		while (node != NULL) {
			u = node->vertex;
			in_degree[u]--; // ���� ���� �ϳ� ����

			if (in_degree[u] == 0) push(&s, u);

			node = node->link;
		}// end of inner while loop
	} // end of outer while loop

	// 4. ������ ������ ����Ǿ� �ִ� �̿� ������ ���� ������ 1���� ���δ�.

	// 5. 2������ �ݺ� ����

	// 6. ������ is_empty()�� TRUE�� �ɶ����� �ݺ�

	free(in_degree);
	return;
}

// main()

int main() {
	FILE* fp;
	fp = fopen("data2.txt", "r");

	GraphType g;
	char flag;
	int vertex, edge1, edge2;

	graph_init(&g);

	while (!feof(fp)) {
		fscanf(fp, "%c", &flag);

		if (flag == 'v') {
			fscanf(fp, "%d", &vertex);
			insert_vertex(&g, vertex);
		}

		else if (flag == 'e') {
			fscanf(fp, "%d %d", &edge1, &edge2);
			insert_edge(&g, edge1, edge2);
		}
	}

	topo_sort(&g);

	fclose(fp);
	return 0;
}