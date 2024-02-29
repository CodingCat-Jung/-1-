#include <stdio.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

//        17
//    15      93
//  05      35  95
//        22

TreeNode n1 = { 05,NULL,NULL };
TreeNode n2 = { 22,NULL,NULL };
TreeNode n3 = { 95,NULL,NULL };
TreeNode n4 = { 15,&n1,NULL };
TreeNode n5 = { 35,&n2,NULL };
TreeNode n6 = { 93,&n5,&n3 };
TreeNode n7 = { 17,&n4,&n6 };

TreeNode* root = &n7;

#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

void push(TreeNode* p)
{
	if (top < SIZE - 1 ) {
		stack[++top] = p;
	}
}

TreeNode* pop()
{
	TreeNode* p = NULL;
	if (top >= 0) {
		p = stack[top--];
	}
	return p;
}

void inorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left) {
			push(root);
		}
		
		root = pop();

		if (!root) break;

		printf("[%d] ", root->data);
		root = root->right;
	}
}

int main() {

	printf("중위 순회 = ");
	inorder_iter(root);
	printf("\n");

	return 0;
}