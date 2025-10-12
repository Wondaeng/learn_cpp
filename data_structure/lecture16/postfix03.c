/* 

후위표기식으로 변환 - 괄호가 있는 경우

1. 여는 괄호는 무조건 스택에 push한다. 이때 스택 내의 어떤 연산자도 pop하지 않는다.
2. 어떤 연산자를 스택에 push할 때, 스택의 top에 여는 괄호가 있으면 아무도 pop하지 않고 그냥 push한다.
3. 입력에 닫는 괄호가 나오면 스택에서 여는 괄호가 나올 때 까지 pop하여 출력한다. 닫는 괄호는 스택에 push하지 않는다.

*/

#define MAX_LENGTH 100

#include "stackADT.h"
#include <stdlib.h>
#include <stdio.h>


char OPERATORS[] = "+=*/()";
int PRECEDENCE[] = { 1, 1, 2, 2, -1, -1 };  // -1로 해두면 괄호냐 아니냐를 검사할 필요가 없이 무조건 operator가 push됨

Stack operator_stack;

char* convert(char* infix) {
	operator_stack = create();
	char* postfix = (char*)malloc(strlen(infix) + 1);
	char* pos = postfix;

	char* token = strtok(infix, " ");
    while (token != NULL) {
        if (token[0] >= '0' && token[0] <= '9') {
            sprintf(pos, "%s ", token);  // sprintf를 이용하여 문자열에 append한다.
            pos += (strlen(token) + 1);  // 공백 때문에 +1
        }
        else if (is_operator(token[0]) > -1) {
            pos = process_op(token[0], pos);  // 현재 operator_stack에서 연산자를 꺼내 출력해야 할 수도 있으므로, process_op() 함수에서 현재 postfix의 pos를 알아야함 (또한, 내부적으로 pos값을 전진시키고 반환함)
        }
        else {
            handle_exception("Syntax Error: invalid character encountered.");
        }
        token = strtok(NULL, " ");
    }

    while (!is_empty(operator_stack)) {
        char op = (char)pop(operator_stack);
        if (op == '(') {  // stack에 여는 괄호가 남아있으면 안된다 (닫히지 않았다는 뜻)
            handle_exception("Unmatched parenthesis.");
        }
        sprintf(pos, "%c ", op);
        pos += 2;
    }

    *pos = '\0';
    return postfix;
}


char* process_op(char op, char* pos) {
    if (is_empty(operator_stack) || op == '(') {  // 1. 여는 괄호 무조건 push
        push(operator_stack, op);
    }
    else {  // op가 여는괄호는 아님 -> +-*/)
        char top_op = peek(operator_stack);
        if (precedence(op) > precedence(top_op)) {
            push(operator_stack, op);
        }
        else {
            while (!is_empty(operator_stack) && precedence(op) <= precedence(top_op)) {
                pop(operator_stack);
                if (top_op == '(') {  // 2. op의 우선순위가 top_op보다 낮거나 같은데, top_op가 여는 괄호라면 op는 닫는 괄호라는 뜻이다.
                    break;
                }
                sprintf(pos, "%c ", top_op);
                pos += 2;
                if (!is_empty(operator_stack)) {
                    top_op = (char)peek(operator_stack);
                }
            }
            if (op != ')') {  // 3. 닫는 괄호는 push하지 않는다
                push(operator_stack, op);
            }
        }
    }
    return pos;
}


int main() {
    char infix[MAX_LENGTH];
    read_line(stdin, infix, MAX_LENGTH);

    printf(" %s := ", infix);
    char* postfix = convert(infix);
    printf("%d\n", eval(postfix));
}


/*

미흡한 점:
- 피연산자는 양의 정수만 허용: 음수나 실수로 확장
- 모든 토큰들이 공백문자로 구분되어 있어야 함
- 일진(unary) 연산자의 처리: e.g., -(-2)
- right associativity를 가지는 연산자의 처리: 2^3^4
- 후위표기식으로 변환하는 일과 후위표기식으로 계산하는 일을 하나로 합치기

*/
