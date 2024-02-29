// data1.txt에 학생의 정보 이름 학번 등수로 저장되어 있다.
// 등수 순은 선택정렬 / 학번은 삽입정렬 / 이름은 버블정렬
// 동적 할당을 이용하여 데이터를 저장
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name[20];
	int student_no;
	int rank;
}element;

void print_list(element list[], int n)
{
	printf("----------------------------\n");
	printf("|  이름  |   학번   |등수|\n");
	printf("----------------------------\n");
	for (int i = 0; i < n; i++) {
		printf("| %-7s| %-8d | %-2d |\n", list[i].name, list[i].student_no, list[i].rank);
	}
	printf("----------------------------\n\n");
}

// 버블 정렬 - 이름 순
#define SWAP(x,y,t)((t)=(x),(x)=(y),(y)=(t))
void bubble_sort(element list[], int n)
{
	int i, j;
	element temp;

	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (strcmp(list[j].name, list[j + 1].name) > 0) {
				SWAP(list[j], list[j + 1], temp);
			}
		}
	}
}

// 삽입 정렬 - 학번 순
void insertion_sort(element list[], int n)
{
	int i, j;
	element key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j].student_no > key.student_no; j--) {
			list[j + 1] = list[j];
		}
		list[j + 1] = key;
	}
}

// 선택 정렬 - 등수 순
void selection_sort(element list[], int n)
{
	int i, j, least;
	element temp;

	for (i = 0; i < n - 1; i++) {
		least = i;

		for (j = i + 1; j < n; j++) {
			if (list[j].rank < list[least].rank) {
				least = j;
			}
		}

		// 가장 작은 least 찾은 상태
		temp = list[i];
		list[i] = list[least];
		list[least] = temp;
	}
}

int main() {
	FILE* fp;
	fp = fopen("data3.txt", "r");

	int count = 0;
	element temp;

	element* list;

	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", temp.name, &temp.student_no, &temp.rank);
		count++;
	}

	list = (element*)malloc(sizeof(element) * count);
	rewind(fp);

	count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", list[count].name, &list[count].student_no, &list[count].rank);
		count++;
	}

	printf("< 정렬전 데이터 >\n");
	print_list(list, count);

	printf("< 등수 정렬후 데이터 >\n");
	selection_sort(list, count);
	print_list(list, count);

	printf("< 학번 정렬 후 데이터 >\n");
	insertion_sort(list, count);
	print_list(list, count);

	printf("< 이름 정렬 후 데이터 >\n");
	bubble_sort(list, count);
	print_list(list, count);

	free(list);
	fclose(fp);
	return 0;
}