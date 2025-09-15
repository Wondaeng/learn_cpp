#include <stdio.h>

int main() {
    int num_card = 0;
    int threshold = 0;
    
    scanf("%d %d", &num_card, &threshold);
    
    int cards[100] = {0, };
    
    for (int i = 0; i < num_card; i++) {
        scanf("%d", &cards[i]);
    }
    
    int sum_max = 0;
    
    for (int i = 0; i < (num_card - 2); i++) {
        int sum = 0;
        for (int j = i + 1; j < (num_card - 1); j++) {
            for (int k = j + 1; k < (num_card); k++) {
                sum = cards[i] + cards[j] + cards[k];
                if ((sum >= sum_max) && (sum <= threshold)) {
                    sum_max = sum;
                }
            }
        }
    }
    printf("%d", sum_max);
    return 0;
}
