#include <stdio.h>
#include <stdlib.h> /* MQ1. 없이 malloc을 쓰면... */

struct node {
	char* data;
	struct node* next;
};  /* 강의에는 없는데, 구조체 선언시 중괄호 뒤에 세미콜론이 필요하다 함 */

typedef struct node Node;
Node* head = NULL;


int main() {
	/* 배열과는 다르게 데이터를 추가할 때 마다 필요한 메모리를 할당 받음 */
	head = (Node*)malloc(sizeof(Node));
	head->data = "Tuesday";
	head->next = NULL;

	Node* q = (Node*)malloc(sizeof(Node));
	q->data = "Thursday";
	q->next = NULL;
	head->next = q;

	q = (Node*)malloc(sizeof(Node));
	q->data = "Monday";
	q->next = head;
	head = q;

	Node* p = head;
	while (p != NULL) {
		printf("%s\n", p->data);
		p = p->next;  /* 중요! */
	}
	return 0;
} 

/*
Q. 왜 p라는 추가적인 포인터 변수를 사용했을까? 
그냥 head를 가지고 해도 되지않나?
while (head != NULL) {
	print();
	head = head -> next;
}

A. 결과적으론 같은 내용이 출력될 것이지만 head가 첫 노드의 주소를 잃게됨.
*/
