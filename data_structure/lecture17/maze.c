/*
[�̷�ã��]

1. ���� ��ġ�� ����� (0, 0)�̴�.
2. ������ �ݺ��Ѵ�:
    1. ���� ��ġ�� �湮�ߴٴ� ǥ�ø� �Ѵ�.
    2. ���� ��ġ�� �ⱸ��� �����Ѵ�.
    3. ���� ��ġ���� ��, ��, ��, �� 4���⿡ ���ؼ� �������:
        1) �� �������� �̵��� �� �ִ��� (��, ���� �ƴϰ�, �̷��� �ܺε� �ƴϰ�, �̹� �湮�� ��ġ�� �ƴ���) �˻��Ѵ�.
        2) ���� �� �� �ִٸ� �� �������� �̵��Ѵ�.
    4. ���� 3������ 4���� �� ��� �����ε� ���� ���ߴٸ� ���� ��ġ�� �����ϱ� ���� ��ġ�� �ǵ��ư���. (���� ���ư� ��ġ�� ���ٸ� �ع��� ���� �̷��̴�.)

Q. ��� ���ư��ų�?
A. ������ ���:
2-3-2) ���� �� �� ������ "���� ��ġ�� ���ÿ� push�ϰ�" �� �������� �̵��Ѵ�.
2-4) ���� 3������ 4���� �� ��� �����ε� �� �� �����ٸ� "���ÿ��� pop�� �� �� ��ġ�� ���ư���"

*/


#include <stdio.h>
#include "stack.h"
#include "pos.h"


#define MAX 100  /* �̷��� �ִ� ũ�� (2���� �迭 ũ��) */
#define PATH 0  /* ������ �� �ִ� ��ġ�� �� */
#define WALL 1  /* ������ �� ���� ��ġ(��)�� �� */
#define VISITED 2  /* ������ ��� ǥ���� �� */
#define BACKTRACKED 3  /* �湮�ߴٰ� �ǵ��� ���� ��ġ */

int maze[MAX][MAX];
int n;

void read_maze();
void print_maze();
bool movable(Position pos, int dir);


int main() {
    read_maze();  /* maze.txt ���Ϸκ��� �̷��� ����� �迭 maze�� �Է¹޴´�. */

    Stack s = create();  /* ��ġ�� ������ ���� (������ �ƴ϶� Position�̶�� ����ü�� �����ϴ� ������) */
    Position cur;  /* �׻� ���� ��ġ�� ǥ�� */
    cur.x = 0;
    cur.y = 0;

    while (1) {
        maze[cur.x][cur.y] = VISITED;  /* ���� ��ġ�� �湮�ߴٰ� ǥ���Ѵ�. */
        if (cur.x == n - 1 && cur.y == n - 1) {  /* ���� ��ġ�� �ⱸ��� */
            printf("Found the path.\n");
            break;
        }
        bool forwarded = false;  /* ����� �� ��� �������� �����ϴµ� �����ߴ����� ����Ѵ�. */
        for (int dir = 0; dir < 4; dir++) {  /* 0: ��, 1: ��, 2: ��, 3: �� */
            if (movable(cur, dir)) {  /* dir �������� �̵��� �� �ִ��� �˻� */
                push(s, cur);  /* ���� ��ġ�� stack�� push�ϰ� */
                cur = move_to(cur, dir);  /* dir �������� �� ĭ �̵��� ��ġ�� ���ο� cur�̶�� �Ѵ�. */
                forwarded = true;
                break;
            }
        }
        if (!forwarded) {
            maze[cur.x][cur.y] = BACKTRACKED;
            if (is_empty(s)) {
                printf("No path exists.\n");
                break;
            }
            cur = pop(s);
        }
    }
    print_maze();
}


bool movable(Position pos, int dir) {
    switch (dir) {
    case 0: // ��
        if (pos.x - 1 >= 0 && maze[pos.x - 1][pos.y] == PATH)
            return true;
        break;
    case 1: // ��
        if (pos.y + 1 < n && maze[pos.x][pos.y + 1] == PATH)
            return true;
        break;
    case 2: // ��
        if (pos.x + 1 < n && maze[pos.x + 1][pos.y] == PATH)
            return true;
        break;
    case 3: // ��
        if (pos.y - 1 >= 0 && maze[pos.x][pos.y - 1] == PATH)
            return true;
        break;
    default:
        break;
    }
    return false;
}