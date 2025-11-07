#include <stdio.h>
#include <stdlib.h>


int compare(const void *a, const void *b) {
    int va = *(const int*)a;
    int vb = *(const int*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

int main() {
	int n = 0;
	scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; i++) {
        int temp = 0;
        scanf("%d", &temp);
        arr[i] = temp;
    }
    
    qsort(arr, n, sizeof(int), compare);
    
    int m = 0;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int temp = 0;
        scanf("%d", &temp);
        
        int is_found = 0;
        
        int begin = 0;
        int end = n - 1;
        // binary search
        while (begin <= end) {
            int middle = (begin + end) / 2;
            if (temp == arr[middle]) {
                is_found = 1;
                break;
            }
            else if (temp < arr[middle]) {
                end = middle - 1;
            }
            else if (temp > arr[middle]) {
                begin = middle + 1;
            }
        }
        
        if (is_found) {
            printf("1\n");
        }
        else {
            printf("0\n");
        }
    }
}
