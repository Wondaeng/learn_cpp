#include <stdio.h>
#include <string.h>

int main() {
    /*
    char str[] vs char* str --> 후자는 string literal이 됨
    */
    char str[] = "now # is the time # to start preparing ### for the exam#";
    char delim[] = "#";
    char* token;
    
    /*
    first call: strtok returns pointer of the start of the first token
    e.g., strtok(str, delim);
    next call: pointer of the start of following tokens
    e.g., strtok(NULL, delim);
    NOTE: strtok actually replace delimeter with '\0' null character
    */
    token = strtok(str, delim);
    
    while (token != NULL) {
        printf("next token is: %s:%d\n", token, strlen(token));
        token = strtok(NULL, delim);
    }
    return 0;
}
