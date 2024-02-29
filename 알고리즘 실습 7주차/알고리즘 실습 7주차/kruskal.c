#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VARTICES 100
#define INF 10000

int parent[MAX_VARTICES];
int num[MAX_VARTICES];

int set_init(int n)
{
	int i;

	for (i = 0; i < n; i++) {
		parent[i] = -1;
		num[i] = 1;
	}
}

// retrun ultimate ancestor of given vertex
int set_find(int vertex)
{
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		;

	s = i;
	for (i = vertex; (p = parent[i]) >= 0; i = p) {
		parent[i] = s;
	}
	return s;
}

// s1 and s2 같은 집합인지 확인
void set_union(int s1, int s2)
{
	if (num[s1] < num[s2]) {
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

typedef struct {
	int u;
	int v;
	int key;
}element;

typedef struct {
	element heap[MAX_VARTICES];
	int heap_size;
}HeapType;

void init(HeapType* h)
{
	h->heap_size = 0;
}

int is_empty(HeapType* h)
{
	if (h->heap_size == 0)
		return 1;
	else return 0;
}

void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && item.key < h->heap[i / 2].key) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && h->heap[child].key > h->heap[child + 1].key)
			child++;

		if (temp.key <= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;

	return item;
}

void insert_all_edges(HeapType* h)
{
	FILE* fp;
	element e;

	fp = fopen("data2.txt", "r");
	if (fp == NULL) return;

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &e.u, &e.v, &e.key);
		insert_min_heap(h, e);
	}

	fclose(fp);
}

void kruskal(int n)
{
	HeapType h;
	element e;

	int edge_accpted = 0;
	int uset, vset;

	init(&h);
	insert_all_edges(&h);

	set_init(n);

	while (edge_accpted < (n - 1)) {
		e = delete_min_heap(&h);
		// from to weight
		uset = set_find(e.u);
		vset = set_find(e.v);

		if (uset != vset) {
			printf("(%d, %d) %d\n", e.u, e.v, e.key);
			edge_accpted++;
			set_union(uset, vset);
		}// end of if

	}// end of while
}

int main() {
	FILE* fp;
	fp = fopen("data2.txt", "r");
	if (fp == NULL) return 0;

	int max = 0;
	element e;

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &e.u, &e.v, &e.key);
		if (e.v > max) max = e.v;
	}

	kruskal(max + 1);
	fclose(fp);

	return 0;
}