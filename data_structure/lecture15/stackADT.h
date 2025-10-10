#ifndef STACKADT_H
#define STACKADT_H

#include <stdbool.h>  /* C99 only --> bool 타입 정의 가능 */

typedef int Item;  // int 데이터 타입을 Item으로 이름을 다시 바꿈 --> 왜? 지금은 정수를 저장하는 stack을 만들거지만, 나중에 자료형이 바뀐다면 다 일일히 고쳐줘야 하므로...

typedef struct stack_type* Stack;  // stack_type* 를 Stack으로 하겠다

Stack create();
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);

#endif
