/*
[미로찾기]

1. 현재 위치는 출발점 (0, 0)이다.
2. 다음을 반복한다:
    1. 현재 위치에 방문했다는 표시를 한다.
    2. 현재 위치가 출구라면 종료한다.
    3. 현재 위치에서 북, 동, 남, 서 4방향에 대해서 순서대로:
        1) 그 방향으로 이동할 수 있는지 (즉, 벽이 아니고, 미로의 외부도 아니고, 이미 방문한 위치도 아닌지) 검사한다.
        2) 만약 갈 수 있다면 그 방향으로 이동한다.
    4. 만약 3번에서 4방향 중 어느 쪽으로도 가지 못했다면 현재 위치에 도달하기 직전 위치로 되돌아간다. (만약 돌아갈 위치가 없다면 해법이 없는 미로이다.)

Q. 어떻게 돌아갈거냐?
A. 스택의 사용:
2-3-2) 만약 갈 수 있으면 "현재 위치를 스택에 push하고" 그 방향으로 이동한다.
2-4) 만약 3번에서 4방향 중 어느 쪽으로도 갈 수 없었다면 "스택에서 pop한 후 그 위치로 돌아간다"

*/


#include <stdio.h>
#include "stack.h"
#include "pos.h"


#define MAX 100  /* 미로의 최대 크기 (2차원 배열 크기) */
#define PATH 0  /* 지나갈 수 있는 위치의 값 */
#define WALL 1  /* 지나갈 수 없는 위치(벽)의 값 */
#define VISITED 2  /* 지나온 길로 표시할 값 */
#define BACKTRACKED 3  /* 방문했다가 되돌아 나온 위치 */

int maze[MAX][MAX];
int n;

void read_maze();
void print_maze();
bool movable(Position pos, int dir);


int main() {
    read_maze();  /* maze.txt 파일로부터 미로의 모양을 배열 maze로 입력받는다. */

    Stack s = create();  /* 위치를 저장할 스택 (정수가 아니라 Position이라는 구조체를 저장하는 스택임) */
    Position cur;  /* 항상 현재 위치를 표현 */
    cur.x = 0;
    cur.y = 0;

    while (1) {
        maze[cur.x][cur.y] = VISITED;  /* 현재 위치를 방문했다고 표시한다. */
        if (cur.x == n - 1 && cur.y == n - 1) {  /* 현재 위치가 출구라면 */
            printf("Found the path.\n");
            break;
        }
        bool forwarded = false;  /* 사방위 중 어느 방향으로 전진하는데 성공했는지를 기록한다. */
        for (int dir = 0; dir < 4; dir++) {  /* 0: 북, 1: 동, 2: 남, 3: 서 */
            if (movable(cur, dir)) {  /* dir 방향으로 이동할 수 있는지 검사 */
                push(s, cur);  /* 현재 위치를 stack에 push하고 */
                cur = move_to(cur, dir);  /* dir 방향으로 한 칸 이동한 위치를 새로운 cur이라고 한다. */
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
    case 0: // 북
        if (pos.x - 1 >= 0 && maze[pos.x - 1][pos.y] == PATH)
            return true;
        break;
    case 1: // 동
        if (pos.y + 1 < n && maze[pos.x][pos.y + 1] == PATH)
            return true;
        break;
    case 2: // 남
        if (pos.x + 1 < n && maze[pos.x + 1][pos.y] == PATH)
            return true;
        break;
    case 3: // 서
        if (pos.y - 1 >= 0 && maze[pos.x][pos.y - 1] == PATH)
            return true;
        break;
    default:
        break;
    }
    return false;
}