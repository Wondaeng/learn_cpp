#include <stdio.h>


int my_strlen(char* str) {
    if (*str == '\0') {
        return 0;
    }
    else {
        printf("%s\n", str);
        return (1 + my_strlen(str + 1));
    }
}

    
int main() {
    int len = my_strlen("world");
    printf("%d", len);
}

/*
Output: 

world
orld
rld
ld
d
5

*/
