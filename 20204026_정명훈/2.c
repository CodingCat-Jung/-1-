// 20204026 2��

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AVL Ʈ�� ��忡 �� ������ ����ü
typedef struct {
	char word[20];
	char mean[20];
}element;

// AVL Ʈ�� ��� ����ü
typedef struct AvlNode {
	element data;
	struct AvlNode* left_child, * right_child;
}AvlNode;

// AVL Ʈ�� ��Ʈ ��� ����
AvlNode* root;

// �������� ȸ���ϴ� LL�Լ�
AvlNode* rotate_LL(AvlNode* parent)
{
	AvlNode* child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}

// ���������� ȸ���ϴ� RR�Լ�
AvlNode* rotate_RR(AvlNode* parent)
{
	AvlNode* child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}

AvlNode* rotate_RL(AvlNode* parent)
{
	AvlNode* child = parent->right_child;
	parent->right_child = rotate_LL(child);
	return rotate_RR(parent);
}

AvlNode* rotate_LR(AvlNode* parent)
{
	AvlNode* child = parent->left_child;
	parent->left_child = rotate_RR(child);
	return rotate_LL(parent);
}

// �� ���� �� ū ���� ��ȯ�ϴ� �Լ�
int maxs(int a, int b)
{
	int result = 0;

	if (a > b)
	{
		result = a;
	}
	else if (a <= b)
	{
		result = b;
	}

	return result;
}

// ����� ���̸� ���ϴ� �Լ�
int get_height(AvlNode* node)
{
	int height = 0;

	if (node != NULL)
		height = 1 + maxs(get_height(node->left_child), get_height(node->right_child));
	return height;
}

// ����� ���� ���̸� ���ϴ� �Լ�
int get_height_diff(AvlNode* node)
{
	if (node == NULL) return 0;

	return get_height(node->left_child) - get_height(node->right_child);
}

// AVL Ʈ���� ������ϴ� �Լ�
AvlNode* rebalance(AvlNode** node)
{
	// ���� ���� ���Ѵ�
	int height_diff = get_height_diff(*node);

	// ���� ���̰� 1���� ũ��
	if (height_diff > 1)
	{
		if (get_height_diff((*node)->left_child) > 0)
			*node = rotate_LL(*node);
		else
			*node = rotate_LR(*node);
	}

	// ���� ���̰� -1���� ������
	else if (height_diff < -1)
	{
		if (get_height_diff((*node)->right_child) < 0)
			*node = rotate_RR(*node);
		else
			*node = rotate_RL(*node);
	}

	return *node;
}

// AVL Ʈ���� ��带 �߰��ϴ� �Լ�
AvlNode* avl_add(AvlNode** root, element new_key)
{
	// ��Ʈ ��尡 ���������
	if (*root == NULL)
	{
		*root = (AvlNode*)malloc(sizeof(AvlNode));

		if (*root == NULL) // �Ҵ� ���н� ����
		{
			fprintf(stderr, "�޸� �Ҵ� ����\n");
			exit(1);
		}

		// ��� ������ �����ϰ� �ڽ� ��� �ʱ�ȭ
		(*root)->data = new_key;
		(*root)->left_child = (*root)->right_child = NULL;
	}

	// ���ο� Ű�� ���� ����� Ű���� ũ��
	else if (strcmp(new_key.word, (*root)->data.word) > 0)
	{
		// ���� ����Ʈ���� �߰�
		(*root)->left_child = avl_add(&((*root)->left_child), new_key);
		(*root) = rebalance(root);
	}

	// ���ο� Ű�� ���� ����� Ű���� ������
	else if (strcmp(new_key.word, (*root)->data.word) < 0)
	{
		// ������ ����Ʈ���� �߰�
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);
		(*root) = rebalance(root);
	}

	else
	{
		fprintf(stderr, "�ߺ��� Ű ����\n");
		exit(1);
	}

	return *root;
}

// AVL Ʈ������ Ű�� Ž���ϴ� �Լ�
AvlNode* avl_search(AvlNode* node, element key)
{
	if (node == NULL) return NULL;
	//printf("%s %s\n ", node->data.word, node->data.mean);

	// ���� ����� Ű�� ã�� Ű�� ������ ���� ��� ��ȯ
	if (strcmp(key.word, node->data.word) == 0)
		return node;

	// ã�� Ű�� ���� ����� Ű���� ũ�� ���� ����Ʈ������ Ž��
	else if (strcmp(key.word, node->data.word) > 0)
		return avl_search(node->left_child, key);

	else
		return avl_search(node->right_child, key);
}

void display(AvlNode* node, int level)
{
	int i;

	if (node != NULL)
	{
		display(node->right_child, level + 1);
		printf("\n");
	}
	else
		return;

	for (i = 0; i < level; i++)
	{
		printf("\t\t");
	}

	printf("(%s-%s)", node->data.word, node->data.mean);
	display(node->left_child, level + 1);
}

// AVL Ʈ���� ���� ��ȸ�ϸ� ���
void preorder(AvlNode* root) {
	if (root != NULL) {
		printf("%s-%s ", root->data.mean, root->data.word);
		preorder(root->left_child);
		preorder(root->right_child);
	}
}

int main()
{
	FILE* fp;
	char flag;
	element tmp;
	AvlNode* AN;

	fp = fopen("data2.txt", "r");

	while (!feof(fp))
	{
		fscanf(fp, "%c", &flag);

		if (flag == 'i')
		{
			fscanf(fp, "%s %s", tmp.word, tmp.mean);
			printf("���� : %s %s\n", tmp.word, tmp.mean);
			avl_add(&root, tmp);
		}

		if (flag == 's')
		{
			fscanf(fp, "%s", &tmp.word);

			printf("\n< %s�� �ǹ� Ž�� >\n", tmp.word);
			strcpy(tmp.mean, ""); // �� ������ �ʱ�ȭ
			AN = avl_search(root, tmp);
			printf("%s�� ����� %s�Դϴ�.\n", AN->data.word, AN->data.mean);
		}
	}

	printf("\n\n< AVL Ʈ�� ��� >\n");
	display(root, 0);

	printf("\n\n");
	printf("< AVL Ʈ�� ������ȸ ��� ��� >\n");
	preorder(root);
	fclose(fp);
}