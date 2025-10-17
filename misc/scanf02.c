/*

주제: scanf() 함수의 작동 원리 파악 
내용: scanf()에서 끝에 '\n'을 넣으면 어떤 영향이 있는지 확인

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main() {
	int a, b;
	scanf("%d\n", &a);
	printf("a: %d\n", a);
	scanf("%d", &b);
	printf("b: %d\n", b);
}

/*

실행결과:
10  // first user's input
5  // second user's input
a: 10
b: 5

*/

/*

해석:
첫 scanf() 호출의 format string 끝에 '\n'가 있음. '\n'는 scanf()에선 white-space character로 공백과 동일하게 취급됨.
scanf()의 내부를 보면 format string을 처리하기 문자를 하나씩 받으면서 포인터를 전진시키는데, 이때 공백을 만나게 되면 getchar()가 실행 됨.
따라서 유저입장에선 이미 정수를 하나 치고 입력이 끝난건데, scanf() 입장에선 getchar()가 실행되어 입력을 기다리고 있는 상태가 되어버리는 문제가 발생하게 됨.
따라서 다른 정수 (위의 예제에선 5)를 한번 더 입력해주면 이 상황이 풀리게 됨.
단, 이 5는 입력 버퍼에 남게 되므로 scanf()를 한번 더 불러오면 별도의 유저 입력 (타이핑) 없이 바로 이 값이 scanf()에 의해 읽히게 됨 (변수 b가 이것을 보여줌).

*/
