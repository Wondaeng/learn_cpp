#include "stack.h"
#define MAX_CAPACITY 100


// 2. (단방향) 연결리스트를 이용한 구현
/*
데이터 삽입 (push):
head나 tail이나 비슷함

데이터 삭제 (pop):
top이 head 노드를 가리키면, head를 삭제하기 전에 다음 노드의 주소를 head->next로 저장해 둘 수 있음
top이 tail 노드를 가리키면, 어쨌거나 top이 tail 노드의 주소를 가리키고 있기 때문에 한번은 pop할 수 있음
그러나, 이렇게 되면 단방향 연결리스트는 노드를 거꾸로 거슬러 올라갈 수 없기 때문에 top은 더이상 새로운 tail을 가리키지 못하고
따라서 추가적인 pop(i.e., 새로운 tail에 접근 후 삭제)이 불가능해짐 

* 그럼 끝에 두개를 알고 있으면 되지 않는가? 아님. 어쨌거나 삭제를 계속하면 점점 앞의 노드를 알아야 하므로 결과적으로 모든 노드의 주소를 알아야하는 것과 동일함.

*/ 

struct node {
	char* data;  // 문자열을 저장하는 스택이라고 가정
	struct node* next;
};
typedef struct node Node;

Node* top = NULL;  // Node 포인터 변수 생성

void push(char* item) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = item;
	p->next = top;
	top = p;
}


char* pop() {
	if (is_empty()) {
		return NULL;  // 사용자가 이런 특수한 예외사항이 벌어졌음을 인지할 수 있게 하는 것이 더 좋은 방법임. silent하게 return하는 것은 좋은 방법은 아님.
	}
	char* result = top->data;
	top = top->next;
	return result;

	/*
	
	malloc 메모리를 free하려면:
	Node* temp = top;  // head 노드 주소 보관
	char* result = top->data;
	top = top -> next;
	free(temp);
	return result;
	*/
}


char* peek() {
	if (is_empty()) {
		return NULL;
	}
	return top->data;
}


int is_empty() {
	return top == NULL;
}
