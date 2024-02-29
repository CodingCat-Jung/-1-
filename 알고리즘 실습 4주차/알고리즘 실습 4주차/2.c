// 문제 2. 완전 이진 트리 검증
// data.txt에서 정수로 이루어진 정보를 읽어와 이진 트리를 생성하고, 생성된 트리가 완전 이진 트리인지 검증

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
}TreeNode;

// insert_node 이용해 트리 생성
void insert_node(TreeNode** root, element key)
{
	TreeNode* p, * t; //이진탐색트리 탐색을 위한 보조 포인터
	TreeNode* n; //새로 추가할 노드
	t = *root;
	p = NULL;


	// key값으로 판단
	while (t != NULL) {
		if (key == t->data) //이미 존재하는 단어
			return;

		p = t; // 자식에게 가기전에 
		if (key < p->data) // 0보다 작으면 왼쪽
			t = p->left;
		else
			t = p->right;
	}


	//이 시점에서는 트리에 없는 새로운 단어로 확인
	n = (TreeNode*)malloc(sizeof(TreeNode));
	//방어코드
	if (n == NULL)
		return;


	n->data = key;
	n->left = n->right = NULL;

	if (p != NULL)
		if (key < p->data)
			p->left = n;
		else
			p->right = n;
	else
		*root = n;
}

void preorder(TreeNode* root)
{
	if (root) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

int MAX(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

// 탐색 트리 안의 노드의 개수를 계산
// 각각의 서브트리에 대하여 순환 호출한 다음, 반환되는 값에 1을 더해서 반환
int get_node_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);

	return count;
}


int get_leaf_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL)
	{
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_leaf_count(node->left) + get_leaf_count(node->right);

	}
	return count;
}

//2^a 
int pow(int a)
{
	int i, result = 1;

	for (i = 0; i < a; i++)
		result *= 2;

	return result;

}

int get_height(TreeNode* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + MAX(get_height(node->left), get_height(node->right));

	return height;
}

int main(void)
{
	FILE* fp = NULL;
	element e;
	TreeNode* root = NULL;

	fp = fopen("data2.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%d", &e);

		insert_node(&root, e);
		printf("inserted %d\n", e);

	}

	printf("전위순회 결과: ");
	preorder(root);


	//2^(이진트리높이 -1) == 단말노드
	if (pow(get_height(root) - 1) == get_leaf_count(root))
		printf("\n완전 이진 탐색트리\n");
	else
		printf("\n 완전 이진 탐색트리 아님\n");

	fclose(fp);

	return 0;
}
