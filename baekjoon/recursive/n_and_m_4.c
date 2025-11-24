#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void print_sequence(int index, int depth, int n, int* arr, int* result, int* used) {
	if (index == depth) {
		for (int i = 0; i < depth; i++) {
			printf("%d ", result[i]);
		}
		printf("\n");
	}
	else {
		for (int i = 0; i < n; i++) {

			if (index == 0 || result[index - 1] <= arr[i]) {
				result[index] = arr[i];
				print_sequence(index + 1, depth, n, arr, result, used);

			}
		}
	}
}


int main() {
	int arr[8] = { 0 };
	
	int n = 0;
	int m = 0;
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		arr[i] = i + 1;
	}

	int* result = (int*)malloc(m * sizeof(int));
	int* used = (int*)calloc(n, sizeof(int));

	print_sequence(0, m, n, arr, result, used);

	free(result);
	free(used);

	return 0;
}
