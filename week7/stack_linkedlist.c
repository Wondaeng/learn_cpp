/*

push X: 정수 X를 스택에 넣는 연산이다.
pop: 스택에서 가장 위에 있는 정수를 빼고, 그 수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.
size: 스택에 들어있는 정수의 개수를 출력한다.
empty: 스택이 비어있으면 1, 아니면 0을 출력한다.
top: 스택의 가장 위에 있는 정수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CAPACITY 10000


struct node {
	int data;
	struct node* next;
};

struct stack_type {
	struct node* top;
	int num;
};


typedef struct stack_type* Stack;

Stack create(){
    
    Stack s = (Stack)malloc(sizeof(struct stack_type));
    s->top = NULL;
    s->num = 0;
    return s;
}


void push(Stack s, int data) {
    
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = s->top;
    s->top = new_node;
    s->num++;
}


int is_empty(Stack s){
    if (s->top == NULL){
        return 1;
    } else {
        return 0;
    }
}


int pop(Stack s) {
    if (is_empty(s)){
        return -1;
    }
    
    struct node* old_top;
    int i;
    
    old_top = s->top;  // free 해주기 위해 들고있어야 함
    i = old_top->data;
    
    s->top = old_top->next;  // top 갱신 후 기존 old_top 삭제 
    free(old_top);
    
    s->num--;
    
    return i;
}


int main() {
    Stack s = create();
    
    int num_commands = 0;
    scanf("%d", &num_commands);
    getchar();
    
    char command_line[MAX_CAPACITY] = "";
    
    for (int i = 0; i < num_commands; i++) {
        fgets(command_line, MAX_CAPACITY, stdin);
        command_line[strcspn(command_line, "\n")] = '\0';  // 개행 제거
        
        char* command = strtok(command_line, " ");
        
        if (strcmp(command, "push") == 0) {
            int number = atoi(strtok(NULL, " "));
            push(s, number);
        }
        else if (strcmp(command, "pop") == 0) {
            printf("%d\n", pop(s));
        }
        else if (strcmp(command, "size") == 0) {
            printf("%d\n", s->num);
        }
        else if (strcmp(command, "empty") == 0) {
            printf("%d\n", is_empty(s));
        }
        else if (strcmp(command, "top") == 0) {
            if (is_empty(s) == 0){
                printf("%d\n", s->top->data);
            }
            else {
                printf("%d\n", -1);
            }
        }

    }
}
