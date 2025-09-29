#include <stdio.h>
#include <stdlib.h>

struct node {
	char* data;
	struct node* next;
};

typedef struct node Node;

Node* head = NULL;


Node* get_node(int index) {
	/* 연결리스트의 index번째 노드의 주소를 반환한다. */
	if (index < 0) {
		return NULL;
	}
	Node* p = head;
	for (int i = 0; i < index && p != NULL; i++) {
		p = p->next;
	}
	return p;
}


int add(int index, char* item) {
	/* 연결리스트의 index번째 위치에 새로운 노드를 만들어서 삽입한다. */
	if (index < 0) {
		return 0;
	}

	/* add_first(), add_after() 에서 새로운 노드를 만드는 일을 하기 때문에 새로운 노드를 만들 필요 없음 */
	if (index == 0) {
		add_first(item);
		return 1;
	}

	Node* prev = get_node(index - 1);
	if (prev != NULL) {
		add_after(prev, item);
		return 1;
	}
	return 0;
}


Node* remove(int index) {
	/* index번째 노드를 삭제하고, 그 노드의 주소를 반환한다. */
	if (index < 0) {
		return NULL;
	}

	if (index == 0) {
		return remove_first();
	}

	Node* prev = get_node(index - 1);
	if (prev == NULL) {
		return NULL;
	}
	else {
		return remove_after(prev);
	}
}


Node* remove(char* item) {
	/* 입력된 문자열을 가지고 있는 노드를 찾아 삭제하고, 해당 노드의 주소를 반환한다. */
	Node* p = head;
	Node* prev = NULL;
	while (p != NULL && strcmp(p->data, item) != 0) {
		prev = p;
		p = p->next;
	}
	if (p == NULL) {  /* 너가 찾는 데이터가 없다 */
		return NULL;
	}
	if (prev == NULL) {  /* 첫번째 노드가 삭제할 노드일 경우 */
		return remove_first();
	}
	else {
		return remove_after(prev);
	}
}


void add_to_ordered_list(char* item) {
	/* 연결리스트의 데이터들이 (알파벳) 오름차순으로 정렬되어 있다는 가정하에 새로운 데이터를 삽입한다. */
	Node* p = head;
	Node* prev = NULL;

	while (p != NULL && strcmp(p->data, item) <= 0) {
		/* strcmp(a, b) ==> 대충 char별로 a - b */
		prev = p;
		p = p->next;
	}
	if (prev == NULL) {
		add_first(item);
	}
	else {
		add_after(prev, item);
	}
}
