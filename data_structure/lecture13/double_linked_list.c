#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
단방향 연결 리스트 (single linked list)의 한계: 노드가 한쪽 방향(다음 주소)으로만 연결 되어있음
- 어떤 노드의 앞에 새로운 노드를 삽입하기 어려움 (이전 노드의 주소를 알아야 함. 즉, 뒤에만 삽입 가능)
- 삭제의 경우에도 항상 삭제할 노드의 앞 노드가 필요 
- 단방향의 순회만이 가능

이중 연결 리스트:
- 각각의 노드가 다음(next) 노드와 이전(previous) 노드의 주소를 둘다 가지는 연결 리스트
- 양방향의 순회가 가능
*/


struct node {
	char* data;
	struct node* next;
	struct node* prev;
};

typedef struct node Node;

Node* head;
Node* tail;
int size = 0;


void add(Node* p) {
	/*
	예시) 포인터 p가 가리키는 노드 앞에 새로운 노드를 삽입하기
	! 여러가지 예외적 경우들이 있음 (empty, 맨 앞, 맨 뒤, 사이)
	*/
	Node* new_node = (Node*)malloc(sizeof(Node));

	new_node->data = "Sharon";
	new_node->next = p;  
	new_node->prev = p->prev;

	p->prev->next = new_node;
	p->prev = new_node;
}


void remove(Node* p) {
	/* p가 가리키는 노드를 삭제하는 경우 */
	p->prev->next = p->next;
	p->next->prev = p->prev;
}


void add_after(Node* pre, char* item) {
	/*
	pre가 가리키는 노드 바로 다음에 새로운 노드를 만들어서 item을 저장하여 삽입 
	뿐만아니라, 연결리스트의 맨 앞에 삽입, empty list인 경우 등등도 커버
	*/

	/* 새로운 노드 생성 */
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = item;
	new_node->prev = NULL;
	new_node->next = NULL;

	/* 연결리스트가 비어있는 경우 (함수명과는 살짝 미스매치) */
	if (pre == NULL && head == NULL) {
		head = new_node;
		tail = new_node;
	}
	/* NULL 다음에 삽입: 즉, 연결리스트의 가장 앞에 삽입하는 경우 */
	else if (pre == NULL) {
		new_node->next = head;
		head->prev = new_node;
		head = new_node;
	}
	/* 연결리스트의 가장 마지막 노드(tail) 뒤에 삽입하는 경우 */
	else if (pre == tail) {
		new_node->prev = tail;
		tail->next = new_node;
		tail = new_node;
	}
	/* 어떤 두 노드의 사이에 삽입하는 경우 */
	else {
		new_node->next = pre->next;
		new_node->prev = pre;
		pre->next->prev = new_node;
		pre->next = new_node;
	}
	size++;
}


void remove(Node* p) {
	/*
	1. p가 유일한 노드인 경우
	2. p가 head인 경우
	3. p가 tail인 경우
	4. 그밖의 일반적인 경우 
	*/
	if (p == NULL) {
		return;
	}

	if (p == head && p == tail) {
		head = NULL;
		tail = NULL;
	}
	else if (p == head) {
		head = p->next;
		head->prev = NULL;
	}
	else if (p == tail) {
		tail = p->prev;
		tail->next = NULL;
	}
	else {
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	free(p);
	size--;
}


void add_ordered_list(char* item) {
	/* 알파벳 오름차순 순서로 삽입하기 */
	Node* p = tail;
	while (p != NULL && strcmp(item, p->data) < 0) {
		p = p->prev;
	}
	add_after(p, item);
}
