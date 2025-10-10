/*

리스트에서 주로 하는 동작: 데이터 검색, 데이터 삽입/삭제

[스택 (stack)]
- 스택은 일종의 리스트
- 데이터의 삽입과 삭제가 한쪽 끝에서만 이루어짐: Last-In, First-Out (LIFO) 후입선출
- 삽입/삭제가 일어나는 쪽을 스택의 top이라고 부름

일상생활에서 물건을 쌓아놓은 것과 비슷함 (e.g., 동전 탑)


[스택이 지원하는 연산]
1. push: 스택에 새로운 원소를 삽입하는 연산
2. pop: 스택의 top에 있는 원소를 스택에서 제거하고 반환
3. peek: 스택의 top에 있는 원소를 스택에서 제거하지 않고 반환
4. empty: 스택이 비었는지 검사


[스택 응용 예: 괄호 검사 문제]
입력 수식의 괄호가 올바른지 검사
e.g., [ a + b * { c / ( d - e ) } ] + ( d / e )

단순히 여는 괄호와 닫는 괄호의 개수 비교만으로는 부족 -> 스택을 이용하여 검사:
- 여는 괄호는 스택에 push
- 닫는 괄호가 나오면 스택에서 pop한 후, 두 괄호가 같은 유형이어야 함
- 마지막에 스택에 남는 괄호가 없어야 함

*/

#include <stdio.h>
#include <string.h>
#include "stack.h"

#define MAX_LENGTH 100

char OPEN[] = "([{";
char CLOSE[] = ")]}";

int is_balanced(char* expr);
int is_open(char ch);
int is_close(char ch);


int main() {
	char expr[MAX_LENGTH];
	scanf("%s", expr);  // 입력에 괄호만 들어온다고 가정
	if (is_balanced(expr)) {
		printf("%s: balanced.\n", expr);
	}
	else {
		printf("%s: unbalanced.\n", expr);
	}
}


int is_balanced(char* expr) {
	int balanced = 1;
	int index = 0;
	while (balanced && index < strlen(expr)) {
		char ch = expr[index];
		if (is_open(ch) > -1) {
			push(ch);
		}
		else if (is_close(ch) > -1) {
			if (is_empty()) {  // stack이 비었는지 먼저 검사한 뒤에 pop을 시도
				balanced = 0;
				break;
			}
			char top_ch = pop();
			if (is_open(top_ch) != is_close(ch)) {
				balanced = 0;
			}
		}
		index++;
	}
	return (balanced == 1 && is_empty() == 1);
}


int is_open(char ch) {
	for (int i = 0; i < strlen(OPEN); i++) {
		if (OPEN[i] == ch) {
			return i;
		}
	}
	return -1;
}


int is_close(char ch) {
	for (int i = 0; i < strlen(CLOSE); i++) {
		if (CLOSE[i] == ch) {
			return i;
		}
	}
	return -1;
}
