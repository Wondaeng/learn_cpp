#include <stdio.h>
#include <ctype.h>
#define BUFFER_SIZE 80


int main() {
    char line[BUFFER_SIZE];
    while(1) {
        print("$ ")
        int length = read_line_with_compression(line, BUFFER_SIZE);
        printf("%s:%d\n", line, length);
    }
} 


int read_line_with_compression(char compressed[], int limit) {
    int ch, i = 0;
    while ((ch = getchar()) != '\n') {
        if (i < limit - 1 && (!isspace(ch) || i > 0 && !isspace(compressed[i - 1]))) {
            compressed[i++] = ch;
        }
    }
    if (i > 0 && isspace(compressed[i - 1])) {
        i--; 
    } 
    compressed[i] = '\0';
    return 1;
}
