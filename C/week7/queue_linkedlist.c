#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 10000

struct node {
    int item;
    struct node* next;
};


struct queue_type {
    struct node* front;
    struct node* rear;
    int size;
};


typedef struct queue_type* Queue;


Queue create() {
    Queue q = (Queue)malloc(sizeof(struct queue_type));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    
    return q;
}


void push(Queue q, int i) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    
    new_node->item = i;
    new_node->next = NULL;
    
    if (q->front == NULL && q->rear == NULL) {  // empty case
        q->front = new_node;
        q->rear = new_node;
    }
    else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++;
}



int is_empty(Queue q) {
    if (q->size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}


int pop(Queue q) {
    if (is_empty(q) == 1) {
        return -1;
    }
    
    int item = q->front->item;
    
    struct node* old_node = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(old_node);
    q->size--;
    
    return item;
}


int main() {
    Queue q = create();
    
	int num_commands = 0;
	scanf("%d", &num_commands);
	getchar();
	
	char command_line[MAX_LEN] = "";
	
	for (int i = 0; i < num_commands; i++) {
	    fgets(command_line, MAX_LEN, stdin);
	    command_line[strcspn(command_line, "\n")] = '\0';
	    
	    char* command = strtok(command_line, " ");
	    
	    if (strcmp(command, "push") == 0) {
	        int number = atoi(strtok(NULL, " "));
	        push(q, number);
	    }
	    else if (strcmp(command, "pop") == 0) {
	        printf("%d\n", pop(q));
	    }
	    else if (strcmp(command, "size") == 0) {
	        printf("%d\n", q->size);
	    }
	    else if (strcmp(command, "empty") == 0) {
	        printf("%d\n", is_empty(q));
	    }
	    else if (strcmp(command, "front") == 0) {
	        if (is_empty(q) != 1) {
	            printf("%d\n", q->front->item);
	        }
	        else {
	            printf("%d\n", -1);
	        }
	    }
	    else if (strcmp(command, "back") == 0) {
	        if (is_empty(q) != 1) {
	            printf("%d\n", q->rear->item);
	        }
	        else {
	            printf("%d\n", -1);
	        }
	    }
	}
}


