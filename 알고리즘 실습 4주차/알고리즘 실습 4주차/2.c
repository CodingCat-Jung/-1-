// ���� 2. ���� ���� Ʈ�� ����
// data.txt���� ������ �̷���� ������ �о�� ���� Ʈ���� �����ϰ�, ������ Ʈ���� ���� ���� Ʈ������ ����

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
}TreeNode;

// insert_node �̿��� Ʈ�� ����
void insert_node(TreeNode** root, element key)
{
	TreeNode* p, * t; //����Ž��Ʈ�� Ž���� ���� ���� ������
	TreeNode* n; //���� �߰��� ���
	t = *root;
	p = NULL;


	// key������ �Ǵ�
	while (t != NULL) {
		if (key == t->data) //�̹� �����ϴ� �ܾ�
			return;

		p = t; // �ڽĿ��� �������� 
		if (key < p->data) // 0���� ������ ����
			t = p->left;
		else
			t = p->right;
	}


	//�� ���������� Ʈ���� ���� ���ο� �ܾ�� Ȯ��
	n = (TreeNode*)malloc(sizeof(TreeNode));
	//����ڵ�
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

// Ž�� Ʈ�� ���� ����� ������ ���
// ������ ����Ʈ���� ���Ͽ� ��ȯ ȣ���� ����, ��ȯ�Ǵ� ���� 1�� ���ؼ� ��ȯ
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

	printf("������ȸ ���: ");
	preorder(root);


	//2^(����Ʈ������ -1) == �ܸ����
	if (pow(get_height(root) - 1) == get_leaf_count(root))
		printf("\n���� ���� Ž��Ʈ��\n");
	else
		printf("\n ���� ���� Ž��Ʈ�� �ƴ�\n");

	fclose(fp);

	return 0;
}
