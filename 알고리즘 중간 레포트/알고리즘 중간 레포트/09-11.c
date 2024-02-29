#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 할일 구조체 정의
typedef struct Task {
    int priority;             // 할일의 우선순위
    char description[100];    // 할일의 설명
} Task;

// 우선순위 큐 구조체 정의
typedef struct PriorityQueue {
    Task* tasks;    // 할일을 저장할 배열
    int maxSize;    // 큐의 최대 크기
    int size;       // 현재 큐에 저장된 할일 개수
} PriorityQueue;

// 우선순위 큐 초기화 함수
PriorityQueue* createPriorityQueue(int maxSize) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->tasks = (Task*)malloc(sizeof(Task) * maxSize);
    queue->maxSize = maxSize;
    queue->size = 0;    // 초기 큐 크기를 0으로 설정
    return queue;
}

// 할일 추가 함수
void enqueue(PriorityQueue* queue, int priority, const char* description) {
    if (queue->size >= queue->maxSize) {  // 큐가 가득 찬 경우 예외 처리
        printf("Queue is full.\n");
        return;
    }

    Task newTask;
    newTask.priority = priority;
    strcpy(newTask.description, description);

    // 새로운 할일을 큐에 추가하고 우선순위에 따라 정렬
    int index = queue->size;
    queue->tasks[index] = newTask;
    queue->size++;

    // 삽입된 할일을 우선순위에 따라 재배열
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (queue->tasks[index].priority < queue->tasks[parentIndex].priority) {
            // 부모와 자식의 우선순위가 뒤바뀌면 교환
            Task temp = queue->tasks[index];
            queue->tasks[index] = queue->tasks[parentIndex];
            queue->tasks[parentIndex] = temp;
            index = parentIndex;
        }
        else break;  // 부모와 우선순위가 바뀌지 않으면 종료
    }
}

// 가장 높은 우선순위의 할일을 추출하고 출력하는 함수
void dequeue(PriorityQueue* queue) {
    if (queue->size == 0) {  // 큐가 비어 있는 경우 예외 처리
        printf("Queue is empty.\n");
        return;
    }

    Task highestPriorityTask = queue->tasks[0];
    printf("우선순위: %d, 할일: %s\n", highestPriorityTask.priority, highestPriorityTask.description);

    // 큐에서 할일을 추출하고 나머지 할일을 다시 정렬
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
            // 자식 중에서 우선순위가 높은 것과 교환
            Task temp = queue->tasks[index];
            queue->tasks[index] = queue->tasks[minIndex];
            queue->tasks[minIndex] = temp;
            index = minIndex;
        }
        else {
            break;  // 자식과 우선순위가 바뀌지 않으면 종료
        }
    }
}

// 우선순위 큐 메모리 해제 함수
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
        printf("삽입(i), 삭제(d), 종료(q): ");
        scanf(" %c", &choice);
        switch (choice) {
        case 'i':
            printf("우선순위: ");
            scanf("%d", &priority);
            printf("할일: ");
            scanf("%s", description);
            enqueue(queue, priority, description);
            break;
        case 'd':
            dequeue(queue);
            break;
        case 'q':
            // 종료
            destroyPriorityQueue(queue);
            return 0;
        default:
            printf("다시 입력하세요.\n");
        }
    }
}