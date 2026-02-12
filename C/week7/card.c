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
    
    int num_cards = 0;
    scanf("%d", &num_cards);
    
    for (int i = 1; i <= num_cards; i++) {
        push(q, i);
    }
    
    while (q->size > 1) {
        int first = pop(q);
        int second = pop(q);
    
        push(q, second);
    }
    
    int last = pop(q);
    printf("%d", last);
}
