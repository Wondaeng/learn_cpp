/*

큐(Queue): 스택과 마찬가지로 일종의 리스트
- 단, 데이터의 삽입은 한쪽 끝에서, 삭제는 반대쪽 끝에서만 일어남
- 삽입이 일어나는 쪽을 rear, 삭제가 일어나는 쪽을 front라고 부름
- FIFO(First-In, First-Out)라고 불림


큐가 지원하는 연산:
- insert, enqueue, offer, push: 큐의 rear에 새로운 원소를 삽입하는 연산
- remove, dequeue, poll, pop: 큐의 front에 있는 원소를 큐로부터 삭제하고 반환하는 연산
- peek, element, front: 큐의 front에 있는 원소를 제거하지 않고 반환하는 연산
- is_empty: 큐가 비었는지 검사


활용 예:
- CPU 스케쥴링: multitasking 환경에서 프로세스들은 큐에서 CPU가 할당되기를 기다린다.
- 데이터 버퍼: 네트워크 패킷들은 도착한 순서대로 버퍼에 저장되어 처리되기를 기다린다.

*/


/*

[단방향 연결리스트를 이용한 큐의 구현]

큐의 rear에는 삽입, front에서는 삭제가 일어남
연결리스트의 앞: 삽입 이나 삭제 모두 어렵지 않음
연결리스트의 끝: 삽입을 하려면 마지막 노드의 주소를 기억해야함
하지만 삭제의 경우에는 마지막 노드의 앞 노드의 주소를 기억해야함 --> 불편함
(head쪽 삭제는 기존 head가 삭제되기전에 해당 노드의 next를 통해 head가 업데이트 가능하나,
tail쪽 삭제는 prev가 없으므로 업데이트가 불가능 또는 head부터 끝까지 다시 traverse 해야함)

*/

#include <stdio.h>
#include <stdlib.h>
#include "queueADT.h"

struct node {
	Item data;
	struct node* next;
};

struct queue_type {
	struct node* front;
	struct node* rear;
	int size;
};

void terminate(const char* message) {
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}


int get_size(Queue q) {
	return q->size;
}


Queue create() {
	Queue q = (Queue)malloc(sizeof(struct queue_type));
	if (q == NULL) {
		terminate("Error in create: queue could not be created.");
	}

	q->front = NULL;
	q->rear = NULL;
	q->size = 0;
	return q;
}


void destroy(Queue q) {
	make_empty(q);
	free(q);
}


void make_empty(Queue q) {
	while (!is_empty(q)) {
		dequeue(q);
	}
	q->size = 0;
}


bool is_empty(Queue q) {
	return q->front == NULL;  /* or return q->size == 0; */
}


void enqueue(Queue q, Item i) {
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	if (new_node == NULL) {
		terminate("Error in push: queue is full.");
	}

	new_node->data = i;
	new_node->next = NULL;

	if (q->front == NULL) {
		q->front = new_node;
		q->rear = new_node;
	}
	else {
		q->rear->next = new_node;
		q->rear = new_node;
	}
	q->size++;
}


Item dequeue(Queue q) {
	struct node* old_front;
	Item i;

	if (is_empty(q)) {
		terminate("Error in dequeue: queue is empty.");
	}

	old_front = q->front;
	i = old_front->data;
	q->front = old_front->next;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	free(old_front);
	q->size--;
	return i;
}


Item peek(Queue q) {
	if (is_empty(q)) {
		terminate("Error in peek: queue is empty.");
	}
	return q->front->data;
}
