#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 100

typedef struct {
	int key; // 우선순위
	char animal[MAX_LEN];
}element;

typedef struct {
	int heap_size;
	element heap[MAX_LEN];
}HeapType;

void init(HeapType* h)
{
	h->heap_size = 0;
}

// upheap
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	// 루트노드가 아니고 && 신입 사원이 부모 노드보다 크면
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

void display(HeapType* h)
{
	int i;
	for (i = 1; i < h->heap_size + 1; i++) {
		printf("%d : %s > ", h->heap[i].key, h->heap[i].animal);
	}
	printf("\n\n");
}

int main() {
	FILE* fp;
	fp = fopen("data.txt", "r");
	if (fp == NULL) exit(1);

	element tmp;
	HeapType heap;

	init(&heap);

	while (!feof(fp)) {
		fscanf(fp, "%d %s", &tmp.key, tmp.animal);
		printf("%d %s\n", tmp.key, tmp.animal);

		insert_max_heap(&heap, tmp);
		display(&heap);
	}



	while (1) {
		printf("동물의 우선순위와 이름을 입력하시오(0: 완료) \n");
		printf(">> ");
		scanf("%d", &tmp.key);

		if (tmp.key != 0) {
			scanf("%s", tmp.animal);
			insert_max_heap(&heap, tmp);
			display(&heap);
		}
		else break;
	}

	fclose(fp);
	return 0;
}