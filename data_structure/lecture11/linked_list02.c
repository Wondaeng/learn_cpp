#include <stdio.h>
#include <stdlib.h> /* MQ1. 없이 malloc을 쓰면... */

struct node {
	char* data;
	struct node* next;
};  /* 강의에는 없는데, 구조체 선언시 중괄호 뒤에 세미콜론이 필요하다 함 */

typedef struct node Node;
Node* head = NULL;

/* head가 전역변수인 경우 */
void add_first(char* item) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = item;
	temp->next = head;
	head = temp;
}


/* 
head가 전역변수가 아닌 경우 매개변수로 Node* head를 전달하면 되지 않는가?
--> head의 주소값을 그대로 이용할 땐 문제가 없지만,
head가 가르키는 주소값을 변경해야할 땐 문제가된다. 왜냐하면:
C언어에서 함수의 매개변수의 전달 방식은 call-by-value이므로
값이 매개변수에 복사되어 전달된 상태로 이 변수에 할당된 값을 수정하더라도 
원래의 head 변수의 값은 수정되지 않기 때문
*/
void add_first(char* item, Node* head) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = item;
	temp->next = head;  /* 이 줄은 문제가 없으나 */
	head = temp;  /* 이 줄은 이 add_first 바깥의 head를 직접 바꾸지 않음 */
}


/* 다음과 같이 호출해야함: add_first(&head, item_to_store); */
void add_first(Node** ptr_head, char* item) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = item;
	temp->next = *ptr_head;
	*ptr_head = temp;
}


/* 다음과 같이 호출해야함: add_first(head, item_to_store); */
void add_first(Node* head, char* item) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = item;
	temp->next = head;
	return temp;
}

