#include <stdio.h>

int main() {
    int num_testcase;
    scanf("%d", &num_testcase);
    
    for (int i = 0; i < num_testcase; i++) {
        int num1, num2;
        scanf("%d %d", &num1, &num2);
        printf("%d\n", num1 + num2);
    }
    return 0;
}
