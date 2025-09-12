#include <stdio.h>

int main() {
    int num_tests = 0;
    scanf("%d", &num_tests);
    
    int test_scores[1000] = {0,};
    
    double total_score = 0;
    
    int current_score = 0;
    int max_score = 0;
    
    for (int i = 0; i < num_tests; i++) {
        scanf("%d", &current_score);
        test_scores[i] = current_score;
        if (current_score >= max_score) {
            max_score = current_score;
        }
    }

    for (int i = 0; i < num_tests; i++) {
        total_score += (double)test_scores[i] / max_score * 100;
    }
    total_score /= num_tests;
    printf("%f", total_score);
    return 0;
}
