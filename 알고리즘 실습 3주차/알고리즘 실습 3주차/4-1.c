#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

// ������ �ʵ�
typedef struct {
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
}element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}TreeNode;

// e1 < e2 �̸� -1 ��ȯ
// e1 == e2 �̸� 0 ��ȯ
// e1 > e2 �̸� 1 ��ȯ
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}

TreeNode* insert_node(TreeNode** root, element key)
{
	TreeNode* t, * p;
	TreeNode* n;

	t = *root;
	p = NULL;

	while (t != NULL) {

		if (compare(key, t->key) == 0) // �̹� �ߺ��� �����Ͱ� ����
			return;
		
		p = t;

		if (compare(key, t->key) < 0)
			t = t->left;
		else
			t = t->right;
	}

	// while ������ ���� ������ �ߺ� �����Ͱ� ���� ������ �ܸ������� �˻��� �Ϸ����
	// �ű� Ʈ�� �߰�
	n = (TreeNode*)malloc(sizeof(TreeNode));
	// ����ڵ�
	if (n == NULL) return;

	n->key = key;
	n->left = n->right = NULL;

	if (p != NULL) {
		if (compare(key, p->key) < 0)
			p->left = n;
		else
			p->right = n;
	}
	else *root = n;
}

void display(TreeNode* root) // ���� ���·� ����ϱ� ���� inorder ����
{
	if (root != NULL) {
		display(root->left);
		printf("Ʈ����� ( %s : %s )", root->key.word, root->key.meaning);
		display(root->right);
		printf("-> ");
	}
}

TreeNode* search_node(TreeNode* root, element key)
{
	TreeNode* p = root;

	while (p != NULL) {
		switch (compare(key, p->key)) {
		case 0:
			return p;
		case -1:
			p = p->left;
			break;
		case 1:
			p = p->right;
			break;
		}
	}
	return p;
}

int main()
{
	FILE* fp;
	char command;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp;

	fp = fopen("data.txt", "r");

	//fp ����ڵ�

	while (!feof(fp)) {
		fscanf(fp, "%c", &command);

		switch (command) {
		case'i':
			//insert_node;
			fscanf(fp, " %s %s", e.word, e.meaning);
			insert_node(&root, e);
			printf("�ܾ� %s�� ����Ϸ�\n", e.word);
			break;
		case'd':
			//delete
			break;
		case's':
			//search
			fscanf(fp, "%s", e.word);
			strcpy(e.meaning, "");
			tmp = search_node(root, e);
			if (tmp != NULL) { // ������ �ܾ ������ �˻� ����
				printf("�ܾ� %s�� �ǹ̴� %s�Դϴ�.\n", tmp->key.word, tmp->key.meaning);
			}
			else {  // ������ �ش� �ܾ ����
				printf("\n�ܾ� %s�� ������ �����ϴ�.\n", e.word);
			}
			break;
		case'p':
			//print_node
			display(root);
			break;
		case'q':
			fclose(fp);
			exit(1);
			break;
		}
	}
	fclose(fp);
	return 0;
	//child case 3���� delete
}