#include <stdio.h>

int main() {
    int num1, num2;
    char op_symbol;
   scanf("%d %d %c", &num1, &num2, &op_symbol);
    
    switch(op_symbol){
        case '+':
            printf("%d\n", num1 + num2);
            break;
        case '-':
            printf("%d\n", num1 - num2);
            break;
        case '*':
            printf("%d\n", num1 * num2);
            break;
        case '/':
            if (num2 == 0){
                printf("Cannot divide by zero.\n");
            } else {
                printf("%.2f\n", (float)num1 / (float)num2);
            }
            break;
        case '%':
            printf("%d\n", num1 % num2);
            break;
        default:
            printf("%c is not a supported operator.", op_symbol);
            break;
    }

    return 0;
}

