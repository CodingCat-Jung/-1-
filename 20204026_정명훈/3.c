// 20204026 3��

// data3.txt�� �л��� ���� �̸� �й� ����� ����Ǿ� �ִ�.
// �й� ���� ������ / �̸��� �������� / ������ ��������


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �л� ���� ����ü
typedef struct {
	char name[20];
	int student_no;
	int score;
}element;

void print_list(element list[], int n)
{
	printf("----------------------------\n");
	printf("|  �̸�  |   �й�   |����|\n");
	printf("----------------------------\n");
	for (int i = 0; i < n; i++) {
		printf("| %-7s| %-8d | %-2d |\n", list[i].name, list[i].student_no, list[i].score);
	}
	printf("----------------------------\n\n");
}

// ���� ���� - �̸� ��
void insertion_sort(element list[], int n)
{
	int i, j;
	element key;

	for (i = 1; i < n; i++) { // i - �� ��° ��Һ��� ����

		key = list[i]; // ���� ��� list[i]�� key�� ����

		// �й��� ���Ͽ� ����
		// j - ���� ��� i���� 1���� ��Һ��� �����ؼ� �������� �̵� j--
		for (j = i - 1; j >= 0 && strcmp(list[j].name, list[j + 1].name) < 0; j--) {
			list[j + 1] = list[j]; // ���������� �̵���Ŵ list[i] = list[i-1]
		}

		// ���ĵ� ��ġ�� ���� ��� ����
		list[j + 1] = key; // list[i] = key
	}
}

// �� ���� - �й� ��
#define SWAP(x,y,t)((t)=(x),(x)=(y),(y)=(t))

int count = 0; // ������ ���� ������ ���� ����

// �� ���Ŀ��� ���Ǵ� ���� �Լ�
int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left]; // �Ǻ��� ���� ���� ��ҷ� ����

	do {
		// low�� ���ʺ��� �Ǻ����� ū ���� ã��
		do {
			low++;
		} while (low <= right && list[low] < pivot);

		// high�� �����ʺ��� �Ǻ����� ���� ���� ã��
		do {
			high--;
		} while (high >= left && list[high] > pivot);

		// low�� high�� ���� �������� ���� ���
		if (low < high) {

			// �� ������ ��ȯ
			SWAP(list[low], list[high], temp);


		}
	} while (low < high);

	// low�� high�� ������ ���
	SWAP(list[left], list[high], temp);

	return high;
}

// �� ���� �Լ�
void quick_sort(int list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right); // partition�Լ��� ���� q ����
		quick_sort(list, left, q - 1); // ���� �κ� �迭 �� ����
		quick_sort(list, q + 1, right); // ������ �κ� �迭 �� ����
	}
}

// ���� ���� - ���� ��
void selection_sort(element list[], int n)
{
	int i, j, least;
	element temp;

	for (i = 0; i < n - 1; i++) { // �迭�� ó������ �����ؿ�

		least = i; // ���� ���� ���� ����Ű�� �ε��� - i�� ����

		// i ���� �ε��� i+1���� �����Ͽ� ���� ���� ���� ã��
		for (j = i + 1; j < n; j++) {

			if (list[j].score < list[least].score) {
				least = j; // ���� least���� ���� �� �߰��ϸ� �ֽ�ȭ
			}

		}

		// ���� ���� least ã�� ���� - �ڸ� ��ȯ
		temp = list[i];
		list[i] = list[least];
		list[least] = temp;
	}
}

int main() {
	FILE* fp;
	fp = fopen("data3.txt", "r");
	if (!feof(fp)) {
		printf("���� ���� ����\n");
		return;
	}

	int count = 0; // �л� ���� ī��Ʈ�ϱ� ���� ����

	count = 8;

	char flag;
	element temp;

	element* list; // ���� �迭�� ���� ������

	// �л� �� count��ŭ ���� �Ҵ�
	list = (element*)malloc(sizeof(element) * count);

	rewind(fp);
	count = 0;

	// ���� �б�
	while (!feof(fp))
	{
		fscanf(fp, "%c", &flag);

		// i�� ����
		if (flag == 'i')
		{
			fscanf(fp, "%d %s %d", &list[count].student_no, list[count].name, &list[count].score);
			printf("%d %s %s ���� �Ϸ�\n", list[count].student_no, list[count].name, list[count].score);
			count++;
		}

		char sel[1024];
		int num = 0;

		// p�� ���
		if (flag == 'p')
		{
			fscanf(fp, "%s %d", sel, num);

			// name�� ���
			if (strcmp(sel, "name") == 0)
				insertion_sort(list, num);

			// score�� ���
			else if (strcmp(sel, "score") == 0)
				selection_sort(list, num);

			// number�� ���
			else if (strcmp(sel, "number") == 0)
				quick_sort(list, 0, num - 1);
		}
	}


	fclose(fp);
	return 0;
}