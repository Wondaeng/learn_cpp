#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "my_strings.h"

/*
read() 함수

read(int fides, void *buf, size_t nbytes);

*/


/*
VLA 사용을 피하려 하다보니 buffer를 함수 밖에서 만들고 그 포인터를 넘기는 방식으로 구현
생각했던 대안들:
1. 매크로를 read_line안에서 쓰자 -> 버퍼 사이즈에 대한 유연성이 줄어드는 것 같아서 좀 별로
2. malloc/free 활용 -> malloc이 엄청 비싼 작업이라 기억해서 이것도 별로 (어차피 strcat에서 부르니까 상관없나? 잘모르겠음)
*/
char* read_line(const int fd, char* buffer, char** backup, size_t buffer_size) {
    char* temp = strdup("");

    if (*backup != NULL) {
        temp = strjoin(*backup, temp);  // backup 내용 이어붙이기
        free(*backup);
        *backup = NULL;  // dangling pointer 방지
    }

    size_t bytes = 0;
    while ((bytes = read(fd, buffer, buffer_size)) > 0) {
        
        buffer[bytes] = '\0';
        
        // join new string from the buffer to 'temp' variable
        char* old_temp = temp;
        temp = strjoin(temp, buffer);
        free(old_temp);

        char* newline_ptr = strchr(temp, '\n');
        if (newline_ptr) {  // if newly added string contains '\n'
            // put strings before '\n' to line (which will be returned)
            size_t len_line = (size_t)(newline_ptr - temp);
            char* line = malloc(len_line + 1);
            strncpy(line, temp, len_line);
            line[len_line] = '\0';

            // put string after '\n' to backup
            *backup = strdup(newline_ptr + 1);

            free(temp);
            return line;
        }
    }
    
    if (bytes == -1) {        /* read 에러 */
        free(temp);
        return NULL;
    }

    // EOF 처리 (\n 없이 끝났을 경우)
    if (*temp != '\0') {  // temp가 비어있지 않다면
        return temp;  // 마지막 줄 반환 --> while 루프 안에서 line을 반환하는 것과 동일함. 따라서 호출자가 사용이 끝나면 책임지고 free 해줘야함
    }

    free(temp);
    return NULL; 
}




int get_next_line(const int fd, char** line) {
    /*
    fd: file descriptor (0: stdin 1: stdout 2:stderr?)
    char: 문자열(char*)을 가르키는 포인터

    [헷갈렸던 포인트: 왜 char* 가 아니라 char**인가?]
    - char* p는 문자열의 첫 문자의 주소를 가르키는 포인터 변수
    - char** pp는 이 포인터 변수 p의 주소를 가르키는 포인터 변수

    */

    /*
    여기에 read를 통해 BUFF_SIZE만큼 문자열을 받음
    (+1은 '\0' 널문자 포함하기 위한 공간)
    */
    char buffer[BUFF_SIZE + 1];  
    
    /*
    여기에 \n 또는 EOF가 등장할 때 까지 buffer에서 받은 문자열을 쌓음
    static인 이유? (vs malloc) 데이터 영역에 저장 vs 힙 영역에 저장 + 어쨌거나 malloc으로 해도 포인터를 계속 들고있어야 함
    */
    static char* backup = NULL;
    *line = read_line(fd, buffer, &backup, BUFF_SIZE);
    
    if (*line == NULL)
        return 0;  // EOF
    return 1;      // success
}

/*
get_next_line: 

fd의 파일을 BUFF_SIZE만큼 계속 읽다가 1) 한줄이 완성 되거나 2) EOF에 도달하면 함수가 끝나고
주어진 문자열의 포인터가 가르키던 주소값을 바꿈 (즉, 다른 문자열을 가르키게 바꿈)
--> MQ2. 여기서 그럼 기존에 있던 문자열은 어떻게 되는건가? char* 가 어떤식으로 이 함수에 주어지는 건지 잘 모르겠음


*/
