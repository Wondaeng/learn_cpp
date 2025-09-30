#include <stdio.h>
#include <stdlib.h>

#define MAX_POLYS 100


/* 다항식을 항들의 연결리스트로 표현 */
struct term {
	int coef;
	int expo;
	struct term* next;
};
typedef struct term Term;


struct polynomial {
	char name;
	Term* first;
	// int size = 0;  // MQ1. C에선 구조체 정의 안에 멤버 변수에 초기값 줄 수 없다는데?
	int size;
};
typedef struct polynomial Polynomial;

Polynomial* polys[MAX_POLYS];  // 다항식의 포인터들의 배열
int n = 0;  // 저장된 다항식의 개수



/*
구조체 객체들을 동적메모리 할당을 이용해 만들어 사용하는 경우에 자주하는 실수:
malloc으로 구조체 객체를 만든 다음에 그 구조체 객체의 멤버 변수를 초기화 해주는 것을
깜빡해서 오류 발생?
--> malloc으로 포인터 만들면 곧바로 멤버 변수 초기화 하기
--> 매번 생성시 마다 하는 것 보다, 함수를 하나 만들어 반복 사용
*/

Term* create_term_instance() {
	Term* t = (Term*)malloc(sizeof(Term));
	t->coef = 0;
	t->expo = 0;
	return t;
}


Polynomial* create_polynomial_instance(char name) {
	Polynomial* ptr_poly = (Polynomial*)malloc(sizeof(Polynomial));
	ptr_poly->name = name;
	ptr_poly->size = 0;
	ptr_poly->first = NULL;
	return ptr_poly;
}


void add_term(int c, int e, Polynomial* poly) {
	/*
	Polynomical 포인터 poly가 가리키는 다항식에 새로운 하나의 항 (c, e)를 추가하는 함수
	- 추가하려는 항과 동일 차수의 항이 이미 있는 경우: 기존 항의 계수에 더하기
	- 그렇지 않은 경우: 새로운 항을 삽입 (항들의 차수의 내림차순으로 항상 정렬)
	
	새로운 항이 삽입될 위치를 찾기 위해선, 새로운 항보다 차수가 작거나 같은 항이
	나올 때 까지 첫번째 항부터 순서대로 검사해야한다
	*/

	if (c == 0) {
		return;
	}

	Term* p = poly->first;
	Term* q = NULL;
	while (p != NULL && p->expo > e) {
		q = p;
		p = p->next;
	}

	if (p != NULL && p->expo == e) {
		p->coef += c;
		if (p->coef == 0) {  // 더했더니 0이면 q의 다음 노드를 삭제해야한다
			if (q == NULL) {  // e가 최고차항이라 while문을 바로 빠져나온 경우
				poly->first = p->next;  // 첫번째 항을 삭제하고 다음(두번째) 항을 첫번쨰로 함
			}
			else {
				q->next = p->next;
			}
			poly->size--;
			free(p);
		}
		return;
	}

	Term* term = create_term_instance();
	term->coef = c;
	term->expo = e;

	if (q == NULL) {
		term->next = poly->first;
		poly->first = term;
	}
	else {
		term->next = p;
		q->next = term;
	}
	poly->size++;
}
