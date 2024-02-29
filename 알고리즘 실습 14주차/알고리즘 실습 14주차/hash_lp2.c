#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 13
#define KEY_SIZE 10

#define empty(item) (strlen(item.key)==0)
#define equal(item1, item2) (!strcmp(item1.key, item2.key))

typedef struct {
	char key[KEY_SIZE];
}element;

element hash_table[TABLE_SIZE];

// string to integer convertion
int transform1(char* key)
{
	int number = 0;

	while (*key) {
		number = number + *key++;
	}

	return number;
}

int hash_funtion(char* key)
{
	return transform1(key) % TABLE_SIZE;
}

void hash_lp_add(element item, element ht[])
{
	
	int hash_value, i;
	hash_value = i = hash_funtion(item.key);

	// �浹 ���� Ȯ��
	while (!empty(ht[i])) {
		printf("collision detected �浹 �߻�\n");
		// �ߺ� ���������� Ȯ��
		if (equal(item, ht[i])) {
			printf("�ߺ��� ���� �̹� �����մϴ�. \n");
			return;
		}

		// linear probing
		i = (i + 1) % TABLE_SIZE;

		// �ؽ� ���̺� is_full ���� Ȯ��
		if (i == hash_value) {
			printf("���̺��� ����á���ϴ�. \n");
			return;
		}
	}

	ht[i] = item;
}

void hash_lp_print(element ht[])
{
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("[%d] %s\n", i, ht[i].key);
	}
	printf("\n");
}

void hash_lp_search(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_funtion(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			printf("Ž�� : slot %d key %s \n", i, ht[i].key);
			return;
		}

		printf("collision detected. \n");

		// linear probing
		i = (i + 1) % TABLE_SIZE;

		if (i == hash_value) {
			printf("�ؽ� ���̺��� ã�� ���߽��ϴ�. \n");
			return;
		}
	}

	printf("no key found in hash table. \n");
}

int main() {
	char* s[7] = { "do","for","if","case","else","return","funtion" };

	element e;

	for (int i = 0; i < 7; i++) {
		strcpy(e.key, s[i]);
		hash_lp_add(e, hash_table);
		hash_lp_print(hash_table);
	}

	for (int i = 0; i < 7; i++) {
		strcpy(e.key, s[i]);
		hash_lp_search(e, hash_table);
	}

	return 0;
}