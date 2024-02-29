#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// �л� ���� ����ü
typedef struct student {
    int number;
    char name[10];
    int math;
    int english;
    int korea;
    int total;
    double aver;
}stu;

// ���� ����Ʈ ����ü
typedef struct ListNODE {
    stu data;
    struct ListNODE* link;
}node;

// ���ο� ��� ���� �Լ�
node* createNode(stu data)
{
    node* newNode;
    newNode = (node*)malloc(sizeof(stu));

    newNode->data = data;
    newNode->link = NULL;

    return newNode;
}

// ��� ���� �Լ�
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
    printf("| ��  �� | �̸� |����|����|����| ���� | ��� |\n");
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
    printf("| ��  �� | �̸� |����|����|����| ���� | ��� |\n");
    printf("|--------------------------------------------|\n");

    while (p != NULL) {
        if (p->data.number == sNum) {
            printf("|%d|%s| %d | %d | %d | %d  | %.2f|\n", p->data.number, p->data.name, p->data.math, p->data.english, p->data.korea,
                p->data.total, p->data.aver);
            break;  // �ش� �л� ������ ����ϰ� ���� ����
        }
        p = p->link;
    }
    printf("|--------------------------------------------|\n");
}

void printOrder()
{
    printf("<<���� ���� ���α׷�>>\n");
    printf(">> -0- ����\n");
    printf(">> -1- �˻�\n");
    printf(">> -2- ���\n");
    printf(">> -3- �߰�\n");
}

int main() {

    FILE* fp = NULL;
    stu tmp;
    node* head = NULL;

    // 1. ������ ������ ��� ������ ���� ���ö����� �ݺ�
    fp = fopen("data.txt", "r");
    if (fp == NULL) printf("FILE not found\n");

      //  1-1. �ӽ� ����ü ������ ���Ͽ��� ���� ���� ����
      //  1-2. �հ�� ��� ����ؼ� �ӽ� ����ü�� ����
    while (!feof(fp)) {
        fscanf(fp, "%d %s %d %d %d", &tmp.number, tmp.name, &tmp.math, &tmp.english, &tmp.korea);
        tmp.total = tmp.math + tmp.english + tmp.korea;
        tmp.aver = tmp.total / 3.0;
        insertNode(&head, createNode(tmp));// insertNode(head, ListNode *newNode)

    }
    
    // 2. �ӽ� ����ü ũ�⸸ŭ �������� �޸� �Ҵ� �޴´�
    //  createNode(tmp);
    // 3. ���Ḯ��Ʈ �Լ����� �����ؼ� ���� �߰��Ѵ�

    // 4, ���Ḯ��Ʈ�� �����ؼ� ����Ʈ ��带 �ϳ��� ����Ѵ�.
    display(head);

    //////////////////////////////////////////////////////////////////////////////
    // 2������

    int sel; // ���� �ɼ� �Է� ���� ����
    int sNum; // �˻� �� �й� �Է� ���� ����

    while (1) {
        printOrder();
        scanf("%d", &sel);

        switch (sel) {
        case 0:
            // ���α׷� ����
            exit(0);
        case 1:
            // �й����� �˻�
            printf("�˻��� �й� : ");
            scanf("%d", &sNum);
            node* result = search(head, sNum);
            if (result != NULL) {
                printf("�˻� ���:\n");
                displayStudent(head, sNum);  // �˻��� �л� ������ ���
            }
            else {
                printf("�ش� �й��� �л��� ã�� �� �����ϴ�.\n");
            }
            break;
        case 2:
            // ��� ���
            display(head);
            break;
        case 3:
            // ���ο� �л� ���� �߰�
            printf("�߰��� �л� �̸� : ");
            scanf("%s", tmp.name);
            printf("�й� : ");
            scanf("%d", &tmp.number);
            printf("���� ���� : ");
            scanf("%d", &tmp.math);
            printf("���� ���� : ");
            scanf("%d", &tmp.english);
            printf("���� ���� : ");
            scanf("%d", &tmp.korea);
            tmp.total = tmp.math + tmp.english + tmp.korea;
            tmp.aver = tmp.total / 3.0;
            insertNode(&head, createNode(tmp));
            printf("�л� ������ �߰��Ǿ����ϴ�.\n");
            break;
        default:
            printf("�ùٸ��� ���� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    }

    // 1. ��ɾ� ȭ�� ���
    // 2. ����� ��� �Է�(�߰�, ���, �˻�, ���� - i,d,s,q)
    // 3. swith �б� ��ƾ �߰�
    // 4. �Է� i ����� ���, �й�, �̸�, �� ���� �Է� �޾Ƽ� ����ü�� ����
    // 5. ���� ��ƾ�� ���Ͽ��� ������ �о ���Ḯ��Ʈ�� �����ϴ� �κа� ����

    // 5. �����ִ� ������ �ݾ��ش�. �޸𸮵� ����
    fclose(fp);

    return 0;
}