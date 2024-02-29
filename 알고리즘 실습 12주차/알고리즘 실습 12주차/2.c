#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)


int seq_search(int key, int low, int high, int list[])
{
	int i;
	for (i = low; i <= high; i++)
		if (list[i] == key)
			return i;

	return -1;
}
int seq2_search(int key, int low, int high, int list[])
{
	int i;
	list[high + 1] = key;

	for (i = low; list[i] != key; i++);
	if (i == (high + 1))
		return -1;
	else
		return i;
}


int main()
{
	FILE* fp;
	int count = 0;
	int i;
	int* list = NULL;
	int KEY = -1;
	clock_t start, end, start2, end2;
	float seq_time, seq2_time;
	int result, result2;

	fp = fopen("data2.txt", "r");

	while (!feof(fp))
	{
		fscanf(fp, "%d", &i);
		count++;
	}

	rewind(fp);


	list = (int*)malloc(sizeof(int) * (count + 2));

	count = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%d", &list[count]);
		count++;
	}
	printf("데이터 개수: %d\n", count);
	printf("검색하는 정수를 입력하시오: ");
	scanf("%d", &KEY);

	start = clock();
	result = seq_search(KEY, 0, count - 1, list);
	end = clock();

	start2 = clock();
	result2 = seq2_search(KEY, 0, count - 1, list);
	end2 = clock();

	seq_time = (float)(end - start) / CLOCKS_PER_SEC;
	seq2_time = (float)(end2 - start2) / CLOCKS_PER_SEC;

	if (result != -1 && result2 != -1)
	{
		printf("탐색 성공\n");
		printf("순차검색 속도: %f\n", seq_time);
		printf("개선된 순차검색 속도: %f\n", seq2_time);
	}
	else
	{
		printf("탐색 실패\n");
		printf("순차검색 속도: %f\n", seq_time);
		printf("개선된 순차검색 속도: %f\n", seq2_time);
	}
	free(list);
	fclose(fp);

	return 0;
}