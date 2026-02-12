#include <stdio.h>

int main() {
    char word[1000001]; 
    int counter = 0;

    while (scanf("%s", word) != EOF) {
        counter++;
    }

    printf("%d\n", counter);
    return 0;
}
