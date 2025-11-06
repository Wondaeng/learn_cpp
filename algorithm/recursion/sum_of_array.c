#include <stdio.h>


// sum from data[0] to data[n]
// MQ. 파라미터 상에서 int* data랑 동일하면... 뭐가 더 낫나?
int sum_array(int n, int data[]) {
    if (n <= 0) {
        return 0;
    }
    else {
        return data[n - 1] + sum_array(n - 1, data);
    }
}


int main(){
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8 , 9, 10};
    int sum1 = sum_array(5, arr);
    printf("%d\n", sum1);
    int sum2 = sum_array(10, arr);
    printf("%d\n", sum2);
}

/*
Output:
15
55
*/
