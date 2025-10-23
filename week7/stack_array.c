#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CAPACITY 10000


struct stack_type {

	int* contents;  /* Item의 배열 */
	int top;

};

typedef struct stack_type* Stack;



Stack create(){

    Stack s = (Stack)malloc(sizeof(struct stack_type));
    
    s->contents = (int*)malloc(sizeof(int) * MAX_CAPACITY);
    s->top = -1;
 
    return s;
}


void push(Stack s, int i){
    s->top++;
    s->contents[s->top] = i;
}


int is_empty(Stack s){
    if (s->top == -1){
        return 1;
    }
    else {
        return 0;
    }
}


int pop(Stack s){
    if (is_empty(s)){
        return -1;
    }
    else{
        s->top--;
        return s->contents[s->top + 1];
    }
}


int main() {
    
    Stack s = create();
    
    int num_commands = 0;
    scanf("%d", &num_commands);
    getchar();  // scanf로 정수를 읽고 남은 newline 제거 (추후 fgets에 의해 읽히기 때문)
	
	for (int i = 0; i < num_commands; i++){
    	char command_line[MAX_CAPACITY] = "";
    	
        fgets(command_line, MAX_CAPACITY, stdin);
        command_line[strcspn(command_line, "\n")] = '\0';
	
	    char* command = strtok(command_line, " ");
	    // printf("%s\n", command);
	    if (strcmp(command, "push") == 0) {
	        int number_int = atoi(strtok(NULL, " "));
	        
	        push(s, number_int);
	    } 
	    else if (strcmp(command, "pop") == 0) {
	        int number = pop(s);
	        printf("%d\n", number);
	    }
	    else if (strcmp(command, "size") == 0) {
	        printf("%d\n", s->top + 1);
	    }
	    else if (strcmp(command, "empty") == 0) {
	        int result = is_empty(s);
	        printf("%d\n", result);
	    }
	    else if (strcmp(command, "top") == 0) {
	        if (is_empty(s)) {
	            printf("%d\n", -1);
	        } 
	        else{
	            printf("%d\n", s->contents[s->top]);
	        }
	    }

	}
}

