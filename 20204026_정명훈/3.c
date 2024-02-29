// 20204026 3번

// data3.txt에 학생의 정보 이름 학번 등수로 저장되어 있다.
// 학번 순은 퀵정렬 / 이름은 삽입정렬 / 총점은 선택정렬


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생 정보 구조체
typedef struct {
	char name[20];
	int student_no;
	int score;
}element;

void print_list(element list[], int n)
{
	printf("----------------------------\n");
	printf("|  이름  |   학번   |총점|\n");
	printf("----------------------------\n");
	for (int i = 0; i < n; i++) {
		printf("| %-7s| %-8d | %-2d |\n", list[i].name, list[i].student_no, list[i].score);
	}
	printf("----------------------------\n\n");
}

// 삽입 정렬 - 이름 순
void insertion_sort(element list[], int n)
{
	int i, j;
	element key;

	for (i = 1; i < n; i++) { // i - 두 번째 요소부터 시작

		key = list[i]; // 현재 요소 list[i]를 key에 저장

		// 학번을 비교하여 정렬
		// j - 현재 요소 i보다 1작은 요소부터 시작해서 왼쪽으로 이동 j--
		for (j = i - 1; j >= 0 && strcmp(list[j].name, list[j + 1].name) < 0; j--) {
			list[j + 1] = list[j]; // 오른쪽으로 이동시킴 list[i] = list[i-1]
		}

		// 정렬된 위치에 현재 요소 삽입
		list[j + 1] = key; // list[i] = key
	}
}

// 퀵 정렬 - 학번 순
#define SWAP(x,y,t)((t)=(x),(x)=(y),(y)=(t))

int count = 0; // 데이터 개수 저장할 전역 변수

// 퀵 정렬에서 사용되는 분할 함수
int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left]; // 피봇은 가장 왼쪽 요소로 선택

	do {
		// low는 왼쪽부터 피봇보다 큰 값을 찾음
		do {
			low++;
		} while (low <= right && list[low] < pivot);

		// high는 오른쪽부터 피봇보다 작은 값을 찾음
		do {
			high--;
		} while (high >= left && list[high] > pivot);

		// low와 high가 아직 교차하지 않은 경우
		if (low < high) {

			// 두 데이터 교환
			SWAP(list[low], list[high], temp);


		}
	} while (low < high);

	// low와 high가 교차한 경우
	SWAP(list[left], list[high], temp);

	return high;
}

// 퀵 정렬 함수
void quick_sort(int list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right); // partition함수를 통해 q 구함
		quick_sort(list, left, q - 1); // 왼쪽 부분 배열 퀵 정렬
		quick_sort(list, q + 1, right); // 오른쪽 부분 배열 퀵 정렬
	}
}

// 선택 정렬 - 총점 순
void selection_sort(element list[], int n)
{
	int i, j, least;
	element temp;

	for (i = 0; i < n - 1; i++) { // 배열의 처음부터 시작해여

		least = i; // 가장 작은 값을 가리키는 인덱스 - i로 설정

		// i 다음 인덱스 i+1부터 시작하여 가장 작은 값을 찾음
		for (j = i + 1; j < n; j++) {

			if (list[j].score < list[least].score) {
				least = j; // 현재 least보다 작은 값 발견하면 최신화
			}

		}

		// 가장 작은 least 찾은 상태 - 자리 교환
		temp = list[i];
		list[i] = list[least];
		list[least] = temp;
	}
}

int main() {
	FILE* fp;
	fp = fopen("data3.txt", "r");
	if (!feof(fp)) {
		printf("파일 오픈 실패\n");
		return;
	}

	int count = 0; // 학생 수를 카운트하기 위한 변수

	count = 8;

	char flag;
	element temp;

	element* list; // 동적 배열을 위한 포인터

	// 학생 수 count만큼 동적 할당
	list = (element*)malloc(sizeof(element) * count);

	rewind(fp);
	count = 0;

	// 파일 읽기
	while (!feof(fp))
	{
		fscanf(fp, "%c", &flag);

		// i면 삽입
		if (flag == 'i')
		{
			fscanf(fp, "%d %s %d", &list[count].student_no, list[count].name, &list[count].score);
			printf("%d %s %s 삽입 완료\n", list[count].student_no, list[count].name, list[count].score);
			count++;
		}

		char sel[1024];
		int num = 0;

		// p면 출력
		if (flag == 'p')
		{
			fscanf(fp, "%s %d", sel, num);

			// name인 경우
			if (strcmp(sel, "name") == 0)
				insertion_sort(list, num);

			// score인 경우
			else if (strcmp(sel, "score") == 0)
				selection_sort(list, num);

			// number인 경우
			else if (strcmp(sel, "number") == 0)
				quick_sort(list, 0, num - 1);
		}
	}


	fclose(fp);
	return 0;
}