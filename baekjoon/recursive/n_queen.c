#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
	int row;
	int col;
};
typedef struct point Point;

void put_queen(int size, int* board, Point pos) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == pos.row ||
				j == pos.col ||
				i + j == pos.row + pos.col ||
				i - j == pos.row - pos.col) {
				board[i * size + j] = 1;
			}
		}
	}
}

void n_queen(int row, int size, int* board, int* sum) {
	if (row == size) {
		*sum += 1;
	}
	else {
		// 현재 행(row)에서만 열(j)을 선택
		for (int j = 0; j < size; j++) {
			if (board[row * size + j] == 0) {
				// 보드 상태 저장
				int* backup = (int*)malloc(size * size * sizeof(int));
				memcpy(backup, board, size * size * sizeof(int));

				Point pos = { row, j };
				put_queen(size, board, pos);
				n_queen(row + 1, size, board, sum);  // 다음 행부터 시작

				// 보드 상태 복원
				memcpy(board, backup, size * size * sizeof(int));
				free(backup);
			}
		}
	}
}

int main() {
	int n = 0;
	scanf("%d", &n);
	int* board = (int*)calloc(n * n, sizeof(int));

	int sum = 0;
	n_queen(0, n, board, &sum);  // 0행부터 시작
	free(board);
	printf("%d", sum);
	return 0;
}
