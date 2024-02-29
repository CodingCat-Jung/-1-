#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7

typedef struct {
	int key;
}element;

typedef struct {
	element data;
	struct list* link;
}list;

list* hash_table[TABLE_SIZE];

int hash_function(int key)
{
	return key % TABLE_SIZE;
}

void hash_chain_add(element item, list* ht[])
{
	int hash_value = hash_function(item.key);

	list* ptr;
	list* node_before = NULL;
	list* node = ht[hash_value];

	// dupe check
	// node not NULL
	for (; node; node_before = node, node = node->link) {
		if (node->data.key == item.key) {
			printf("deplicated key in hash table. 중복 키 존재 \n");
			return;
		}
	}

	ptr = (list*)malloc(sizeof(list));
	ptr->data = item;
	ptr->link = NULL;

	if (node_before) {
		node_before->link = ptr;
	}

	else ht[hash_value] = ptr;
}

void hash_chain_print(list* ht[])
{
	list* node;
	int i;

	for (i = 0; i < TABLE_SIZE; i++) {
		printf("slot %d -> ", i);

		for (node = ht[i]; node; node = node->link) {
			printf("%d -> ", node->data.key);
		}

		printf("\n");
	}

	printf("\n");
}

void hash_chain_search(element item, list* ht[])
{
	list* node;

	int hash_value = hash_function(item.key);

	for (node = ht[hash_value]; node; node = node->link) {
		if (node->data.key == item.key) {
			printf("탐색 성공 %d \n", item.key);
			return;
		}
	}

	printf("no key found in hash table \n");
}

int main() {
	int data[5] = { 8,1,9,6,13 };

	element e;

	for (int i = 0; i < 5; i++) {
		e.key = data[i];
		hash_chain_add(e, hash_table);
		hash_chain_print(hash_table);
	}

	for (int i = 0; i < 5; i++) {
		e.key = data[i];
		hash_chain_search(e, hash_table);
	}

	return 0;
}