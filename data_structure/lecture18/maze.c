/*

너비 우선 탐색(BFS)으로 미로 찾기 

다음과 같은 순서로 셀(cell)들을 방문:
- L_0 = {s}, s는 출발 지점
- L_1 = L_0에서 한번에 갈 수 있는 모든 셀들
- L_2 = L_1에서 한번에 갈 수 있는 셀들 중에서 L_0에 속하지 않는 셀들
...
- L_i = L_i-1에서 한번에 갈 수 있는 셀들 중에서 L_i-2에 속하지 않는 셀들

--> 최단 경로를 찾음


1. 하나의 큐를 만든다. 
2. 위치 (0, 0)은 이미 방문한 위치임을 표시하고, 큐에 위치 (0, 0)을 넣는다.
3. 큐가 빌 때 까지 다음을 반복한다:
    a. 큐에서 하나의 위치 p를 꺼낸다.
    b. p에서 한 칸 떨어진 위치들 중에서 이동 가능하면서,
       아직 방문하지 않은 모든 위치들을 방문된 위치임을 표시하고 큐에 넣는다.
    c. 만약 그 위치가 출구라면 종료한다.
4. 출구에서 숫자가 감소하는 방향으로 따라가면 입구에 도달

*/

#include "queueADT.h"

int main() {
    Queue queue = create();
    Position cur;
    cur.x = 0;
    cur.y = 0;

    enqueue(queue, cur);

    maze[0][0] = -1;
    bool found = false;

    while (!is_empty(queue)) {
        Position cur = dequeue(queue);
        for (int dir = 0; dir < 4; dir++) {
            if (movable(cur, dir)) {
                Position p = move_to(cur, dir);
                maze[p.x][p.y] = maze[cur.x][cur.y] - 1;
                if (p.x == n - 1 && p.y == n - 1) {
                    printf("Found the path.\n");
                    found = true;
                    break;
                }
                enqueue(queue, p);
            }
        }
    }
}

/*
[큐의 변형]

1. Deque (Double ended queue):
- 양 쪽 끝에서 삽입과 삭제가 허용되는 큐
- "덱" 혹은 "디큐"라고 읽음

2. 우선순위 큐 (priority queue):
- 큐에 들어온 순서와 무관하게 큐에 저장된 값들 중에서 가장 큰 값이 (혹은 가장 작은 값이) 가 장 먼저 꺼내지는 큐
  (-> 최대우선순위 큐 / 최소우선순위 큐)
- 대표적인 구현 방법으로는 이진 힙(binary heap)이 있음

*/
