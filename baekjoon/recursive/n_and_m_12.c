#include <stdio.h>
#include <stdlib.h>


int compare(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y;
}


void print_sequence(int depth, int start, int* arr, int* result, int n, int m) {
    if (depth == m) {
        for (int i = 0; i < m; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        return;
    }
    
    int last_used = -1;  // 같은 depth에서 마지막으로 사용한 값
        
    for (int i = start; i < n; i++) {
        if (arr[i] == last_used) {
            continue;
        }
        
        result[depth] = arr[i];
        last_used = arr[i];
        print_sequence(depth + 1, i, arr, result, n, m);
    }
}


int main() {
    int n = 0;
    int m = 0;
    
    scanf("%d %d", &n, &m);
    
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);      
    }    
	
	qsort(arr, n, sizeof(int), compare);
    
    int* result = (int*)malloc(m * sizeof(int));
    
    print_sequence(0, 0, arr, result, n, m);
    
    free(arr);
    free(result);
    
    return 0;   
}

