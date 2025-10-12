
#ifndef STACK_H
#define STACK_H

#include "pos.h"
#include <stdbool.h>  /* C99 only --> bool 타입 정의 가능 */


typedef Position Item;  // int가 아닌 Position 구조체를 Item으로서 받을 계획 

typedef struct stack_type* Stack;  // stack_type* 를 Stack으로 하겠다

Stack create();
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);

#endif