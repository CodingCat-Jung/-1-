// 20204026 2번

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AVL 트리 노드에 들어갈 데이터 구조체
typedef struct {
	char word[20];
	char mean[20];
}element;

// AVL 트리 노드 구조체
typedef struct AvlNode {
	element data;
	struct AvlNode* left_child, * right_child;
}AvlNode;

// AVL 트리 루트 노드 선언
AvlNode* root;

// 왼쪽으로 회전하는 LL함수
AvlNode* rotate_LL(AvlNode* parent)
{
	AvlNode* child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}

// 오른쪽으로 회전하는 RR함수
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

// 두 정수 중 큰 값을 반환하는 함수
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

// 노드의 높이를 구하는 함수
int get_height(AvlNode* node)
{
	int height = 0;

	if (node != NULL)
		height = 1 + maxs(get_height(node->left_child), get_height(node->right_child));
	return height;
}

// 노드의 높이 차이를 구하는 함수
int get_height_diff(AvlNode* node)
{
	if (node == NULL) return 0;

	return get_height(node->left_child) - get_height(node->right_child);
}

// AVL 트리를 재균형하는 함수
AvlNode* rebalance(AvlNode** node)
{
	// 높이 차를 구한다
	int height_diff = get_height_diff(*node);

	// 높이 차이가 1보다 크면
	if (height_diff > 1)
	{
		if (get_height_diff((*node)->left_child) > 0)
			*node = rotate_LL(*node);
		else
			*node = rotate_LR(*node);
	}

	// 높이 차이가 -1보다 작으면
	else if (height_diff < -1)
	{
		if (get_height_diff((*node)->right_child) < 0)
			*node = rotate_RR(*node);
		else
			*node = rotate_RL(*node);
	}

	return *node;
}

// AVL 트리에 노드를 추가하는 함수
AvlNode* avl_add(AvlNode** root, element new_key)
{
	// 루트 노드가 비어있으면
	if (*root == NULL)
	{
		*root = (AvlNode*)malloc(sizeof(AvlNode));

		if (*root == NULL) // 할당 실패시 에러
		{
			fprintf(stderr, "메모리 할당 에러\n");
			exit(1);
		}

		// 노드 데이터 설정하고 자식 노드 초기화
		(*root)->data = new_key;
		(*root)->left_child = (*root)->right_child = NULL;
	}

	// 새로운 키가 현재 노드의 키보다 크면
	else if (strcmp(new_key.word, (*root)->data.word) > 0)
	{
		// 왼쪽 서브트리에 추가
		(*root)->left_child = avl_add(&((*root)->left_child), new_key);
		(*root) = rebalance(root);
	}

	// 새로운 키가 현재 노드의 키보다 작으면
	else if (strcmp(new_key.word, (*root)->data.word) < 0)
	{
		// 오른쪽 서브트리에 추가
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

// AVL 트리에서 키를 탐색하는 함수
AvlNode* avl_search(AvlNode* node, element key)
{
	if (node == NULL) return NULL;
	//printf("%s %s\n ", node->data.word, node->data.mean);

	// 현재 노드의 키와 찾는 키가 같으면 현재 노드 반환
	if (strcmp(key.word, node->data.word) == 0)
		return node;

	// 찾는 키가 현재 노드의 키보다 크면 왼쪽 서브트리에서 탐색
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

// AVL 트리를 전위 순회하며 출력
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
			printf("삽입 : %s %s\n", tmp.word, tmp.mean);
			avl_add(&root, tmp);
		}

		if (flag == 's')
		{
			fscanf(fp, "%s", &tmp.word);

			printf("\n< %s의 의미 탐색 >\n", tmp.word);
			strcpy(tmp.mean, ""); // 빈 뜻으로 초기화
			AN = avl_search(root, tmp);
			printf("%s은 영어로 %s입니다.\n", AN->data.word, AN->data.mean);
		}
	}

	printf("\n\n< AVL 트리 출력 >\n");
	display(root, 0);

	printf("\n\n");
	printf("< AVL 트리 전위순회 출력 결과 >\n");
	preorder(root);
	fclose(fp);
}