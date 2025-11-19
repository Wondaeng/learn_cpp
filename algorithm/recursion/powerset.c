#include <stdio.h>
#include <stdlib.h>

char data[] = "abcdef";
int length = 6;
int* include;

void power_set(int k) {
    if (k == length) {
        for (int i = 0; i < length; i++) {
            if (include[i]) {
                printf("%c ", data[i]);
            }
        }
        printf("\n");
        return;
    }

    include[k] = 0;
    power_set(k + 1);

    include[k] = 1;
    power_set(k + 1);
}

int main() {
    include = (int*)malloc(sizeof(int) * length);

    power_set(0);

    free(include);
    return 0;
}
