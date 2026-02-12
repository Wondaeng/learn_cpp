#include <stdio.h>

int get_factorial(int n) {
    int product = 1;
    for (int i = 2; i <= n; i++) {
        product *= i;
    }
    return product;
}


int main() {
    int n = 0;
    int k = 0;
    
    scanf("%d %d", &n, &k);
    
    /* n! / (k! * (n-k)!) */
    int combination = get_factorial(n) / (get_factorial(k) * get_factorial(n-k));
    printf("%d", combination);
    return 0;
}
