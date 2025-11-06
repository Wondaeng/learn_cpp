#include <stdio.h>


void my_print(char* str) {
    if (*str == '\0') {
        return;
    }
    else {
        my_print(str + 1);
        printf("%c\n", *str);
    }
}

    
int main() {
    my_print("world");
}

/*
Output: 

d
l
r
o
w

*/
