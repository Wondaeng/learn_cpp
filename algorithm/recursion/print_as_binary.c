#include <stdio.h>


void print_as_binary(int n) {
    if (n < 2) {
        printf("%d", n);
    }
    else {
        print_as_binary(n / 2);
        printf("%d", n % 2);
    }
}


int main(){
    print_as_binary(14);
}

/*
Output:
1110
*/
