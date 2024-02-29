/*
알고리즘 기말 레포트 과제
20204026 정명훈
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 50000 // 5만개의 정수를 저장하기 위한 배열 크기 지정

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
int comparison_count_quick = 0; // 퀵 정렬 비교 횟수
int swap_count_quick = 0; // 퀵 정렬 이동 횟수

// 퀵 정렬에서 사용하는 분할 함수
int partition(int array[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = array[left];

	do {
		do { // 왼쪽에서 오른쪽으로 이동하며 pivot보다 큰 값을 찾음
			low++;
			comparison_count_quick++; // 비교 횟수 증가
		} while (array[low] < pivot);

		do { // 오른쪽에서 왼쪽으로 이동하며 pivot보다 작은 값을 찾음
			high--;
			comparison_count_quick++; // 비교 횟수 증가
		} while (array[high] > pivot);

		if (low < high) { // low와 high 교환
			temp = array[low];
			array[low] = array[high];
			array[high] = temp;
			swap_count_quick++; // 이동 횟수 증가
		}

	} while (low < high);

	// pivot과 high가 가리키는 값 교환
	temp = array[left];
	array[left] = array[high];
	array[high] = temp;
	swap_count_quick++; // 이동 횟수 증가

	return high;
}

void quick_sort(int array[], int left, int right)
{
	if (left < right) {
		int q = partition(array, left, right); // partition 함수의 반환값은 피봇의 위치가 된다.
		quick_sort(array, left, q - 1); // left에서 pivot 위치 바로 앞까지를 대상으로 순환호출
		quick_sort(array, q + 1, right); // pivot 위치 바로 다음부터 right까지 순환호출
	}
}


//////////////////////////////////////////////////////////////////////////////
// 합병 정렬
#define MAX_SIZE 50000
int sorted[MAX_SIZE]; // 추가 공간이 필요

// i는 정렬된 왼쪽 리스트에 대한 인덱스
// j는 정렬된 오른쪽 리스트에 대한 인덱스
// k는 정렬될 리스트에 대한 인덱스
void merge(int array[], int left, int mid, int right, int* comparison_count, int* swap_count)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	// 분할 정렬된 array의 합병
	while (i <= mid && j <= right) {

		(*comparison_count)++; // 비교 횟수 증가
		if (array[i] <= array[j]) sorted[k++] = array[i++];
		else sorted[k++] = array[j++];
	}

	// 남아 있는 레코드의 일괄 복사
	if (i > mid) {
		for (l = j; l <= right; l++) sorted[k++] = array[l];
	}

	// 남아 있는 레코드의 일괄 복사
	else {
		for (l = i; l <= mid; l++) sorted[k++] = array[l];
	}

	// 배열 sorted[]의 리스트를 배열 array[]로 재복사
	for (l = left; l <= right; l++) {
		array[l] = sorted[l];
		(*swap_count)++; // 이동 횟수 증가
	}
}

void merge_sort(int array[], int left, int right, int* comparison_count, int* swap_count)
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2; // 리스트의 균등 분할
		merge_sort(array, left, mid, comparison_count, swap_count); // 부분 리스트 정렬
		merge_sort(array, mid + 1, right, comparison_count, swap_count); // 부분 리스트 정렬
		merge(array, left, mid, right, comparison_count, swap_count); // 합병
	}
}


//////////////////////////////////////////////////////////////////////////////
// 쉘 정렬
// gap만큼 떨어진 요소들을 삽입 정렬, 범위는 first에서 last
void inc_insertion_sort(int array[], int first, int last, int gap, int* comparison_count, int* swap_count)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {

		key = array[i];
		(*comparison_count)++; // 비교 횟수 증가

		for (j = i - gap; j >= first && key < array[j]; j = j - gap) {
			array[j + gap] = array[j];
			(*swap_count)++; // 이동 횟수 증가
			(*comparison_count)++; // 비교 횟수 증가
		}

		array[j + gap] = key;
	}
}

// 쉘 정렬 함수
void shell_sort(int array[], int size, int* comparison_count, int* swap_count)
{
	int i, gap;

	for (gap = size / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++; // gap이 짝수인 경우 1 증가시킴
		for (i = 0; i < gap; i++)
			inc_insertion_sort(array, i, size - 1, gap, comparison_count, swap_count);
	}
}


//////////////////////////////////////////////////////////////////////////////
// 버블 정렬 함수
void bubble_sort(int array[], int size, int *comparison_count, int *swap_count)
{
	int i, j, temp;

	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - i - 1; j++) {

			(*comparison_count)++; // 비교 횟수 증가

			if (array[j] > array[j + 1]) { // 앞뒤의 레코트를 비교한 후 교체
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;

				(*swap_count)++; // 이동 횟수 증가
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////////
// 선택 정렬 함수
void selection_sort(int array[], int size, int* comparison_count, int* swap_count)
{
	int i, j, least, temp;

	for (i = 0; i < size - 1; i++) {
		least = i;

		for (j = i + 1; j < size; j++) { // 최소값 탐색

			(*comparison_count)++; // 비교 횟수 증가

			if (array[j] < array[least]) 
				least = j;
		}

		// 최소값과 현재 위치의 값 교환
		temp = array[least];
		array[least] = array[i];
		array[i] = temp;

		(*swap_count)++; // 이동 횟수 증가
	}
}


//////////////////////////////////////////////////////////////////////////////
// 삽입 정렬 함수
void insertion_sort(int array[], int size, int* comparison_count, int* swap_count)
{
	int i, j, key;

	for (i = 1; i < size; i++) {
		key = array[i];
		j = i - 1;

		(*comparison_count)++; // 비교 횟수 증가

		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j]; // 레코드의 오른쪽으로 이동
			j = j - 1;
			(*swap_count)++; // 이동 횟수 증가
			(*comparison_count)++; // 비교 횟수 증가
		}

		array[j + 1] = key;
	}
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int main() {
	// 1. 5만개 정수 저장할 배열 선언
	int randomNum_array[ARRAY_SIZE];
	
	// 2. RandomNum 함수를 이용하여 난수 생성 후 배열에 저장
	RandomNum(randomNum_array, ARRAY_SIZE);

	clock_t start, end; // 호출되기 전 시간, 함수 종료된 후 시간
	double total_used_time; // 정렬 실행시간

	int comparison_count = 0; // 비교 횟수
	int swap_count = 0; // 이동 횟수

	// 3. 정렬 알고리즘을 이용해 오름차순으로 정렬
	// 정렬 함수가 호출되기 전에 시간을 기록하고, 함수가 종료된 후의 시간을 구해 총 소요시간을 초로 환산하여 표시
	// 정렬 실행 시간과 함계 비교 횟수와 이동 횟수를 구해서 표시

	//////////////////////////////////////////////////////////////////////////////
	// 3-1. 삽입 정렬 함수 호출
	start = time(NULL);
	insertion_sort(randomNum_array, ARRAY_SIZE, &comparison_count, &swap_count);
	end = time(NULL);

	total_used_time = difftime(end, start); // 총 소요시간 계산

	// 3-2. 출력
	printf("< 삽입 정렬 함수 >\n");
	printf("시작 시간 : %d 종료 시간 : %d\n", start, end);
	printf("총 소요시간 : %.2f\n", total_used_time);
	printf("비교 횟수 : %d 이동 횟수 : %d\n\n", comparison_count, swap_count);

	// 3-3. 초기화
	comparison_count = 0; // 비교 횟수 초기화
	swap_count = 0; // 이동 횟수 초기화
	total_used_time = 0; // 총 소요시간 초기화
	RandomNum(randomNum_array, ARRAY_SIZE);


	//////////////////////////////////////////////////////////////////////////////
	// 3-1. 선택 정렬 함수 호출
	start = time(NULL);
	selection_sort(randomNum_array, ARRAY_SIZE, &comparison_count, &swap_count);
	end = time(NULL);

	total_used_time = difftime(end, start); // 총 소요시간 계산

	// 3-2. 출력
	printf("< 선택 정렬 함수 >\n");
	printf("시작 시간 : %d 종료 시간 : %d\n", start, end);
	printf("총 소요시간 : %.2f\n", total_used_time);
	printf("비교 횟수 : %d 이동 횟수 : %d\n\n", comparison_count, swap_count);

	// 3-3. 초기화
	comparison_count = 0; // 비교 횟수 초기화
	swap_count = 0; // 이동 횟수 초기화
	total_used_time = 0; // 총 소요시간 초기화
	RandomNum(randomNum_array, ARRAY_SIZE);


	//////////////////////////////////////////////////////////////////////////////
	// 3-1. 버블 정렬 함수 호출
	start = time(NULL);
	bubble_sort(randomNum_array, ARRAY_SIZE, &comparison_count, &swap_count);
	end = time(NULL);

	total_used_time = difftime(end, start); // 총 소요시간 계산

	// 3-2. 출력
	printf("< 버블 정렬 함수 >\n");
	printf("시작 시간 : %d 종료 시간 : %d\n", start, end);
	printf("총 소요시간 : %.2f\n", total_used_time);
	printf("비교 횟수 : %d 이동 횟수 : %d\n\n", comparison_count, swap_count);

	// 3-3. 초기화
	comparison_count = 0; // 비교 횟수 초기화
	swap_count = 0; // 이동 횟수 초기화
	total_used_time = 0; // 총 소요시간 초기화
	RandomNum(randomNum_array, ARRAY_SIZE);


	//////////////////////////////////////////////////////////////////////////////
	// 3-1. 쉘 정렬 함수 호출
	start = time(NULL);
	shell_sort(randomNum_array, ARRAY_SIZE, &comparison_count, &swap_count);
	end = time(NULL);

	total_used_time = difftime(end, start); // 총 소요시간 계산

	// 3-2. 출력
	printf("< 쉘 정렬 함수 >\n");
	printf("시작 시간 : %d 종료 시간 : %d\n", start, end);
	printf("총 소요시간 : %.2f\n", total_used_time);
	printf("비교 횟수 : %d 이동 횟수 : %d\n\n", comparison_count, swap_count);

	// 3-3. 초기화
	comparison_count = 0; // 비교 횟수 초기화
	swap_count = 0; // 이동 횟수 초기화
	total_used_time = 0; // 총 소요시간 초기화
	RandomNum(randomNum_array, ARRAY_SIZE);


	//////////////////////////////////////////////////////////////////////////////
	// 3-1. 합병 정렬 함수 호출
	start = time(NULL);
	merge_sort(randomNum_array, 0, ARRAY_SIZE - 1, &comparison_count, &swap_count);
	end = time(NULL);

	total_used_time = difftime(end, start); // 총 소요시간 계산

	// 3-2. 출력
	printf("< 합병 정렬 함수 >\n");
	printf("시작 시간 : %d 종료 시간 : %d\n", start, end);
	printf("총 소요시간 : %.2f\n", total_used_time);
	printf("비교 횟수 : %d 이동 횟수 : %d\n\n", comparison_count, swap_count);

	// 3-3. 초기화
	comparison_count = 0; // 비교 횟수 초기화
	swap_count = 0; // 이동 횟수 초기화
	total_used_time = 0; // 총 소요시간 초기화
	RandomNum(randomNum_array, ARRAY_SIZE);

	
	//////////////////////////////////////////////////////////////////////////////
	// 3-1. 퀵 정렬 함수 호출
	start = time(NULL);
	quick_sort(randomNum_array, 0, ARRAY_SIZE - 1);
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
	RandomNum(randomNum_array, ARRAY_SIZE);
	
	return 0;
}