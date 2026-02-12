#include <stdio.h>

int main(void) {
    int num1 = 0;
    int num2 = 0;
    
    scanf("%d %d", &num1, &num2);
    
    int product = num1 * num2;    
    
    int temp = 0;  /* placeholder to save previous num2 */
    while (num2 > 0) {
        temp = num2;
        num2 = num1 % num2;
        num1 = temp;
    }
    
    int gcd = num1;
    int lcm = product / gcd;
    
    printf("%d\n", gcd);
    printf("%d\n", lcm);
    return 0;
}
