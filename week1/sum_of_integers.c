#include <stdio.h>

int main() {
    int length;
    scanf("%d", &length);
    
    int sum = 0;
    char number;
    for (int i = 0; i < length; i++) {
        scanf(" %c", &number);
        sum += number - '0';
    }
    printf("%d", sum);
}
