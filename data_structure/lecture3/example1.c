#include <stdio.h>
#define BUFFER_SIZE 20

int main() {
    char buffer[BUFFER_SIZE];
    while (1) {
        printf("$ ");
        // scanf("%s", buffer); 공백 기준으로 짤리므로 적절치못함
        // scanf, gets --> 배열 사이즈를 초과해도 주어진 메모리를 넘어 값을 씀 (오버플로우)
        // stdin: 표준 입력 파일에 대한 포인터, fgets는 stdin뿐아닌 파일 읽어옴
        // fgets가 줄바꿈 문자"까지" 버퍼에 저장함
        fgets(buffer, BUFFER_SIZE, stdin); // line 단위 입력 (newline 기준)
        buffer[strlen(buffer) - 1] = "\0";
        printf("%s:%d\n", buffer, strlen(buffer));
    }
    return 0;
}
