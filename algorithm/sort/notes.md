# 제 3장: 정렬 (sort)
## 다양한 정렬 알고리즘
| 정렬 알고리즘 | 특징 |
|---|---|
| • Bubble sort<br>• Insertion sort<br>• Selection sort | simple, slow |
| • Quicksort<br>• Merge sort<br>• Heap sort | fast |
| • Radix sort | O(N) |

## 기본적인 정렬 알고리즘
### 선택 정렬 (selection sort)
- 각 루프마다:
  - 최대 원소를 찾는다
  - 최대 원소와 맨 오른쪽 원소를 교환한다
  - 맨 오른쪽 원소를 (루프의 탐색 범위에서) 제외한다  
--> 하나의 원소만 남을 때까지 위의 루프를 반복

```
selectionSort(A[], n)
{
    for last <- n downto 2    {
        find max A[k] among A[1...last] // 가장 큰 수 A[k]를 찾는다;
        A[k] <-> A[last];  // 교환
    }
}
```
- for 루프는 총 $n-1$회 반복
- 각 루프마다 가장 큰 수를 찾기 위한 비교 횟수: $n-1, n-2, ..., 2, 1$
- 교환은 상수 작업  
--> 시간 복잡도 $T(n) = (n-1) + (n-2) + ... + 2 + 1 = O(n^2)$
