#include <stdio.h>
#include <stdlib.h>

// 이진 트리 노드 구조체 정의
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 이진 트리의 높이를 반환하는 함수
int height(struct TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    int left_height = height(node->left);    // 왼쪽 서브트리의 높이 계산
    int right_height = height(node->right);  // 오른쪽 서브트리의 높이 계산
    return (left_height > right_height) ? left_height + 1 : right_height + 1; // 더 높은 서브트리의 높이에 1을 더함
}

// 이진 트리의 균형 여부를 검사하는 함수
int isBalanced(struct TreeNode* root) {
    if (root == NULL) {
        return 1; // 빈 트리는 균형 트리입니다.
    }
    int left_height = height(root->left);    // 왼쪽 서브트리의 높이 계산
    int right_height = height(root->right);  // 오른쪽 서브트리의 높이 계산

    // 왼쪽 서브트리와 오른쪽 서브트리의 높이 차이가 1 이하이면 균형 트리입니다.
    if (abs(left_height - right_height) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return 1;
    }

    // 그렇지 않으면 균형 트리가 아닙니다.
    return 0;
}

// 이진 트리 노드 생성 함수
struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {
    // 이진 트리 생성
    struct TreeNode* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(2);
    root->left->left = newNode(3);
    root->left->right = newNode(3);

    //root->left->right->left = newNode(4);

    // 균형 트리 검사
    if (isBalanced(root)) {
        printf("이진 트리는 균형 트리입니다.\n");
    }
    else {
        printf("이진 트리는 균형 트리가 아닙니다.\n");
    }

    return 0;
}