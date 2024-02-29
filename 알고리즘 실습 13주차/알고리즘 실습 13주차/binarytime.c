// 알고리즘 실습 13주차 1번
// 반복을 이용한 이진 탐색
// 데이터 파일에 저장된 정수들을 이진 탐색을 동적 할당을 이용한 배열로 구현하고 탐색하여 걸린 시간 출력
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binary_search(int key, int low, int high, int list[])
{
	int mid;

	while (low <= high) {
		mid = (low + high) / 2;

		if (key == list[mid]) return mid;
		else if (key > list[mid]) 
			low = mid + 1;
		else high = mid - 1;
	}

	return -1;
}

int main() {
	FILE* fp;
	fp = fopen("data2.txt", "r");

	int count = 0;
	int i = 0;

	int* list = NULL;
	int key = 0;
	clock_t start, end;
	float result;
	int flag;

	while (!feof(fp))
	{
		fscanf(fp, "%d", &i);
		count++;
	}

	rewind(fp);

	list = (int*)malloc(sizeof(int) * count);

	count = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%d", &list[count]);
		count++;
	}

	printf("찾고자 하는 정수를 입력하세요 : ");
	scanf("%d", &key);

	start = clock();
	flag = binary_search(key, 0, count - 1, list);
	end = clock();

	result = (float)(end - start) / CLOCKS_PER_SEC;

	if (flag == -1) printf("탐색 실패\n");
	else {
		printf("< 탐색 성공 >\n");
		printf("%d 번째에 저장되어 있음\n", flag + 1);
		printf("이진탐색 실행 속도 : %d\n", result);
	}

	free(list);
	fclose(fp);
	return 0;
}