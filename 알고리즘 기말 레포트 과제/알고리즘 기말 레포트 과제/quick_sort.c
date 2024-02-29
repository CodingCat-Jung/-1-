#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define array_size 50000 // 5������ ������ �����ϱ� ���� �迭 ũ�� ����

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
			comparison_count_quick++; // �� Ƚ�� ����
		} while (array[low] < pivot);

		do {
			high--;
			comparison_count_quick++; // �� Ƚ�� ����
		} while (array[high] > pivot);

		if (low < high) {
			temp = array[low];
			array[low] = array[high];
			array[high] = temp;
			swap_count_quick++; // �̵� Ƚ�� ����
		}

	} while (low < high);

	temp = array[left];
	array[left] = array[high];
	array[high] = temp;
	swap_count_quick++; // �̵� Ƚ�� ����

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

	clock_t start, end; // ȣ��Ǳ� �� �ð�, �Լ� ����� �� �ð�
	double total_used_time; // ���� ����ð�

	int comparison_count = 0; // �� Ƚ��
	int swap_count = 0; // �̵� Ƚ��

	//////////////////////////////////////////////////////////////////////////////
	// 3-1. �� ���� �Լ� ȣ��
	start = time(NULL);
	quick_sort(randomNum_array_quick, 0, array_size);
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

	return 0;
}