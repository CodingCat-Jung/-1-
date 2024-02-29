#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char word[20];
	char mean[20];
}element;

typedef struct AvlNode {
	element data;
	struct AvlNode* left_child, * right_child;
}AvlNode;

AvlNode* root;

AvlNode* rotate_LL(AvlNode* parent)
{
	AvlNode* child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}

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

int get_height(AvlNode* node)
{
	int height = 0;

	if (node != NULL)
		height = 1 + maxs(get_height(node->left_child), get_height(node->right_child));
	return height;
}

int get_height_diff(AvlNode* node)
{
	if (node == NULL) return 0;
	return get_height(node->left_child) - get_height(node->right_child);
}

AvlNode* rebalance(AvlNode** node)
{
	int height_diff = get_height_diff(*node);

	if (height_diff > 1)
	{
		if (get_height_diff((*node)->left_child) > 0)
			*node = rotate_LL(*node);
		else
			*node = rotate_LR(*node);
	}
	else if (height_diff < -1)
	{
		if (get_height_diff((*node)->right_child) < 0)
			*node = rotate_RR(*node);
		else
			*node = rotate_RL(*node);
	}
	return *node;
}

AvlNode* avl_add(AvlNode** root, element new_key)
{
	if (*root == NULL)
	{
		*root = (AvlNode*)malloc(sizeof(AvlNode));

		if (*root == NULL)
		{
			fprintf(stderr, "메모리 할당 에러\n");
			exit(1);
		}
		(*root)->data = new_key;
		(*root)->left_child = (*root)->right_child = NULL;
	}
	else if (strcmp(new_key.word, (*root)->data.word) > 0)
	{
		(*root)->left_child = avl_add(&((*root)->left_child), new_key);
		(*root) = rebalance(root);
	}
	else if (strcmp(new_key.word, (*root)->data.word) < 0)
	{
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);
		(*root) = rebalance(root);
	}
	else
	{
		fprintf(stderr, "중복된 키 에러\n");
		exit(1);
	}
	return *root;
}

AvlNode* avl_search(AvlNode* node, element key)
{
	if (node == NULL) return NULL;
	//printf("%s %s\n ", node->data.word, node->data.mean);
	if (strcmp(key.word, node->data.word) == 0)
		return node;
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

	fp = fopen("data.txt", "r");

	while (!feof(fp))
	{
		fscanf(fp, "%c", &flag);

		if (flag == 'i')
		{
			fscanf(fp, "%s %s", tmp.word, tmp.mean);
			printf("삽입 : %s %s\n", tmp.word, tmp.mean);
			avl_add(&root, tmp);
		}

		if (flag == 's')
		{
			fscanf(fp, "%s", &tmp.word);

			printf("\n< %s의 의미 탐색 >\n", tmp.word);
			strcpy(tmp.mean, "");
			AN = avl_search(root, tmp);
			printf("%s-%s\n", AN->data.word, AN->data.mean);
		}
	}

	printf("\n\n< AVL 트리 출력 >\n");
	display(root, 0);

	printf("\n\n");
	preorder(root);
	fclose(fp);
}