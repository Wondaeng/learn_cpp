#include <stdio.h>

int main() {
    int total_num;
    scanf("%d", &total_num);
    
    int min, max, num;
    for (int i = 0; i < total_num; i++) {
        scanf("%d", &num);
        if (i == 0) {
            min = num;
            max = num;
        }
        if (num < min) {
            min = num;
        }
        if (num > max) {
            max = num;
        }
    }
    printf("%d %d\n", min, max);
    return 0;
}
