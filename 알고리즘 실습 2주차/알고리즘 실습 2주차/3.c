#include <stdio.h>
#include <stdlib.h>

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

#define MAX_QUEUE_SIZE 100
typedef TreeNode* element;

typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다.\n");

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다.\n");

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode* ptr)
{
	QueueType q;

	init_queue(&q);

	if (ptr == NULL) return;

	enqueue(&q, ptr);

	while (!is_empty(&q)) {

		ptr = dequeue(&q);
		printf(" [%d] ", ptr->data);

		if (ptr->left)
			enqueue(&q, ptr->left);

		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}

int main() {

	printf("레벨 순회 = ");
	level_order(root);
	printf("\n");

	return 0;
}