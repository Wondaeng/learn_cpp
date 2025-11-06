#include <stdio.h>

// sequential search
int search1(int data[], int n, int target) {
    for (int i = 0; i < n; i++) {  // 인덱스를 0부터 n-1까지 순회
        if (data[i] == target) {
            return i;
        }
    }
    return -1;
}


// recursive version
int search2(int data[], int begin, int end, int target) {
    if (begin > end) {
        return -1;
    }
    else if (target == data[begin]) {
        return begin;
    }
    else {
        return search2(data, begin + 1, end, target);
    }
}


// recursive version
int search3(int data[], int begin, int end, int target) {
    if (begin > end) {
        return -1;
    }
    else if (target == data[begin]) {
        return begin;
    }
    else {
        return search3(data, begin, end - 1, target);
    }
}
