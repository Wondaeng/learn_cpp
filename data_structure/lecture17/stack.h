
#ifndef STACK_H
#define STACK_H

#include "pos.h"
#include <stdbool.h>  /* C99 only --> bool Ÿ�� ���� ���� */


typedef Position Item;  // int�� �ƴ� Position ����ü�� Item���μ� ���� ��ȹ 

typedef struct stack_type* Stack;  // stack_type* �� Stack���� �ϰڴ�

Stack create();
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);

#endif