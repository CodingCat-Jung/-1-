#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

// 데이터 필드
typedef struct {
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
}element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}TreeNode;

// e1 < e2 이면 -1 반환
// e1 == e2 이면 0 반환
// e1 > e2 이면 1 반환
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

		if (compare(key, t->key) == 0) // 이미 중복된 데이터가 있음
			return;

		p = t;

		if (compare(key, t->key) < 0)
			t = t->left;
		else
			t = t->right;
	}

	// while 루프가 끝난 시점은 중복 데이터가 없고 마지막 단말노드까지 검색이 완료됐음
	// 신규 트리 추가
	n = (TreeNode*)malloc(sizeof(TreeNode));
	// 방어코드
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

void display(TreeNode* root) // 정렬 상태로 출력하기 위해 inorder 구현
{
	if (root != NULL) {
		display(root->left);
		printf("트리노드 ( %s : %s )", root->key.word, root->key.meaning);
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
		// key값이 일치하지 않음
		p = t;
		t = (compare(key, t->key) < 0) ? t->left : t->right;

	}

	// case1. t == NULL - 검색 실패, 삭제하려는 key는 존재x
	if (t == NULL) {
		printf("삭제하려는 데이터가 없습니다.\n");
		return;
	}

	// case2. key가 트리에 존재하는 경우

		// case2-1. t의 child node가 없는 경우(leaf node)
	if (t->left == NULL && t->right == NULL) {
		// 2-1-1. parent node가 있는 경우
		if (p != NULL) {
			// case2-1-1-1. t가 p의 왼쪽 child인 경우
			if (p->left == t) p->left == NULL;

			// case2-1-1-2. t가 p의 오른쪽 child인 경우
			else p->right == NULL;

		}

		// 2-1-2. parent node가 없는 경우 - > 트리에 유일한 노드가 t인 경우
		else {
			*root == NULL;
		}
	}

	// case2-2. t의 child node가 한 개만 있는 경우
	else if (t->left == NULL || t->right == NULL) {
		// 손주 노드의 포인터를 얻는다
		child = (t->left != NULL) ? t->left : t->right;

		// case2-2-1. parent node가 있는 경우
		if (p != NULL) {
			// case2-2-1-1. t가 parent의 왼쪽 자식인 경우
			if (p->left == t)
				p->left = child;
			// t가 parent node의 오른쪽 자식인 경우
			else
				p->right = child;
		}
		// case2-2-2. parent node가 없는 경우
		else {
			*root = child;
		}
	}

	// case2-3. t의 left,right가 모두 존재하는 경우
	else {
		// 오른쪽 서브트리에서 후계자 선정
		succ_p = t;
		succ = t->right;

		// 오른쪽 서브트리에서 가장 작은 노드를 찾음
		// 오른쪽 서브트리에서 가장 작은 값은 가장 왼쪽 끝에 있는 노드
		// 이진 탐색 트리이기 때문에 가능한 조건
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

	//fp 방어코드

	while (!feof(fp)) {
		fscanf(fp, "%c", &command);

		switch (command) {
		case'i':
			//insert_node;
			fscanf(fp, " %s %s", e.word, e.meaning);
			insert_node(&root, e);
			printf("단어 %s를 저장완료\n", e.word);
			break;
		case'd':
			//delete_node;
			fscanf(fp, "%s", e.word);
			strcpy(e.meaning, "");
			delete_node(&root, e);
			printf("단어 %s 삭제 완료\n", e.word);
			break;
		case's':
			//search_node
			fscanf(fp, "%s", e.word);
			strcpy(e.meaning, "");
			tmp = search_node(root, e);
			if (tmp != NULL) { // 사전에 단어가 있으면 검색 성공
				printf("단어 %s의 의미는 %s입니다.\n", tmp->key.word, tmp->key.meaning);
			}
			else {  // 사전에 해당 단어가 없다
				printf("\n단어 %s는 사전에 없습니다.\n", e.word);
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
	//child case 3가지 delete
}