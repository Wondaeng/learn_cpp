#include <stdio.h>
#include <stdlib.h> /* MQ1. 없이 malloc을 쓰면... */

struct node {
	char* data;
	struct node* next;
};  /* 강의에는 없는데, 구조체 선언시 중괄호 뒤에 세미콜론이 필요하다 함 */

typedef struct node Node;
Node* head = NULL;


int add_after(Node* prev, char* item) {
	/*
	새로운 노드를 만들고 특정 노드 뒤(prev 포인터 변수가 가르키는)에 삽입하기
	(1) 새로운 노드를 만들고 데이터를 저장
	(2) 새로은 노드의 next 필드가 prev의 다음 노드를 가르키도록 한다
	(3) 새로운 노드를 prev의 다음 노드로 만든다
	*/
	if (prev == NULL) {
		return 0;
	}
	
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = item;
	tmp->next = prev->next;
	prev->next = tmp;
	
	return 1;
	/*
	Q. add_after()를 했으니까... add_before()는 어떨까?
	(어떤 노드의 주소의 앞에 삽입하는 것은 어떨까?)

	A. 간단하지 않다. 삽입의 기준이 되는 노드의 원래 앞에 있던 노드의 주소를 알아야
	하는데, 기준 노드의 주소를 가지고 그 앞의 노드의 주소를 알아내는 방법이 마땅치 않기 때문이다.
	*/
}


Node* remove_first() {
	/*
	첫번째 노드의 삭제: head가 현재 head 노드의 다음 노드를 가리키게 만든다
	head = head->next;
	*/
	if (head == NULL) {
		return NULL;
	}
	else {
		Node* tmp = head;
		head = head->next;
		return tmp;  /* 나중에 기존 첫번째 노드를 free 시켜주기 위해 반환 */
	}
}


Node* remove_after(Node* prev) {
	/*
	어떤 노드의 다음 노드 삭제하기
	왜 굳이 이렇게 하냐? 어떤 노드를 삭제하려면 그 노드의 이전 노드의 next 필드 값을 바꿔야 함.
	삭제할 노드의 주소를 안다고 해서, 그 노드의 이전 노드의 주소는 모르기 때문에...
	*/
	Node* tmp = prev->next;
	if (tmp == NULL) {
		return NULL;
	}
	else {
		prev->next = tmp->next;
		return tmp;
	}
}


Node* find(char* word) {
	/* 연결리스트의 노드들을 처음부터 순서대로 방문하는 것 = 순회(traverse) */
	Node* p = head;
	while (p != NULL) {
		if (strcmp(p->data, word) == 0) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}
