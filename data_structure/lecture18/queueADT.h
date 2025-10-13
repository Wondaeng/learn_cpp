#ifndef QUEUEADT_H
#define QUEUEADT_H

#include <stdbool.h>  /* C99 only */

typedef int Item;
typedef struct queue_type* Queue;

Queue create();
void destroy(Queue q);
void make_empty(Queue q);
bool is_empty(Queue q);
void enqueue(Queue q, Item i);
Item dequeue(Queue q);
Item peek(Queue q);
int get_size(Queue q);  /* queue 경우, 데이터 개수를 알아야 할 경우가 stack보다 많음 */ 

#endif
