/*
스택이라는 개념 자체는 추상적인 자료형(ADT)이며, 리스트라는 자료형의 특수한 형태로 볼 수 있다.
따라서, 스택은 우리가 배웠던 두 종류의 리스트인 배열 또는 연결리스트를 이용하여 구현할 수 있다.
*/

// 1. 배열을 이용한 구현

#include "stack.h"
#define MAX_CAPACITY 100

char stack[MAX_CAPACITY];  // 1. 스택의 이름을 stack, 2. stack에 저장할 데이터 타입은 char로 가정

/*
index of the top element 
초기값이 -1 --> index가 실제 top 데이터의 인덱스를 가리킴
초기값이 0 --> index가 실제 top 데이터의 다음 인덱스를 가리킴
*/

int top = -1;  

void push(char ch) {
	if (is_full()) {  // stack이 가득차면 더이상 push할 수 없다
		return;
	}
	top++;
	stack[top] = ch;
}


char pop() {
	if (is_empty()) {  // pop을 호출하기 전에 먼저 empty인지 검사해야 한다
		return;
	}
	char tmp = stack[top];
	top--;
	return tmp;
}


char peek() {
	return stack[top];
}


int is_empty() {
	return top == -1;
}


int is_full() {
	return top == MAX_CAPACITY - 1;
}
