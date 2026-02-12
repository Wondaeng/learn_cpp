#include <stdio.h>

int main() {
    int number;
    scanf("%d", &number);

    for (int i = 1; i <= 9; i++){
        int multiple = number * i;
        printf("%d * %d = %d\n", number, i, multiple);
    }
    return 0;
}
