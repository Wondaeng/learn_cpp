#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POLYS 100
#define BUFFER_LENGTH 100

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


int eval_term(Term* term, int x) {
	int result = term->coef;
	for (int i = 0; i < term->expo; i++) {
		result *= x;
	}
	return result;
}


int eval_poly(Polynomial* poly, int x) {
	int result = 0;
	Term* t = poly->first;
	while (t != NULL) {
		result += eval_term(t, x);
		t = t->next;
	}
	return result;
}


void print_term(Term* pTerm) {
	if (pTerm->expo == 0) {
		printf("%d", pTerm->coef);
	}
	else if (pTerm->expo == 1) {
		if (pTerm->coef == 1) {
			printf("x");
		}
		else if (pTerm->coef == -1) {
			printf("-x");
		}
		else {
			printf("%dx", pTerm->coef);
		}
	}
	else {
		if (pTerm->coef == 1) {
			printf("x^%d", pTerm->expo);
		}
		else if (pTerm->coef == -1) {
			printf("-x^%d", pTerm->expo);
		}
		else {
			printf("%dx^%d", pTerm->coef, pTerm->expo);
		}
	}
}


void print_poly(Polynomial* p) {
	printf("%c=", p->name);
	Term* t = p->first;
	while (t != NULL) {
		print_term(t);
		if (t->next != NULL && t->next->coef > 0) {
			printf("+");
		}
		t = t->next;
	}
}


void handle_print(char name) {
	for (int i = 0; i < n; i++) {
		if (name == polys[i]->name) {
			print_poly(polys[i]);
			printf("\n");
			return;
		}
	}
	printf("There is no polynomial named '%c'\n", name);
}


void handle_calc(char name, char* x_str) {
	for (int i = 0; i < n; i++) {
		if (name == polys[i]->name) {
			Polynomial* ptr_poly = polys[i];
			int x = atoi(x_str);
			int result = eval_poly(ptr_poly, x);
			printf("%d\n", result);
			return;
		}
	}
	printf("There is no polynomial named '%c'\n", name);
	return;
}


void erase_blanks(char* expression) {
	int len = strlen(expression);
	for (int i = 0; i < len; i++) {
		if (expression[i] == ' ') {
			for (int j = i; j < len; j++) {
				expression[j] = expression[j + 1];
			}
			len--;
			i--;
		}
	}
	expression[len] = '\0';  // for safety
}

int parse_and_add_term(char* expr, int begin, int end, Polynomial* p_poly) {
	int i = begin;
	int sign_coef = 1, coef = 0, expo = 1;
	if (expr[i] == '+') {
		i++;
	}
	else if (expr[i] == '-') {
		sign_coef = -1;
		i++;
	}
	while (i < end && expr[i] >= '0' && expr[i] <= '9') {
		coef = coef * 10 + (int)(expr[i] - '0');
		i++;
	}

	if (coef == 0) {
		coef = sign_coef;
	}
	else {
		coef *= sign_coef;
	}

	if (i >= end) {  // 항이 끝나버렸다 => 계수부분만 있다 (차수 0)
		add_term(coef, 0, p_poly);
		return 1;
	}

	if (expr[i] != 'x') {
		return 0;
	}
	i++;

	if (i >= end) {
		add_term(coef, 1, p_poly);
		return 1;
	}

	if (expr[i] != '^') {
		return 0;
	}
	i++;

	expo = 0;
	while (i < end && expr[i] >= '0' && expr[i] <= '9') {
		expo = expo * 10 + (int)(expr[i] - '0');
		i++;
	}
	add_term(coef, expo, p_poly);
	return 1;
}


void destroy_polynomial(Polynomial* ptr_poly) {
	if (ptr_poly == NULL) {
		return;
	}
	Term* t = ptr_poly->first;
	Term* tmp;
	while (t != NULL) {
		tmp = t;
		t = t->next;
		free(tmp);
	}
	free(ptr_poly);
}


Polynomial* create_by_add_two_polynomials(char name, char f, char g) {
	Polynomial* ptr_poly = create_polynomial_instance(name);
	Polynomial* f_poly = NULL;
	Polynomial* g_poly = NULL;
	for (int i = 0; i < n; i++) {
		if (polys[i]->name == f) {
			f_poly = polys[i];
		}
		if (polys[i]->name == g) {
			g_poly = polys[i];
		}
	}
	
	if (f_poly == NULL || g_poly == NULL) {
		destroy_polynomial(ptr_poly);
		printf("There is no such polynomial %c or %c", f, g);
		return NULL;
	}

	Term* t = f_poly->first;
	while (t != NULL) {
		add_term(t->coef, t->expo, ptr_poly);
		t = t->next;
	}

	t = g_poly->first;
	while (t != NULL) {
		add_term(t->coef, t->expo, ptr_poly);
		t = t->next;
	}

	return ptr_poly;
}


Polynomial* create_by_parse_polynomial(char name, char* body) {
	Polynomial* ptr_poly = create_polynomial_instance(name);

	int i = 0, begin_term = 0;
	while (i < strlen(body)) {
		if (body[i] == '+' || body[i] == '-') {
			i++;
		}
		while (i < strlen(body) && body[i] != '+' && body[i] != '-') {
			i++;
		}
		int result = parse_and_add_term(body, begin_term, i, ptr_poly);
		if (result == 0) {
			destroy_polynomial(ptr_poly);
			return NULL;
		}
		begin_term = i;
	}
	return ptr_poly;
}


void insert_polynomial(Polynomial* ptr_poly) {
	for (int i = 0;i < n; i++) {
		if (polys[i]->name == ptr_poly->name) {
			destroy_polynomial(polys[i]); // 기존 다항식은 free 해야함
			polys[i] = ptr_poly;
			return;
		}
	}
	polys[n++] = ptr_poly;
}


void handle_definition(char* expression) {
	erase_blanks(expression);

	char* f_name = strtok(expression, "=");
	if (f_name == NULL || strlen(f_name) != 1) {
		printf("Unsupported command.");
		return;
	}

	char* exp_body = strtok(NULL, "=");
	if (exp_body == NULL || strlen(exp_body) <= 0) {
		printf("Invalid expression format.--");
		return; 
	}

	if (exp_body[0] >= 'a' && exp_body[0] <= 'z' && exp_body[0] != 'x') {
		char* former = strtok(exp_body, "+");
		if (former == NULL || strlen(former) != 1) {
			printf("Invalid expression format.");
			return;
		}
		char* later = strtok(NULL, "+");
		if (later == NULL || strlen(later) != 1) {
			printf("Invalid expression format.");
			return;
		}
		
		Polynomial* pol = create_by_add_two_polynomials(f_name[0], former[0], later[0]);

		if (pol == NULL) {
			printf("Invalid expression format.");
			return;
		}
		insert_polynomial(pol);
	}
	else {
		Polynomial* pol = create_by_parse_polynomial(f_name[0], exp_body);
		if (pol == NULL) {
			printf("Invalid expression format.");
			return;
		}
		insert_polynomial(pol);
	}
}


int read_line(FILE* fp, char str[], int n) {
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		if (i < n) {
			str[i++] = ch;
		}
	}
	str[i] = '\0';
	return i;
}


void process_command() {
	char command_line[BUFFER_LENGTH];
	char copied[BUFFER_LENGTH];
	char* command, * arg1, * arg2;

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) {
			continue;
		}
		strcpy(copied, command_line);
		command = strtok(command_line, " ");
		if (strcmp(command, "print") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			handle_print(arg1[0]);
		}
		else if (strcmp(command, "calc") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			handle_calc(arg1[0], arg2);
		}
		else if(strcmp(command, "exit") == 0) {
			break;
		}
		else {
			handle_definition(copied);
		}
	}
}

int main() {
	process_command();  
	return 0;
}
