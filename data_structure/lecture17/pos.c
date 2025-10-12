#include "pos.h"

int offset[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };  // 각각 북, 동, 남, 서 방향으로의 이동

Position move_to(Position pos, int dir) {
	Position next;
	next.x = pos.x + offset[dir][0];
	next.y = pos.y + offset[dir][1];
	return next;
}