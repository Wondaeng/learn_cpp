#include <stdio.h>

int main() {
    int num1, num2;
    while (scanf("%d %d", &num1, &num2) && (num1 != 0 || num2 != 0)) {
        printf("%d\n", num1 + num2);
    }
    return 0;
}
