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

void delete_node(TreeNode** root, element key)
{
	// t = traverse node
	// p = parent node of t
	TreeNode* t, * p, * child, * succ, * succ_p;

	p = NULL;
	t = *root;

	while (t != NULL && compare(t->key, key) != 0)
	{
		// key���� ��ġ���� ����
		p = t;
		t = (compare(key, t->key) < 0) ? t->left : t->right;

	}

	// case1. t == NULL - �˻� ����, �����Ϸ��� key�� ����x
	if (t == NULL) {
		printf("�����Ϸ��� �����Ͱ� �����ϴ�.\n");
		return;
	}

	// case2. key�� Ʈ���� �����ϴ� ���

		// case2-1. t�� child node�� ���� ���(leaf node)
	if (t->left == NULL && t->right == NULL) {
		// 2-1-1. parent node�� �ִ� ���
		if (p != NULL) {
			// case2-1-1-1. t�� p�� ���� child�� ���
			if (p->left == t) p->left == NULL;

			// case2-1-1-2. t�� p�� ������ child�� ���
			else p->right == NULL;

		}

		// 2-1-2. parent node�� ���� ��� - > Ʈ���� ������ ��尡 t�� ���
		else {
			*root == NULL;
		}
	}

	// case2-2. t�� child node�� �� ���� �ִ� ���
	else if (t->left == NULL || t->right == NULL) {
		// ���� ����� �����͸� ��´�
		child = (t->left != NULL) ? t->left : t->right;

		// case2-2-1. parent node�� �ִ� ���
		if (p != NULL) {
			// case2-2-1-1. t�� parent�� ���� �ڽ��� ���
			if (p->left == t)
				p->left = child;
			// t�� parent node�� ������ �ڽ��� ���
			else
				p->right = child;
		}
		// case2-2-2. parent node�� ���� ���
		else {
			*root = child;
		}
	}

	// case2-3. t�� left,right�� ��� �����ϴ� ���
	else {
		// ������ ����Ʈ������ �İ��� ����
		succ_p = t;
		succ = t->right;

		// ������ ����Ʈ������ ���� ���� ��带 ã��
		// ������ ����Ʈ������ ���� ���� ���� ���� ���� ���� �ִ� ���
		// ���� Ž�� Ʈ���̱� ������ ������ ����
		while (succ->left != NULL)
		{
			succ_p = succ;
			succ = succ->left;
		}

		if (succ_p->left == succ) {
			succ_p->left = succ->right;
		}

		else succ_p->right = succ->right;

		t->key = succ->key;
		t = succ;
	}
	free(t);

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
			//delete_node;
			fscanf(fp, "%s", e.word);
			strcpy(e.meaning, "");
			delete_node(&root, e);
			printf("�ܾ� %s ���� �Ϸ�\n", e.word);
			break;
		case's':
			//search_node
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