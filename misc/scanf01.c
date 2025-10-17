/*

주제: scanf() 함수의 작동 원리 파악 
내용: format string에서 conversion specification이 아닌 ordinary character가 처리되는 중에 매칭에 실패했을 경우 입력 스트림에 어떤 영향이 있는지 확인

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main() {
	int a, b, c, d;
	scanf("%d,%d", &a, &b);
	printf("a: %d\n", a);
	scanf("%d", &c);
	printf("b: %d\n", b);
	printf("c: %d\n", c);
	scanf("%d", &d);
	printf("d: %d\n", d);
}

/*
실행 결과:

10-20  // first user's input
a: 10
b: -858993460
c: -20
30  // second user's input
d: 30

// 주석 처리 된 부분이 유저가 실제로 값을 타이핑, 엔터를 친 부분
*/

/*

해석: 
scanf()의 첫번째 호출에서 10을 읽고 난 뒤 ','가 나오길 기대했으나 '-'가 나옴으로 인해 scanf()가 실패, 종료. 이떄 읽었던 '-'는 다시 입력 스트림으로 되돌려짐.
따라서 현재 입력 스트림에는 "-20"이 남아있는 상황.
scanf()의 두번째 호출에선 이 남아있는 "-20"을 그대로 이어받음. 이로 인해 유저가 뭘 입력할 틈도 없이 자동으로 두번째 scanf()는 끝나버리며 b와 c의 값까지 출력됨. 
다만, 변수 b에는 첫번째 scanf()의 호출에서 값이 넣어져야하는데 이때 실패하였으므로 초기화가 제대로 되지 않아 알수없는 값이 출력되었으며 "-20"이 두번째 scanf()의 호출에 의해 변수 c에 들어간 것을 확인할 수 있음.
입력버퍼가 다시 비게됨 (아마 \n은 남아있을것? scanf자체가 \n를 만나면 종료되긴 하지만 이것도 "peek"만 하고 다시 되돌려 놓는 것으로 알고있음. 하지만 scanf에서 %d를 처리할 땐 공백문자를 어차피 무시하므로 문제 X).
마지막으로 scanf()의 세번째 호출은 문제없이 정상 작동함.

*/
