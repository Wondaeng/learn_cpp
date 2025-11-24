#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int compare_ints(const void* a, const void* b) {
	// 두 개의 const void * 포인터를 int * 타입으로 캐스팅
	int int_a = *((const int*)a);
	int int_b = *((const int*)b);

	// 오름차순 정렬을 위해
	if (int_a < int_b) return -1;
	if (int_a > int_b) return 1;
	return 0;
}


void print_sequence(int index, int depth, int n, int* arr, int* result, int* used) {
	if (index == depth) {
		for (int i = 0; i < depth; i++) {
			printf("%d ", result[i]);
		}
		printf("\n");
	}
	else {
		for (int i = 0; i < n; i++) {
			if (used[i]) {
				continue;
			}
			result[index] = arr[i];
			used[i] = 1;
			print_sequence(index + 1, depth, n, arr, result, used);
			used[i] = 0;
		}
	}
}


int main() {
	int arr[8] = { 0 };

	int n = 0;
	int m = 0;
	scanf("%d %d", &n, &m);

	int num = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &num);
		arr[i] = num;
	}

	qsort(arr, n, sizeof(int), compare_ints);

	int* result = (int*)malloc(m * sizeof(int));
	int* used = (int*)calloc(n, sizeof(int));

	print_sequence(0, m, n, arr, result, used);

	free(result);
	free(used);

	return 0;
}
