/*

[후위표기식 (postfix expression)]
일반적으로 사용하는 수식은 보통 중위(infix) 표기식임 -> 연산자가 피연산자 사이에 들어감
반면, 후위표기식은 연산자가 피 연산자 뒤에 나옴


수도 알고리즘:

create an empty stack of integers;
while there remains a token  // token은 연산자 혹은 피연산자를 의미
    get the next token;
    if the token is an operands
        push the operand on the stack;
    else if the token is an operator
        pop the right operand off the stack (top);
        pop the left operand off the stack (top - 1);
        evaluate the operation;
        push the result onto the stack;
pop the stack and return the result

가정:
1. 모든 피연산자는 양의 정수다 (음수의 - 기호가 이항연산자인지 구분 불가능).
2. 모든 연산자와 피연산자 사이에는 하나 이상의 공백문자로 구분되어 있다

*/

#include "stackADT.h"
#include <stdlib.h>


static char OPERATORS[] = "+-*/";

Stack operand_stack;

int is_operator(char ch) {
    for (int i = 0; i < strlen(OPERATORS); i++) {
        if (OPERATORS[i] == ch) {
            return i;
        }
    }
    return -1;
}

int eval(char* expr);
void handle_exception(const char* err_msg);
int eval_op(char op);


int eval(char* expr) {
    operand_stack = create();
    char* token = strtok(expr, " ");
    while (token != NULL) {
        if (token[0] >= '0' && token[0] <= '9') {
            int value = atoi(token);
            push(operand_stack, value);
        }
        else if (is_operator(token[0]) > -1) {
            int result = eval_op(token[0]);
            push(operand_stack, result);
        }
        else {
            handle_exception("Syntax Error: invalid character encountered.");
        }
        token = strtok(NULL, " ");
    }
    if (is_empty(operand_stack)) {  // 이 함수에서 이런 경우에 도달할 수가 있나? 어쨌거나 eval_op에서 받은 리턴값을 push 하는데..
        handle_exception("Syntax Error: Stack empty in eval_op.");
    }
    int answer = pop(operand_stack);
    if (is_empty(operand_stack)) {
        return answer;
    }
    else {
        handle_exception("Syntax Error: Stack should be empty.");
        return -1;
    }
}


void handle_exception(const char* err_msg) {
    printf("%s\n", err_msg);
    exit(1);
}


int eval_op(char op) {
    if (is_empty(operand_stack)) {
        handle_exception("Syntax Error: Stack empty in eval_op.");
    }
    int rhs = pop(operand_stack);
    if (is_empty(operand_stack)) {
        handle_exception("Syntax Error: Stack empty in eval_op.");
    }
    int lhs = pop(operand_stack);
    int result = 0;
    
    switch (op) {
    case '+': result = lhs + rhs; break;
    case '-': result = lhs - rhs; break;
    case '*': result = lhs * rhs; break;
    case '/': result = lhs / rhs; break;  // 정수 나누기 정수면 몫만 나오지 않나?
    }
    return result;
}
