// 데이터 파일에 저장되어 있는 데이터를 불러와 오름차순으로 정렬
// 퀵 정렬 이용
// 15 4 8 22 7 54 3 80 48 42 2 98 5
#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t)((t)=(x),(x)=(y),(y)=(t))

int count = 0;

int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	printf("- Pivot: %d -\n", pivot);

	do {
		do {
			low++;
		} while (low <= right && list[low] < pivot);

		do {
			high--;
		} while (high >= left && list[high] > pivot);

		printf("Low: %d High: %d ", list[low], list[high]);
		printf("[ ");
		for (int i = 0; i < count; i++) { // count == right-1
			printf("%d >", list[i]);
		}
		printf(" ]\n\n");

		if (low < high) {
			printf("%d와 %d스왑\n", list[low], list[high]);
			SWAP(list[low], list[high], temp);

			printf("[ ");
			for (int i = 0; i < count; i++) {
				printf("%d >", list[i]);
			}
			printf(" ]\n\n");
		}
	} while (low < high);

	SWAP(list[left], list[high], temp);

	return high;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

int main() {

	FILE* fp;
	fp = fopen("data3.txt", "r");

	int* list;
	int temp;
	
	while (!feof(fp)) {
		fscanf(fp, "%d", &temp);
		count++;
	}

	list = (int*)malloc(sizeof(int) * count);
	rewind(fp);

	for (int i = 0; i < count; i++) {
		fscanf(fp, "%d", &list[i]);
	}

	printf("정렬 전 리스트 >\n");
	for (int i = 0; i < count; i++) {
		printf("%d >", list[i]);
	}

	printf("\n\n");
	quick_sort(list, 0, count-1);
	printf("\n\n");

	printf("정렬 후 리스트 >\n");
	for (int i = 0; i < count; i++) {
		printf("%d >", list[i]);
	}

	fclose(fp);
	return 0;
	
}