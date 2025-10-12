/*

중위표기식을 후위표기식으로 변환 - 괄호가 없는 경우:

- 중위표기식을 처음부터 순서대로 읽으면서
- 피연산자는 즉시 출력한다
- 모든 연산자는 일단 stack에 push한다
- 단, 이때 스택 내에 우선순위가 자신보다 더 높은 (동일한 우선순위여도 먼저 나왔으므로 사실상 우선순위가 높을 수 있음) 연산자가 있으면 pop하여 출력한 후에 push한다
- 수식이 종료되면 스택에 있는 모든 연산자를 pop하여 출력한다.


수도 코드:
Initialize 'postfix' to an empty string;
Create the operator stack;
while there are more tokens in the infix expression
    Get the next token;
    if the next token is operand
        Append it to 'postfix';
    else if the next token is an operator
        Call 'process_operator' to process the operator;
    else
        Indicate a syntax error;
Pop the remaining operators off the operator stack and append them to postfix;


[Algorithm for process_operator]

if the operator stack is empty
    Push the current operator onto the stack;
else
    Peek the operator and let top_op be the top operator;
    if the precedence of the current operator is greater than that of top_op
        Push the current operator onto the stack;
    else 
        while the stack is not empty and the precedence of the current operator is less than or equal to the precedence of top_op
            Pop top_op off the stack and append it to postfix;
            if the operator stack is not empty
                Peek the operator stack and let top_op be the top operator;
        Push the current operator onto the stack;

*/

static char OPERATORS[] = "+-*/";
static int PRECEDENCE[] = { 1, 1, 2, 2 };  // 우선순위 비교를 위해 +, -, *, / 순서대로 1, 1, 2, 2의 값을 배정. 값이 클수록 우선순위가 높음을 뜻함.

Stack operator_stack;

/*

Stack 구조체는 int를 저장하는데 (stackADT.c) 우리에게 필요한건 char 스택임 (e.g., operand_stack의 경우 정수를 저장했었음)

때문에 엄밀히는 틀린 구조지만, 메모리를 뜯어보면 어느정도의 호환성(?)이 있어서 그냥 사용가능: char -> int = 정수 승격 (integer promotion)

char: 1byte
int: 4byte

그냥 정수 스택을 만들어서 char를 집어넣으면, 어차피 사칙연산 기호는 아스키코드(7비트 문자 집합)이므로 첫비트는 0이고,
따라서 이를 int로 변환하면 남는 앞 3byte가 모두 0으로 채워짐 
따라서 int -> char 거꾸로 나중에 다시 변환해도 문제 없음 

예시)

int main() {
    signed char a = 200;      // signed: 음수로 해석됨
    unsigned char b = 200;    // unsigned: 양수 200으로 해석

    printf("a = %d\n", a); // 출력: -56 (부호 확장)
    printf("b = %u\n", b); // 출력: 200
}

*/


char* convert(char* infix) {
    operator_stack = create();

    char* postfix = (char*)malloc(strlen(infix) + 1);  // postfix expression이 저장될 문자 배열 할당. 힙에 저장하여 함수가 종료되더라도 남아있게 malloc 사용. +1은 왜? \0 때문?
    char* pos = postfix;  // postfix의 어디까지 썼는지 위치를 표시할 포인터 
    
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
        sprintf(pos, "%c ", op);
        pos += 2;
    }
    *pos = '\0';
    return postfix;
}


char* process_op(char op, char* pos) {
    if (is_empty(operator_stack)) {
        push(operator_stack, op);
    }
    else {
        char top_op = peek(operator_stack);
        if (precedence(op) > precedence(top_op)) {
            push(operator_stack, op);
        }
        else {
            while (!is_empty(operator_stack) && precedence(op) <= precedence(top_op)) {
                pop(operator_stack);  // 리턴 값을 받지 않고 그냥 버리는 이유: 이미 top_op에 peek해둔 값을 저장해 뒀기 때문
                sprintf(pos, "%c ", top_op);
                pos += 2;
                if (!is_empty(operator_stack)) {
                    top_op = (char)peek(operator_stack);
                }
            }
            push(operator_stack, op);
        }
    }
    return pos;
}

