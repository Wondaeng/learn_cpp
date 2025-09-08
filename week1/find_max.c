#include <stdio.h>

int main() {
    int input_number, max_number, max_index;
    max_number = 0;

    for (int i = 1; i <= 9; i++) {
        scanf("%d\n", &input_number);
        if (input_number > max_number) {
            max_number = input_number;
            max_index = i;
        }    
    }
    printf("%d\n", max_number);
    printf("%d\n", max_index);
}
