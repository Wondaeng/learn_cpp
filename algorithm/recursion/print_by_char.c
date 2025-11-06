#include <stdio.h>


void my_print(char* str) {
    if (*str == '\0') {
        return;
    }
    else {
        printf("%c\n", *str);
        my_print(str + 1);
    }
}

    
int main() {
    my_print("world");
}

/*
Output: 

w
o
r
l
d

*/
