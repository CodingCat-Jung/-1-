#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// 학생 정보 구조체
typedef struct student {
    int number;
    char name[10];
    int math;
    int english;
    int korea;
    int total;
    double aver;
}stu;

// 연결 리스트 구조체
typedef struct ListNODE {
    stu data;
    struct ListNODE* link;
}node;

// 새로운 노드 생성 함수
node* createNode(stu data)
{
    node* newNode;
    newNode = (node*)malloc(sizeof(stu));

    newNode->data = data;
    newNode->link = NULL;

    return newNode;
}

// 노드 삽입 함수
void insertNode(node** phead, node* newData)
{
    if (*phead == NULL) {
        // list empty
        // before : phead
        // after : phead-> newData-> NULL
        newData->link = NULL;
        *phead = newData;
    }

    // before : phead-> oldData-> NULL
    // after : phead-> newData-> oldData-> NULL
    else {
        newData->link = *phead; // newData-> oldData
        *phead = newData; // phead-> newData

    }
}

void display(node* phead)
{
    node* p = phead;

    printf("|--------------------------------------------|\n");
    printf("| 학  번 | 이름 |수학|영어|국어| 총점 | 평균 |\n");
    printf("|--------------------------------------------|\n");

    while (p != NULL) {
        printf("|%d|%s| %d | %d | %d | %d  | %.2f|\n", p->data.number, p->data.name, p->data.math, p->data.english, p->data.korea,
            p->data.total, p->data.aver);
        
        p = p->link;
    }
    printf("|--------------------------------------------|\n");
}

node* search(node* phead, int sNum)
{
    node* p = phead;

    while (p != NULL) {
        if (p->data.number == sNum) {
            return p;
        }
        else
            p = p->link;
    }
    return NULL;
}

void displayStudent(node* phead, int sNum)
{
    node* p = phead;

    printf("|--------------------------------------------|\n");
    printf("| 학  번 | 이름 |수학|영어|국어| 총점 | 평균 |\n");
    printf("|--------------------------------------------|\n");

    while (p != NULL) {
        if (p->data.number == sNum) {
            printf("|%d|%s| %d | %d | %d | %d  | %.2f|\n", p->data.number, p->data.name, p->data.math, p->data.english, p->data.korea,
                p->data.total, p->data.aver);
            break;  // 해당 학생 정보를 출력하고 루프 종료
        }
        p = p->link;
    }
    printf("|--------------------------------------------|\n");
}

void printOrder()
{
    printf("<<성적 관리 프로그램>>\n");
    printf(">> -0- 종료\n");
    printf(">> -1- 검색\n");
    printf(">> -2- 목록\n");
    printf(">> -3- 추가\n");
}

int main() {

    FILE* fp = NULL;
    stu tmp;
    node* head = NULL;

    // 1. 데이터 파일을 열어서 파일의 끝이 나올때까지 반복
    fp = fopen("data.txt", "r");
    if (fp == NULL) printf("FILE not found\n");

      //  1-1. 임시 구조체 변수에 파일에서 읽은 값을 저장
      //  1-2. 합계와 평균 계산해서 임시 구조체에 저장
    while (!feof(fp)) {
        fscanf(fp, "%d %s %d %d %d", &tmp.number, tmp.name, &tmp.math, &tmp.english, &tmp.korea);
        tmp.total = tmp.math + tmp.english + tmp.korea;
        tmp.aver = tmp.total / 3.0;
        insertNode(&head, createNode(tmp));// insertNode(head, ListNode *newNode)

    }
    
    // 2. 임시 구조체 크기만큼 동적으로 메모리 할당 받는다
    //  createNode(tmp);
    // 3. 연결리스트 함수한테 전달해서 노드로 추가한다

    // 4, 연결리스트를 전달해서 리스트 노드를 하나씩 출력한다.
    display(head);

    //////////////////////////////////////////////////////////////////////////////
    // 2번문제

    int sel; // 선택 옵션 입력 받을 변수
    int sNum; // 검색 할 학번 입력 받을 변수

    while (1) {
        printOrder();
        scanf("%d", &sel);

        switch (sel) {
        case 0:
            // 프로그램 종료
            exit(0);
        case 1:
            // 학번으로 검색
            printf("검색할 학번 : ");
            scanf("%d", &sNum);
            node* result = search(head, sNum);
            if (result != NULL) {
                printf("검색 결과:\n");
                displayStudent(head, sNum);  // 검색된 학생 정보만 출력
            }
            else {
                printf("해당 학번의 학생을 찾을 수 없습니다.\n");
            }
            break;
        case 2:
            // 목록 출력
            display(head);
            break;
        case 3:
            // 새로운 학생 정보 추가
            printf("추가할 학생 이름 : ");
            scanf("%s", tmp.name);
            printf("학번 : ");
            scanf("%d", &tmp.number);
            printf("수학 점수 : ");
            scanf("%d", &tmp.math);
            printf("영어 점수 : ");
            scanf("%d", &tmp.english);
            printf("국어 점수 : ");
            scanf("%d", &tmp.korea);
            tmp.total = tmp.math + tmp.english + tmp.korea;
            tmp.aver = tmp.total / 3.0;
            insertNode(&head, createNode(tmp));
            printf("학생 정보가 추가되었습니다.\n");
            break;
        default:
            printf("올바르지 않은 입력입니다. 다시 시도하세요.\n");
            break;
        }
    }

    // 1. 명령어 화면 출력
    // 2. 사용자 명령 입력(추가, 출력, 검색, 종료 - i,d,s,q)
    // 3. swith 분기 루틴 추가
    // 4. 입력 i 명령인 경우, 학번, 이름, 각 점수 입력 받아서 구조체에 저장
    // 5. 이후 루틴은 파일에서 데이터 읽어서 연결리스트에 저장하는 부분과 동일

    // 5. 열러있던 파일을 닫아준다. 메모리도 삭제
    fclose(fp);

    return 0;
}