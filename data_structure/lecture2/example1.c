#include <stdio.h>
#define BUFFER_SIZE 100

int main() {
    
    char* words[100];
    int n = 0; // number of strings
    char buffer[BUFFER_SIZE];
    
    while (n < 4 && scanf("%s", buffer) != EOF) {
        // words[n] = buffer; --> buffer는 배열의 시작 주소값으로 루프마다 바뀌지 않음. (왜 안바뀌나?)
        // 따라서 가장 마지막에 들어간 값으로 덮어씌워지게 됨 
        words[n] = strdup(buffer);
        n++;
        
    }
    
    for (int i = 0; i < 4; i++) {
        printf("%s\n", words[i]);
    }
}

/*

char * strdup(char *s) {
    char *p;
    p = (char *)malloc(strlen(s)+1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}


*/
