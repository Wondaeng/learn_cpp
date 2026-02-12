#include <stdio.h>

int main(void) {
    int n = 0;
    int number = 0;
    int div_count = 0;
    int prime_count = 0;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &number);
        
        for (int j = 2; j <= number; j++) {
            if (number % j == 0) {
                div_count++;
            }        
        }
        if (div_count == 1) {
            prime_count++;
        }
        div_count = 0;
    }
    printf("%d", prime_count);
    return 0;
}
