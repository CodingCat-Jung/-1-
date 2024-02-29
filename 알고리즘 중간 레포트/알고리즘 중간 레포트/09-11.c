#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ����ü ����
typedef struct Task {
    int priority;             // ������ �켱����
    char description[100];    // ������ ����
} Task;

// �켱���� ť ����ü ����
typedef struct PriorityQueue {
    Task* tasks;    // ������ ������ �迭
    int maxSize;    // ť�� �ִ� ũ��
    int size;       // ���� ť�� ����� ���� ����
} PriorityQueue;

// �켱���� ť �ʱ�ȭ �Լ�
PriorityQueue* createPriorityQueue(int maxSize) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->tasks = (Task*)malloc(sizeof(Task) * maxSize);
    queue->maxSize = maxSize;
    queue->size = 0;    // �ʱ� ť ũ�⸦ 0���� ����
    return queue;
}

// ���� �߰� �Լ�
void enqueue(PriorityQueue* queue, int priority, const char* description) {
    if (queue->size >= queue->maxSize) {  // ť�� ���� �� ��� ���� ó��
        printf("Queue is full.\n");
        return;
    }

    Task newTask;
    newTask.priority = priority;
    strcpy(newTask.description, description);

    // ���ο� ������ ť�� �߰��ϰ� �켱������ ���� ����
    int index = queue->size;
    queue->tasks[index] = newTask;
    queue->size++;

    // ���Ե� ������ �켱������ ���� ��迭
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (queue->tasks[index].priority < queue->tasks[parentIndex].priority) {
            // �θ�� �ڽ��� �켱������ �ڹٲ�� ��ȯ
            Task temp = queue->tasks[index];
            queue->tasks[index] = queue->tasks[parentIndex];
            queue->tasks[parentIndex] = temp;
            index = parentIndex;
        }
        else break;  // �θ�� �켱������ �ٲ��� ������ ����
    }
}

// ���� ���� �켱������ ������ �����ϰ� ����ϴ� �Լ�
void dequeue(PriorityQueue* queue) {
    if (queue->size == 0) {  // ť�� ��� �ִ� ��� ���� ó��
        printf("Queue is empty.\n");
        return;
    }

    Task highestPriorityTask = queue->tasks[0];
    printf("�켱����: %d, ����: %s\n", highestPriorityTask.priority, highestPriorityTask.description);

    // ť���� ������ �����ϰ� ������ ������ �ٽ� ����
    queue->size--;
    queue->tasks[0] = queue->tasks[queue->size];

    int index = 0;
    while (1) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int minIndex = index;

        if (leftChildIndex < queue->size && queue->tasks[leftChildIndex].priority < queue->tasks[minIndex].priority) {
            minIndex = leftChildIndex;
        }

        if (rightChildIndex < queue->size && queue->tasks[rightChildIndex].priority < queue->tasks[minIndex].priority) {
            minIndex = rightChildIndex;
        }

        if (minIndex != index) {
            // �ڽ� �߿��� �켱������ ���� �Ͱ� ��ȯ
            Task temp = queue->tasks[index];
            queue->tasks[index] = queue->tasks[minIndex];
            queue->tasks[minIndex] = temp;
            index = minIndex;
        }
        else {
            break;  // �ڽİ� �켱������ �ٲ��� ������ ����
        }
    }
}

// �켱���� ť �޸� ���� �Լ�
void destroyPriorityQueue(PriorityQueue* queue) {
    free(queue->tasks);
    free(queue);
}

int main() {
    int maxSize = 10;
    PriorityQueue* queue = createPriorityQueue(maxSize);

    char choice;
    int priority;
    char description[100];

    while (1) {
        printf("����(i), ����(d), ����(q): ");
        scanf(" %c", &choice);
        switch (choice) {
        case 'i':
            printf("�켱����: ");
            scanf("%d", &priority);
            printf("����: ");
            scanf("%s", description);
            enqueue(queue, priority, description);
            break;
        case 'd':
            dequeue(queue);
            break;
        case 'q':
            // ����
            destroyPriorityQueue(queue);
            return 0;
        default:
            printf("�ٽ� �Է��ϼ���.\n");
        }
    }
}