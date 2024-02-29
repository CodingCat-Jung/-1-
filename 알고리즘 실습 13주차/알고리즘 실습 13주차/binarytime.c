// �˰��� �ǽ� 13���� 1��
// �ݺ��� �̿��� ���� Ž��
// ������ ���Ͽ� ����� �������� ���� Ž���� ���� �Ҵ��� �̿��� �迭�� �����ϰ� Ž���Ͽ� �ɸ� �ð� ���
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

	printf("ã���� �ϴ� ������ �Է��ϼ��� : ");
	scanf("%d", &key);

	start = clock();
	flag = binary_search(key, 0, count - 1, list);
	end = clock();

	result = (float)(end - start) / CLOCKS_PER_SEC;

	if (flag == -1) printf("Ž�� ����\n");
	else {
		printf("< Ž�� ���� >\n");
		printf("%d ��°�� ����Ǿ� ����\n", flag + 1);
		printf("����Ž�� ���� �ӵ� : %d\n", result);
	}

	free(list);
	fclose(fp);
	return 0;
}