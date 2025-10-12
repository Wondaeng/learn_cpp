#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

struct node {
	Item data;
	struct node* next;
};

struct stack_type {
	struct node* top;
};


static void terminate(const char* message) {

	printf("%s\n", message);
	exit(EXIT_FAILURE);

}


Stack create() {

	Stack s = (Stack)malloc(sizeof(struct stack_type));
	if (s == NULL) {
		terminate("Error in create: stack could not be created.");
	}
	s->top = NULL;
	return s;

}


void destroy(Stack s) {  // 각각의 node들을 free시켜 주고, top을 free

	make_empty(s);
	free(s);

}


void make_empty(Stack s) {

	while (!is_empty(s)) {
		pop(s);
	}

}


bool is_empty(Stack s) {

	return s->top == NULL;

}


void push(Stack s, Item i) {

	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	if (new_node == NULL) {
		terminate("Error in push: stack is full");  // 메시지가 왜 stack is full 임? 갑자기 
	}

	new_node->data = i;
	new_node->next = s->top;
	s->top = new_node;

}


Item pop(Stack s) {
	struct node* old_top;
	Item i;

	if (is_empty(s)) {
		terminate("Error in pop: stack is empty.");
	}

	old_top = s->top;
	i = old_top->data;
	s->top = old_top->next;
	free(old_top);
	return i;

}


Item peek(Stack s) {

	if (is_empty(s)) {
		terminate("Error in pop: stack is empty.");
	}
	return s->top->data;

}