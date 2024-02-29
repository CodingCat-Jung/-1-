#include <stdio.h>
#include <stdlib.h>

// ���� Ʈ�� ��� ����ü ����
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// ���� Ʈ���� ���̸� ��ȯ�ϴ� �Լ�
int height(struct TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    int left_height = height(node->left);    // ���� ����Ʈ���� ���� ���
    int right_height = height(node->right);  // ������ ����Ʈ���� ���� ���
    return (left_height > right_height) ? left_height + 1 : right_height + 1; // �� ���� ����Ʈ���� ���̿� 1�� ����
}

// ���� Ʈ���� ���� ���θ� �˻��ϴ� �Լ�
int isBalanced(struct TreeNode* root) {
    if (root == NULL) {
        return 1; // �� Ʈ���� ���� Ʈ���Դϴ�.
    }
    int left_height = height(root->left);    // ���� ����Ʈ���� ���� ���
    int right_height = height(root->right);  // ������ ����Ʈ���� ���� ���

    // ���� ����Ʈ���� ������ ����Ʈ���� ���� ���̰� 1 �����̸� ���� Ʈ���Դϴ�.
    if (abs(left_height - right_height) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return 1;
    }

    // �׷��� ������ ���� Ʈ���� �ƴմϴ�.
    return 0;
}

// ���� Ʈ�� ��� ���� �Լ�
struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {
    // ���� Ʈ�� ����
    struct TreeNode* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(2);
    root->left->left = newNode(3);
    root->left->right = newNode(3);

    //root->left->right->left = newNode(4);

    // ���� Ʈ�� �˻�
    if (isBalanced(root)) {
        printf("���� Ʈ���� ���� Ʈ���Դϴ�.\n");
    }
    else {
        printf("���� Ʈ���� ���� Ʈ���� �ƴմϴ�.\n");
    }

    return 0;
}