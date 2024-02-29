#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 10
#define TABLE_SIZE 13

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

void hash_lp_delete(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_funtion(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			printf("���� : slot %d key %s \n", i, ht[i].key);
			ht[i].key[0] = NULL;
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
	element e;

	char cmd[5];
	char name[100];

	while (1) {
		printf("����(i), Ž��(s), ����(d), ����(q): ");
		scanf("%s", cmd);

		if (strcmp(cmd, "i") == 0) {
			printf("������ �̸� : ");
			scanf("%s", name);
			strcpy(e.key, name);
			hash_lp_add(e, hash_table);
		}
		else if (strcmp(cmd, "s") == 0) {
			printf("������ �̸� : ");
			scanf("%s", name);
			strcpy(e.key, name);
			hash_lp_search(e, hash_table);
		}
		else if (strcmp(cmd, "d") == 0) {
			printf("������ �̸� : ");
			scanf("%s", name);
			strcpy(e.key, name);
			hash_lp_delete(e, hash_table);
		}
		else if (strcmp(cmd, "q") == 0) {
			break;
		}

		hash_lp_print(hash_table);
	} // end of while

	return 0;
}