#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 50

struct stack_type {
    int* contents;
    int top;
};

typedef struct stack_type* Stack;


Stack create(){
    Stack s = (Stack)malloc(sizeof(struct stack_type));
    s->contents = (int*)malloc(sizeof(int) * CAPACITY);
    s->top = -1;
    
    return s;
}


int is_full(Stack s) {
    if (s->top == CAPACITY - 1) {
        return 1;
    } else {
        return 0;
    }
}


int is_empty(Stack s){
    if (s->top == -1) {
        return 1;
    } else {
        return 0;
    }
}


void empty(Stack s) {
    s->top = -1;
}

void push(Stack s, int i) {
    if (is_full(s) == 1) {
        return;
    }
    
    s->top++;
    s->contents[s->top] = i;
    
}


int pop(Stack s) {
    if (is_empty(s) == 1) {
        return -1;
    }
    
    int i = s->contents[s->top];
    s->top--;
    
    return i;
}


int main() {
	Stack s = create();
    
    int num_inputs = 0;
    scanf("%d", &num_inputs);
    getchar();  // 입력스트림에 남아있는 '\n' 제거
    
    for (int i = 0; i < num_inputs; i++) {
        int ch = 0;
        int valid = 1;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            if (ch == '(') {
                push(s, 1);
            }
            else if (ch == ')') {
                int result = pop(s);
                if (result == -1) {
                    valid = 0;
                    while ((ch = getchar()) != '\n' && ch != EOF) {
                        continue;  // 입력스트림에 남아있는 문자 제거거
                    }
                    break;
                }
            }
            
        }

        
            
        if (is_empty(s) == 0) {
            valid = 0;
        }
        
        if (valid == 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        
        empty(s);
    }
}

