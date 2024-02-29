#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define array_size 50000 // 5만개의 정수를 저장하기 위한 배열 크기 지정

// 난수 생성 후 배열에 저장하는 함수
void RandomNum(int array[], int size)
{
	// 난수 발생기를 시간에 기반하여 초기화해줌
	srand(time(NULL));

	for (int i = 0; i < size; i++) {
		array[i] = rand();
	}
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// 퀵 정렬
// 퀵 정렬에서 사용할 비교, 이동 횟수 카운트할 변수를 전역 변수로 선언
int comparison_count_quick;
int swap_count_quick;

int partition(int array[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = array[left];

	do {
		do {
			low++;
			comparison_count_quick++; // 비교 횟수 증가
		} while (array[low] < pivot);

		do {
			high--;
			comparison_count_quick++; // 비교 횟수 증가
		} while (array[high] > pivot);

		if (low < high) {
			temp = array[low];
			array[low] = array[high];
			array[high] = temp;
			swap_count_quick++; // 이동 횟수 증가
		}

	} while (low < high);

	temp = array[left];
	array[left] = array[high];
	array[high] = temp;
	swap_count_quick++; // 이동 횟수 증가

	return high;
}

void quick_sort(int array[], int left, int right)
{
	comparison_count_quick = 0;
	swap_count_quick = 0;
	if (left < right) {
		int q = partition(array, left, right);
		quick_sort(array, left, q - 1);
		quick_sort(array, q + 1, right);
	}
}

int main() {
	int randomNum_array_quick[array_size];
	RandomNum(randomNum_array_quick, array_size);

	clock_t start, end; // 호출되기 전 시간, 함수 종료된 후 시간
	double total_used_time; // 정렬 실행시간

	int comparison_count = 0; // 비교 횟수
	int swap_count = 0; // 이동 횟수

	//////////////////////////////////////////////////////////////////////////////
	// 3-1. 퀵 정렬 함수 호출
	start = time(NULL);
	quick_sort(randomNum_array_quick, 0, array_size);
	end = time(NULL);

	total_used_time = difftime(end, start); // 총 소요시간 계산

	// 3-2. 출력
	printf("< 퀵 정렬 함수 >\n");
	printf("시작 시간 : %d 종료 시간 : %d\n", start, end);
	printf("총 소요시간 : %.2f\n", total_used_time);
	printf("비교 횟수 : %d 이동 횟수 : %d\n\n", comparison_count_quick, swap_count_quick);

	// 3-3. 초기화
	comparison_count = 0; // 비교 횟수 초기화
	swap_count = 0; // 이동 횟수 초기화
	total_used_time = 0; // 총 소요시간 초기화

	return 0;
}