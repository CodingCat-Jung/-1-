/*
�˰��� �⸻ ����Ʈ ����
20204026 ������
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 50000 // 5������ ������ �����ϱ� ���� �迭 ũ�� ����

// ���� ���� �� �迭�� �����ϴ� �Լ�
void RandomNum(int array[], int size)
{
	// ���� �߻��⸦ �ð��� ����Ͽ� �ʱ�ȭ����
	srand(time(NULL));

	for (int i = 0; i < size; i++) {
		array[i] = rand();
	}
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// �� ����
// �� ���Ŀ��� ����� ��, �̵� Ƚ�� ī��Ʈ�� ������ ���� ������ ����
int comparison_count_quick = 0; // �� ���� �� Ƚ��
int swap_count_quick = 0; // �� ���� �̵� Ƚ��

// �� ���Ŀ��� ����ϴ� ���� �Լ�
int partition(int array[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = array[left];

	do {
		do { // ���ʿ��� ���������� �̵��ϸ� pivot���� ū ���� ã��
			low++;
			comparison_count_quick++; // �� Ƚ�� ����
		} while (array[low] < pivot);

		do { // �����ʿ��� �������� �̵��ϸ� pivot���� ���� ���� ã��
			high--;
			comparison_count_quick++; // �� Ƚ�� ����
		} while (array[high] > pivot);

		if (low < high) { // low�� high ��ȯ
			temp = array[low];
			array[low] = array[high];
			array[high] = temp;
			swap_count_quick++; // �̵� Ƚ�� ����
		}

	} while (low < high);

	// pivot�� high�� ����Ű�� �� ��ȯ
	temp = array[left];
	array[left] = array[high];
	array[high] = temp;
	swap_count_quick++; // �̵� Ƚ�� ����

	return high;
}

void quick_sort(int array[], int left, int right)
{
	if (left < right) {
		int q = partition(array, left, right); // partition �Լ��� ��ȯ���� �Ǻ��� ��ġ�� �ȴ�.
		quick_sort(array, left, q - 1); // left���� pivot ��ġ �ٷ� �ձ����� ������� ��ȯȣ��
		quick_sort(array, q + 1, right); // pivot ��ġ �ٷ� �������� right���� ��ȯȣ��
	}
}


//////////////////////////////////////////////////////////////////////////////
// �պ� ����
#define MAX_SIZE 50000
int sorted[MAX_SIZE]; // �߰� ������ �ʿ�

// i�� ���ĵ� ���� ����Ʈ�� ���� �ε���
// j�� ���ĵ� ������ ����Ʈ�� ���� �ε���
// k�� ���ĵ� ����Ʈ�� ���� �ε���
void merge(int array[], int left, int mid, int right, int* comparison_count, int* swap_count)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	// ���� ���ĵ� array�� �պ�
	while (i <= mid && j <= right) {

		(*comparison_count)++; // �� Ƚ�� ����
		if (array[i] <= array[j]) sorted[k++] = array[i++];
		else sorted[k++] = array[j++];
	}

	// ���� �ִ� ���ڵ��� �ϰ� ����
	if (i > mid) {
		for (l = j; l <= right; l++) sorted[k++] = array[l];
	}

	// ���� �ִ� ���ڵ��� �ϰ� ����
	else {
		for (l = i; l <= mid; l++) sorted[k++] = array[l];
	}

	// �迭 sorted[]�� ����Ʈ�� �迭 array[]�� �纹��
	for (l = left; l <= right; l++) {
		array[l] = sorted[l];
		(*swap_count)++; // �̵� Ƚ�� ����
	}
}

void merge_sort(int array[], int left, int right, int* comparison_count, int* swap_count)
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2; // ����Ʈ�� �յ� ����
		merge_sort(array, left, mid, comparison_count, swap_count); // �κ� ����Ʈ ����
		merge_sort(array, mid + 1, right, comparison_count, swap_count); // �κ� ����Ʈ ����
		merge(array, left, mid, right, comparison_count, swap_count); // �պ�
	}
}


//////////////////////////////////////////////////////////////////////////////
// �� ����
// gap��ŭ ������ ��ҵ��� ���� ����, ������ first���� last
void inc_insertion_sort(int array[], int first, int last, int gap, int* comparison_count, int* swap_count)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {

		key = array[i];
		(*comparison_count)++; // �� Ƚ�� ����

		for (j = i - gap; j >= first && key < array[j]; j = j - gap) {
			array[j + gap] = array[j];
			(*swap_count)++; // �̵� Ƚ�� ����
			(*comparison_count)++; // �� Ƚ�� ����
		}

		array[j + gap] = key;
	}
}

// �� ���� �Լ�
void shell_sort(int array[], int size, int* comparison_count, int* swap_count)
{
	int i, gap;

	for (gap = size / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++; // gap�� ¦���� ��� 1 ������Ŵ
		for (i = 0; i < gap; i++)
			inc_insertion_sort(array, i, size - 1, gap, comparison_count, swap_count);
	}
}


//////////////////////////////////////////////////////////////////////////////
// ���� ���� �Լ�
void bubble_sort(int array[], int size, int *comparison_count, int *swap_count)
{
	int i, j, temp;

	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - i - 1; j++) {

			(*comparison_count)++; // �� Ƚ�� ����

			if (array[j] > array[j + 1]) { // �յ��� ����Ʈ�� ���� �� ��ü
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;

				(*swap_count)++; // �̵� Ƚ�� ����
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////////
// ���� ���� �Լ�
void selection_sort(int array[], int size, int* comparison_count, int* swap_count)
{
	int i, j, least, temp;

	for (i = 0; i < size - 1; i++) {
		least = i;

		for (j = i + 1; j < size; j++) { // �ּҰ� Ž��

			(*comparison_count)++; // �� Ƚ�� ����

			if (array[j] < array[least]) 
				least = j;
		}

		// �ּҰ��� ���� ��ġ�� �� ��ȯ
		temp = array[least];
		array[least] = array[i];
		array[i] = temp;

		(*swap_count)++; // �̵� Ƚ�� ����
	}
}


//////////////////////////////////////////////////////////////////////////////
// ���� ���� �Լ�
void insertion_sort(int array[], int size, int* comparison_count, int* swap_count)
{
	int i, j, key;

	for (i = 1; i < size; i++) {
		key = array[i];
		j = i - 1;

		(*comparison_count)++; // �� Ƚ�� ����

		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j]; // ���ڵ��� ���������� �̵�
			j = j - 1;
			(*swap_count)++; // �̵� Ƚ�� ����
			(*comparison_count)++; // �� Ƚ�� ����
		}

		array[j + 1] = key;
	}
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int main() {
	// 1. 5���� ���� ������ �迭 ����
	int randomNum_array[ARRAY_SIZE];
	
	// 2. RandomNum �Լ��� �̿��Ͽ� ���� ���� �� �迭�� ����
	RandomNum(randomNum_array, ARRAY_SIZE);

	clock_t start, end; // ȣ��Ǳ� �� �ð�, �Լ� ����� �� �ð�
	double total_used_time; // ���� ����ð�

	int comparison_count = 0; // �� Ƚ��
	int swap_count = 0; // �̵� Ƚ��

	// 3. ���� �˰����� �̿��� ������������ ����
	// ���� �Լ��� ȣ��Ǳ� ���� �ð��� ����ϰ�, �Լ��� ����� ���� �ð��� ���� �� �ҿ�ð��� �ʷ� ȯ���Ͽ� ǥ��
	// ���� ���� �ð��� �԰� �� Ƚ���� �̵� Ƚ���� ���ؼ� ǥ��

	//////////////////////////////////////////////////////////////////////////////
	// 3-1. ���� ���� �Լ� ȣ��
	start = time(NULL);
	insertion_sort(randomNum_array, ARRAY_SIZE, &comparison_count, &swap_count);
	end = time(NULL);

	total_used_time = difftime(end, start); // �� �ҿ�ð� ���

	// 3-2. ���
	printf("< ���� ���� �Լ� >\n");
	printf("���� �ð� : %d ���� �ð� : %d\n", start, end);
	printf("�� �ҿ�ð� : %.2f\n", total_used_time);
	printf("�� Ƚ�� : %d �̵� Ƚ�� : %d\n\n", comparison_count, swap_count);

	// 3-3. �ʱ�ȭ
	comparison_count = 0; // �� Ƚ�� �ʱ�ȭ
	swap_count = 0; // �̵� Ƚ�� �ʱ�ȭ
	total_used_time = 0; // �� �ҿ�ð� �ʱ�ȭ
	RandomNum(randomNum_array, ARRAY_SIZE);


	//////////////////////////////////////////////////////////////////////////////
	// 3-1. ���� ���� �Լ� ȣ��
	start = time(NULL);
	selection_sort(randomNum_array, ARRAY_SIZE, &comparison_count, &swap_count);
	end = time(NULL);

	total_used_time = difftime(end, start); // �� �ҿ�ð� ���

	// 3-2. ���
	printf("< ���� ���� �Լ� >\n");
	printf("���� �ð� : %d ���� �ð� : %d\n", start, end);
	printf("�� �ҿ�ð� : %.2f\n", total_used_time);
	printf("�� Ƚ�� : %d �̵� Ƚ�� : %d\n\n", comparison_count, swap_count);

	// 3-3. �ʱ�ȭ
	comparison_count = 0; // �� Ƚ�� �ʱ�ȭ
	swap_count = 0; // �̵� Ƚ�� �ʱ�ȭ
	total_used_time = 0; // �� �ҿ�ð� �ʱ�ȭ
	RandomNum(randomNum_array, ARRAY_SIZE);


	//////////////////////////////////////////////////////////////////////////////
	// 3-1. ���� ���� �Լ� ȣ��
	start = time(NULL);
	bubble_sort(randomNum_array, ARRAY_SIZE, &comparison_count, &swap_count);
	end = time(NULL);

	total_used_time = difftime(end, start); // �� �ҿ�ð� ���

	// 3-2. ���
	printf("< ���� ���� �Լ� >\n");
	printf("���� �ð� : %d ���� �ð� : %d\n", start, end);
	printf("�� �ҿ�ð� : %.2f\n", total_used_time);
	printf("�� Ƚ�� : %d �̵� Ƚ�� : %d\n\n", comparison_count, swap_count);

	// 3-3. �ʱ�ȭ
	comparison_count = 0; // �� Ƚ�� �ʱ�ȭ
	swap_count = 0; // �̵� Ƚ�� �ʱ�ȭ
	total_used_time = 0; // �� �ҿ�ð� �ʱ�ȭ
	RandomNum(randomNum_array, ARRAY_SIZE);


	//////////////////////////////////////////////////////////////////////////////
	// 3-1. �� ���� �Լ� ȣ��
	start = time(NULL);
	shell_sort(randomNum_array, ARRAY_SIZE, &comparison_count, &swap_count);
	end = time(NULL);

	total_used_time = difftime(end, start); // �� �ҿ�ð� ���

	// 3-2. ���
	printf("< �� ���� �Լ� >\n");
	printf("���� �ð� : %d ���� �ð� : %d\n", start, end);
	printf("�� �ҿ�ð� : %.2f\n", total_used_time);
	printf("�� Ƚ�� : %d �̵� Ƚ�� : %d\n\n", comparison_count, swap_count);

	// 3-3. �ʱ�ȭ
	comparison_count = 0; // �� Ƚ�� �ʱ�ȭ
	swap_count = 0; // �̵� Ƚ�� �ʱ�ȭ
	total_used_time = 0; // �� �ҿ�ð� �ʱ�ȭ
	RandomNum(randomNum_array, ARRAY_SIZE);


	//////////////////////////////////////////////////////////////////////////////
	// 3-1. �պ� ���� �Լ� ȣ��
	start = time(NULL);
	merge_sort(randomNum_array, 0, ARRAY_SIZE - 1, &comparison_count, &swap_count);
	end = time(NULL);

	total_used_time = difftime(end, start); // �� �ҿ�ð� ���

	// 3-2. ���
	printf("< �պ� ���� �Լ� >\n");
	printf("���� �ð� : %d ���� �ð� : %d\n", start, end);
	printf("�� �ҿ�ð� : %.2f\n", total_used_time);
	printf("�� Ƚ�� : %d �̵� Ƚ�� : %d\n\n", comparison_count, swap_count);

	// 3-3. �ʱ�ȭ
	comparison_count = 0; // �� Ƚ�� �ʱ�ȭ
	swap_count = 0; // �̵� Ƚ�� �ʱ�ȭ
	total_used_time = 0; // �� �ҿ�ð� �ʱ�ȭ
	RandomNum(randomNum_array, ARRAY_SIZE);

	
	//////////////////////////////////////////////////////////////////////////////
	// 3-1. �� ���� �Լ� ȣ��
	start = time(NULL);
	quick_sort(randomNum_array, 0, ARRAY_SIZE - 1);
	end = time(NULL);

	total_used_time = difftime(end, start); // �� �ҿ�ð� ���

	// 3-2. ���
	printf("< �� ���� �Լ� >\n");
	printf("���� �ð� : %d ���� �ð� : %d\n", start, end);
	printf("�� �ҿ�ð� : %.2f\n", total_used_time);
	printf("�� Ƚ�� : %d �̵� Ƚ�� : %d\n\n", comparison_count_quick, swap_count_quick);

	// 3-3. �ʱ�ȭ
	comparison_count = 0; // �� Ƚ�� �ʱ�ȭ
	swap_count = 0; // �̵� Ƚ�� �ʱ�ȭ
	total_used_time = 0; // �� �ҿ�ð� �ʱ�ȭ
	RandomNum(randomNum_array, ARRAY_SIZE);
	
	return 0;
}