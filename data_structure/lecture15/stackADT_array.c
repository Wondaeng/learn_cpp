/*
문제점:

1. 만약 stack이 2개 이상 필요하다면?
배열을 이용한 구현의 경우, 함수들이 모두 "stack"이라는 특정한 배열을 기준으로 정의되어 있음 --> 함수가 스택 개수만큼 배로 필요해짐
연결리스트를 이용한 구현의 경우에도 비슷하게 "top"이라는 이름의 포인터를 기준으로 정의되어 있음

2. 서로 다른 타입의 데이터를 저장할 스택이 필요하다면? (C언어로 완벽하게 해결하기 어려움)

*/


/*

push()라는 하나의 함수로 여러개의 배열에 사용할 수 있으려면...

push() 함수가 매개변수로 stack을 받을 수 밖에 없음 --> void push(Stack s, Item i)

*/


// 배열로 구현

#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

#define INIT_CAPACITY 100

/*
stack을 구현하기 위해선, 하나의 배열과 / top의 위치를 가리키는 변수 --> 2개 이상의 변수가 필요함 --> 하나의 구조체로 정의
*/
struct stack_type {

	Item * contents;  /* Item의 배열 */
	int top;
	int size;  /* contents 배열의 크기 */

};


static void terminate(const char* message) {  // static은 뭐죠? 알아보세요

	printf("%s\n", message);
	exit(1);

}


Stack create() {
	
	Stack s = (Stack)malloc(sizeof(struct stack_type));
	if (s == NULL) {
		terminate("Error in create: stack could not be created.");
	}
	
	s->contents = (Item*)malloc(INIT_CAPACITY * sizeof(Item));
	if (s->contents == NULL) {
		free(s);
		terminate("Error in create: stack could not be created.");
	}

	s->top = -1;
	s->size = INIT_CAPACITY;
	return s;

}


void destroy(Stack s) {

	free(s->contents);
	free(s);

}


void make_empty(Stack s) {
	
	s->top = -1;

}


bool is_empty(Stack s) {

	return s->top == -1;

}


void push(Stack s, Item i) {

	if (is_full(s)) {
		reallocate(s);
	}
	s->top++;
	s->contents[s->top] = i;

}


Item pop(Stack s) {
	if (is_empty(s)) {
		terminate("Error in pop: stack is empty.");
	}
	s->top--;
	return s->contents[s->top + 1];
}


Item peek(Stack s) {
	if (is_empty(s)) {
		terminate("Error in peek: stack is empty.");
	}
	return s->contents[s->top];
}


void reallocate(Stack s) {

	Item* tmp = (Item*)malloc(2 * s->size * sizeof(Item));
	if (tmp == NULL) {
		terminate("Error in create: stack could not be created.");
	}
	for (int i = 0; i < s->size; i++) {
		tmp[i] = s->contents[i];
	}
	free(s->contents);
	s->contents = tmp;
	s->size *= 2;

}

/*

사용 예)

#include "stackADT.h"

int main() {
	
	Stack s1 = create();
	Stack s2 = create();

	push(s1, 12);
	push(s2, 9);

}

*/
