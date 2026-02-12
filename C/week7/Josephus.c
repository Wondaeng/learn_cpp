#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main() {
    int n = 0;
    int k = 0;
    
    scanf("%d", &n);
    scanf("%d", &k);
    
    int* arr = (int*)malloc(sizeof(int) * n);  // VLA는 표준이 아니라고 해서.. 원래는 int arr[n] 이었음.
    
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    
    printf("<");
    
    int killed = 0;
    int i = 0;
    
    while (killed < n) {
        int counter = 0;
        while (counter < k) {
            if (arr[i % n] != 0) {
                counter++;
            }
            if (counter != k) {
                i++;                
            }
        }
        
        killed++;
        
        if (killed < n) {
            printf("%d, ", arr[i % n]);           
        }
        else {
            printf("%d", arr[i % n]);         
        }
        

        arr[i % n] = 0;
        
    }
    
    printf(">");
}
