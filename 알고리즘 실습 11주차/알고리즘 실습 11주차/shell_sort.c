// �� ���� shell_sort ���α׷�
// ������ ���Ͽ� �л��� ������ �̸�, �й�, ��ȭ��ȣ�� ����Ǿ� �ִµ�
// �̸� �о�� �й� ������ �������� ����
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name[20];
	int student_no;
	char phone_no[20];
}element;

void inc_insertion_sort(element list[], int first, int last, int gap)
{
	int i, j;
	element key;
	
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key.student_no > list[j].student_no; j = j - gap) {
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}

// gap ��ŭ ������ ��ҵ��� ���� ����
// ������ ������ first���� last
void shell_sort(element list[], int n)
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++) {
			inc_insertion_sort(list, i, n - 1, gap);
		}
	}
}

int main() {
	FILE* fp;
	fp = fopen("data4.txt", "r");

	int count = 0;
	element temp;

	element* list;

	while (!feof(fp)) {
		fscanf(fp, "%s %d %s", temp.name, &temp.student_no, temp.phone_no);
		count++;
	}

	list = (element*)malloc(sizeof(element) * count);
	rewind(fp);

	count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s %d %s", list[count].name, &list[count].student_no, list[count].phone_no);
		count++;
	}

	printf("< ���� �� >\n");
	for (int i = 0; i < count; i++) {
		printf("%s %d %s\n", list[i].name, list[i].student_no, list[i].phone_no);
	}

	printf("\n\n");

	printf("< ���� �� >\n");
	shell_sort(list, count);
	for (int i = 0; i < count; i++) {
		printf("%s %d %s\n", list[i].name, list[i].student_no, list[i].phone_no);
	}

	free(list);
	fclose(fp);
	return 0;
}