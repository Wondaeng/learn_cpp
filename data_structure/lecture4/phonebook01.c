#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define BUFFER_SIZE 100

/* 각각의 이름 or 전화번호는 string = char 배열 --> char 배열의 배열 = char 포인터(*)의 배열 */
char* names[CAPACITY];    /* names */
char* numbers[CAPACITY];    /* phone numbers */
int n = 0;    /* number of people in phone directory */

/*

* C언어의 메모리 레이아웃: [ code ] - [ data section ] - [ {heap (동적으로 할당된 메모리 - malloc)} -> <- {stack} ]
* [] --> 변하지 않음 / {} --> 변함

유형1. 전역변수 (global variable):
- 함수의 외부에 선언된 변수들
- 프로그램이 시작될 때 메모리가 할당되며, 프로그램이 종료될 때 까지 유지된다
- Data section이라고 부르는 메모리 영역에 위치한다

유형2. 지역변수 (local/automatic variable):
- 함수의 내부에 선언된 변수들
- 자신이 속한 함수가 호출될 때 메모리가 할당되며 함수가 return될때 소멸한다
- 스택(stack)이라고 부르는 영역에 위치한다

유형3. 동적 메모리 할당 (dynamic memory allocation):
- 아무때나 malloc등의 함수를 호출하여 필요한 크기의 메모리를 할당할 수 있다
- 동적으로 할당된 메모리는 힙(heap)이라고 부르는 영역에 위치한다
- 동적으로 할당된 메모리는 명시적으로 free() 함수를 호출하여 반환하지 않는 한 계속 유지된다

*/

void add() {
/* 
Q1. strdup과 strcpy의 차이는? A1. strcpy(p, s): s 배열을 p 배열로 복사 vs strdup(s) 동적메모리할당(malloc)을 통해 새 포인터 주소 반환 
buf1, buf2 --> 지역변수로, lifetime이 자신이 속해있는 함수가 호출되는 순간 생성, 종료되는 순간 소멸
names, numbers 배열의 요소가 buf1 이나 buf2를 가르키게 되면, 함수가 종료되는 순간 이 지역변수들을 사라지므로 저장이 정상적으로 되지 않음

(슬라이드 내용: buf1은 스택에 할당된 메모리이므로 add 함수가 return 되고 나면 소멸된다.
따라서 buf1에 저장된 문자열을 복제한 후 배열 names[0]에 복제된 배열의 주소를 저장해야한다.
복제된 배열은 strdup 함수 내에서 malloc으로 (heap에) 할당된 메모리이므로, add 함수가 종료된 후에도 소멸하지 않는다.)
*/
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1);  
	scanf("%s", buf2);

	names[n] = _strdup(buf1);    
	numbers[n] = _strdup(buf2);
	n++;

	printf("%s was added successfully.\n", buf1);
}


void find() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int i;    /* int i = 0; vs int i 하고 i = 0; ? */
	for (i = 0; i < n; i++) {
		if (strcmp(buf, names[i]) == 0) {
			printf("%s\n", numbers[i]);
			return;
		}
	}
	printf("No person named '%s' exists.\n", buf);
}


void status() {
	int i;
	for (i = 0; i < n; i++) {
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons,\n", n);
}

/* 
MQ1. 이 부분 로직에서 전화번호부에 단 한명만이 남았고, 그 사람을 지우려고 하면 (i = 0, n = 1)
names[0] = names[1 - 1] 로 실질적으로 삭제가 되지 않고 자기자신을 할당하게 되는데, n은 1 줄어드니까
다시 똑같은 삭제를 시도하면 다음번엔 i = 0, n = 0 이 되어서 names[0] = names[0 - 1]로 에러가 나는 것이 아닌가?

MA1. 실제로 해보니까, 문제 없이 잘 작동됨. 그 이유를 알아보니:
- add LEE 0101010 추가
- remove LEE 

하면 실제로 names[0] 에는 LEE의 주소가 남아있음 

다만, n = 0이기 때문에:
- status 명령어는 애초에 for 루프를 돌지 않아 출력되지 않음
- 또, 다시 다른 이름을 add 하면 names[0]에 새로운 이름을 할당하면서 기존의 LEE가 덮어씌워지며
*/

void remove_person() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(buf, names[i]) == 0) {
			//free(names[i]);        // 메모리 해제
			//free(numbers[i]);      // 메모리 해제
			
			names[i] = names[n - 1];
			numbers[i] = numbers[n - 1];
			n--;
			printf("'%s' was deleted successfully.\n", buf);
			return;
		}
	}
	printf("No person named '%s' exists.\n", buf);
}


int main() {
	char command[BUFFER_SIZE];
	while (1) {
		
		printf("$ ");
		scanf("%s", command);
		
		if (strcmp(command, "add") == 0) {
			add();
		}
		else if (strcmp(command, "find") == 0) {
			find();
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "remove") == 0) {
			remove_person();
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
		// 디버깅용: printf("%s %s\n", names[0], numbers[0]);
	}
	return 0;
}
