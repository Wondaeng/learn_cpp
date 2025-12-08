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
→ 하나의 원소만 남을 때까지 위의 루프를 반복

#### 선택 정렬 알고리즘즘
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
- 각 루프마다 가장 큰 수를 찾기 위한 비교 횟수: $n-1, n-2, \cdots, 2, 1$
(last개의 수 중에서 최대값을 찾기 위해선 last-1번의 비교가 필요)
- 교환은 상수 작업
→ 시간 복잡도 $T(n) = (n-1) + (n-2) + \cdots + 2 + 1 = \frac{n(n-1)}{2} = O(n^2)$


- 어떤 입력에 대해서도 동일한 작업을 수행하기 때문에 최선, 최악, 평균의 경우를 구분할 필요가 없이 항상 동일한 시간복잡도를 가짐

### 버블 정렬 (bubble sort)
- 기본 아이디어는 selection sort와 유사함: 정렬할 데이터 중에서 가장 큰 값을 찾아 맨 마지막 자리로 옮긴 뒤, 그 데이터는 제외하고 같은 작업을 계속 반복
- **다만,** 최댓값을 찾고 이를 마지막 요소로 만드는 세부적인 방법이 다름
→ 각 루프마다:
  - $i$번째 값을 $i+1$번째 값과 비교한다
  - $i$번째 값이 $i+1$번째 값보다 크다면 두 요소의 위치를 교환한다
  - 맨 오른쪽 원소를 (루프의 탐색 범위에서) 제외한다

#### 버블 정렬 알고리즘

```
bubbleSort(A[], n)
{
    for last <- n downto 2    {
        for i <- 1 to last - 1    {
            if (A[i] > A[i+1]) then A[i] <-> A[i+1]
        }
    }
}
```
  
시간 복잡도: $T(n) = (n-1) + (n-2) + \cdots + 2 + 1 = \frac{n(n-1)}{2} = O(n^2)$

### 선택 정렬과 버블 정렬의 비교
두 정렬 방식 모두 **비교** 횟수는 각 루프마다 $n-1, n-2, \cdots, 2, 1$번으로 동일함 **그러나:**
- 선택 정렬은 각 루프마다  $1$회의 **교환**이 일어나는 반면, 버블 정렬은 최대 $n-1, n-2, \cdots, 2, 1$회의 교환이 일어날 수 있음
- **대신,** 버블 정렬의 경우엔 주어진 배열이 이미 정렬되었는지 아닌지를 해당 루프에서 **교환이 한번이라도 일어났는지 여부**를 통해 확인이 가능하며, 정렬을 조기 종료 시킬 수 있음. 따라서 버블 정렬의 경우엔 최선의 경우 시간복잡도가 $O(n)$이 됨.
- 선택 정렬은 교환 횟수가 버블 정렬보다 일반적으로 적은 대신, 배열이 이미 정렬되었는지 감지가 불가능하여 어떤 경우에도 $O(n^2)$의 시간복잡도를 가짐.
  
두 정렬 모두 최악의 경우, 시간복잡도는 $O(n^2)$으로 동일하지만, 실제 실행시간을 상수 계수까지 비교해본다면 차이가 발생함.

#### 최악의 경우 연산 횟수 비교 ($n=1000$)

| 구분 | 선택 정렬 | 버블 정렬 | 비율 |
|---|---|---|---|
| **비교 횟수** | $\frac{n(n-1)}{2} = 499,500$ | $\frac{n(n-1)}{2} = 499,500$ | 1:1 |
| **교환 횟수** | $n-1 = 999$ | $\frac{n(n-1)}{2} = 499,500$ | 1:500 |
| **대입 연산** | $3(n-1) = 2,997$ | $\frac{3n(n-1)}{2} = 1,498,500$ | 1:500 |
| **총 연산** | $499,500 + 2,997 \approx 502,000$ | $499,500 + 1,498,500 \approx 2,000,000$ | 1:4 |

### 삽입 정렬 (insertion sort)
각 요소를 앞에서부터 차례대로 이미 정렬된 배열 부분과 비교하여, 자신의 위치를 찾아 삽입함으로써 정렬을 완성하는 알고리즘이다.  
(이미 정렬이 된 $k-1$개의 값이 있고, 거기에 하나를 추가하여 $k$개가 정렬되도록 만든다 생각하면 됨)

#### 삽입 위치를 어떻게 정할 것인가?
1. 맨 앞에서 부터 비교를 시작하여, 새로 넣고자하는 요소보다 크거나 같은 값이 나타나면 (혹은 맨 뒤에 도달 할 때 까지) 그 값 앞에 삽입 
2. 맨 뒤에서 부터 비교를 시작하여, 새로 넣고자하는 요소보다 작거나 같은 값이 나타나면 (혹은 맨 앞에 도달 할 때 까지) 그 값 뒤에 삽입  

두 방법이 대칭적인 것으로 동일할 것이라 생각되나, 그렇지 않을 수도 있음:  
**정렬할 데이터가 배열에 저장되어있기 때문에**, 1번 방법의 경우, 새로 추가하는 요소보다 작은 값들과 모두 비교를 해서 삽입할 위치를 찾았어도, 결국 그 위치에 삽입하기 위해선 새 요소보다 큰 값들을 모두 뒤로 한칸씩 밀어줘야하므로 결국 모두 순회하게 됨. 반면, 2번 방법의 경우엔 새 요소보다 작은 값들까지 순회할 필요가 없음. 

*값을 뒤로 한칸씩 밀어야하기 때문에 추가되는 요소가 지워지지 않도록 임시변수에 저장해야 함!*

#### 삽입정렬 알고리즘
```
insertionSort(A[], n)  // sort array A[1, ..., n]
{
    for i <- 2 to n    {  --- (1)
        find a correct position in A[1, ..., i] and insert A[i]  --- (2)
    }
}
```
수행시간:  
1. for 루프는 $n-1$번 반복
2. 삽입은 최악의 경우 $i-1$번 비교
→ 최악의 경우 $T(n) = (n-1) + (n-2) + \cdots + 2 + 1 = O(n^2)$
→ 최선의 경우(이미 정렬되어있는 경우)엔 $T(n) = 1 + 1 + \cdots + 1 = n - 1 = O(n)$

약간의 오버헤드까지 고려하면 선택/버블 정렬보다 삽입 정렬이 좀 더 빠르다. 특히, 버블 정렬도 최선의 경우가 $O(n)$ 또는 $n-1$로 동일해보이지만, 버블 정렬은 추가로 교환이 발생했는지 체크(`!(swapped)`) 해야하거나 하는 등의 (아주 미미한) 오버헤드가 있긴 함.

## 분할정복법
- 분할: 해결하고자 하는 문제를 작은 크기의 *동일한* 문제들로 분할
- 정복: 각각의 작은 문제를 *순환적*으로 해결
- 합병: 작은 문제의 해를 *합하여*(merge) 원래 문제에 대한 해를 구함

e.g., 합병정렬(merge sort)과 퀵정렬(quick sort)이 분할정복법(divide and conquer)에 해당 됨.

### 합병정렬 (merge sort)
- 데이터가 저장된 배열을 절반으로 나눔 (실제로 무슨 작업을 하는 건 아님)
- 각각을 순환적으로 정렬 (재귀적으로 함수 호출)
- 정렬된 두 개의 배열을 합쳐 전체를 정렬 (즉, 정렬을 합병 과정 중에 진행) <-- 실제 코딩을 할 필요가 있는 부분 
```
e.g., 배열 [5, 2, 4, 7]
5 / 2 / 4 / 7
2 5 / 4 7
2 4 5 7
```

#### 두개의 정렬된 리스트를 하나의 정렬된 리스트로 합치는 법
길이가 정렬된 두 배열의 길이의 합인 *추가배열*을 이용
```
e.g.,
// 각각의 배열이 이미 정렬되어 있으므로
// A 또는 H중 하나가 전체중에서 가장 작은 값이 됨 (A[i]와 A[j] 비교)
A G L O R / H I M S T  
i           j

0 0 0 0 0 0 0 0 0 0
k
-----------------------
A G L O R / H I M S T  
  i         j

A 0 0 0 0 0 0 0 0 0
  k
-----------------------
A G L O R / H I M S T  
    i       j

A G 0 0 0 0 0 0 0 0
    k
-----------------------
A G L O R / H I M S T  
    i         j

A G H 0 0 0 0 0 0 0
      k
-----------------------
A G L O R / H I M S T  
    i           j

A G H I 0 0 0 0 0 0
        k
... (반복)
```

#### 합병 정렬 알고리즘

```
mergeSort(A[], p, r)  // 배열 A의 index p에서 r까지 데이터를 정렬
{
    if (p < r) then {
        q <- (p + r) / 2;  // p, r의 중간 지점 계산
        mergeSort(A, p, q);
        mergeSort(A, q+1, r);
        merge(A, p, q, r);
    }
}

merge(A[], p, q, r)
{
    정렬되어 있는 두 배열 A[p ... q]와 A[q+1 ... r]을 합하여
    정렬된 하나의 배열 A[p ... r]을 만든다.
}
```

```
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void merge(int data[], int p, int q, int r) {
	int i = p;
	int j = q + 1;
	int k = 0;

	int size = r - p + 1;
	int* temp = (int*)malloc(size * sizeof(int));  // 주의: 매호출 malloc 하는 것은 매우 느림

	while (i <= q && j <= r) {
		if (data[i] <= data[j]) {
			temp[k++] = data[i++];
		}
		else {
			temp[k++] = data[j++];
		}
	}

	while (i <= q) {
		temp[k++] = data[i++];
	}
	while (j <= r) {
		temp[k++] = data[j++];
	}

	for (int i = 0; i <= size; i++) {
		data[p + i] = temp[i];
	}
	
	free(temp);

}
```

시간복잡도:

$$
T(n) = \begin{cases}
2T\left(\frac{n}{2}\right) + n & \text{if } n > 1 \\
O(1) & \text{if } n = 1
\end{cases} = O(n\log n)
$$

### 퀵 정렬 (quick sort)
분할: 배열을 임의의 피벗(pivot)을 기준으로 나눈다 - pivot보다 작은 값들 / pivot보다 큰 값 (따라서 항상 반반으로 쪼개지지 않음)  
정복: 각 부분을 순환적으로 정렬한다 (= 각각을 다시 퀵 정렬)  
합병: nothing to do

```
1) 정렬할 배열이 주어짐. 마지막 수를 피벗(pivot)으로 삼는다
31 8 48 73 11 3 20 29 65 <15>

2) 피벗을 기준으로 분할 (재배치)
8 11 3 <15> 31 48 20 29 65 73

3) 피벗의 좌우를 각각 순환적으로 정렬한다 (과정은 생략)
3 8 11 <15> 20 29 31 48 65 73 
```

#### 퀵 정렬 알고리즘
```
quickSort(A[], p, r)  // 배열 A의 인덱스 p부터 r까지 정렬한다
{
    if (p < r) then {  // 배열의 길이가 2 이상 일때만 (즉, 1 이하면 종료)
		q = partition(A, p, r);  // 분할 (q = pivot의 위치)
		quickSort(A, p, q - 1);  // 왼쪽 부분 배열 정렬
		quickSort(A, q + 1, r);  // 오른쪽 부분 배열 정렬
	}
}

partition(A[], p, r)
{
	배열 A[p, ..., r]의 원소들을 A[r]을 기준으로 양쪽으로 재배치하고 A[r]이 자리한 위치를 return;
	(즉, 주어진 범위의 마지막 원소를 피벗으로 분할 후, 피벗의 위치를 반환)
}
```

#### Partition 알고리즘
피벗은 마지막에 그대로 두고 그 앞의 배열을 먼저 피벗보다 작은 요소들의 영역, 큰 요소들의 영역 두개로 분할 한 뒤, 큰 요소들의 영역의 첫번째 요소를 마지막에 피벗과 교환한다. 따라서, 각각의 요소를 피벗과 한번씩 비교를 해야한다.  
```
p: 정렬의 시작 index
r: 정렬의 끝 idnex
i: pivot보다 작은 값들 중 마지막 값의 index (p - 1에서 시작) = '여기까지 정렬이 완료되었음'을 나타내는 index
j: 지금 검사하려는 값의 index (i에서 시작)

Partition(A[], p, r)
{
	x = A[r];
	i = p - 1;  // 아직 pivot보다 작다고 판단된 요소가 없으므로 out-of-index에서 시작
	for (j = p; j <= r - 1; j++) {
		if (A[j] <= x) {
			i = i + 1;
			exchange A[i] and A[j];
		}
	}
	exchange A[i + 1] and A[r];  // pivot과 pivot보다 큰 요소중 첫 요소와 교환  
	return i + 1;
}
```

시간복잡도:  
1. 분할 (Partition): 데이터가 $n$개라면, 모든 데이터를 pivot과 한번씩, 즉, 총 $n-1$회 비교하면 됨 ($+1$ 마지막 피벗 교환). 
2. 순환 (Recursion): 그럼 이 비교를 몇번 재귀/순환적으로 반복할까? 최악의 경우, 항상 한쪽은 $0$개, 다른 쪽은 $n-1$개로 분할 되면 quickSort 함수 자체가 총 $n - 1$회 호출 됨 (재귀의 조건이 `if (p < r)`이므로 배열의 길이가 1이하가 되면 base case 도달)

$$
\begin{aligned}
T(n) &= T(0) + T(n-1) + \Theta(n) \\
&= T(n-1) + \Theta(n) \\
&= T(n-2) + T(n-1) + \Theta(n-1) + \Theta(n) \\
&\quad \vdots \\
&= \Theta(1) + \Theta(2) + \cdots + \Theta(n-1) + \Theta(n) \\
&= \Theta(n^2)
\end{aligned}
$$

($\Theta$는 partition 비용, $T$는 재귀호출된 함수 비용)

모순적이게도, 이미 정렬된 입력 데이터의 경우가 최악의 경우가 됨 (마지막 원소를 피봇으로 선택하는 경우)

반면, 항상 절반으로 분할되는 경우 (최상의 경우 - 분할 시 pivot이 항상 중앙에 놓이는 경우):

$$
\begin{aligned}
T(n) = 2T(n/2) + \Theta(n) = \Theta(n \log n)
\end{aligned}
$$
  
**Q. 이딴게 quick? 최선의 경우에나 합병 정렬이랑 비슷한데?**  
A. 항상 절반씩 나누거나 (최선), 항상 $n-1$, $0$개씩 나누거나 (최악) 하는 경우는 사실 그리 확률이 높지 않음. 대충 한쪽이 적어도 $1/9$ 이상이 되도록 분할된다면? (이 정도면 현실적인 가정) -> 최악의 경우에 필요한 순환/재귀 횟수 = 항상 $9/10$을 가져가는 쪽의 순환/재귀 횟 = $k = \log{10/9}n = \theta(\log n)$. 분할의 연산은 각 재귀 호출마다 $n$회이므로 시간복잡도는 $O(n \log n)$.  

이 예시가 의미하는 바는 퀵 정렬의 성능은 partition이 얼마나 잘 balance되느냐에 달려있다는 것. 즉, 분할이 아주 극단적으로 일어나지만 않는다면 충분히 빠르다.

  
#### 퀵정렬 평균시간복잡도
- '평균' 혹은 '기대값'이란?

$$
A(n) = \sum_{\forall \text{ input instance } I \text{ of size } n} p(I)T(I)
$$

$p(I)$: $I$가 입력으로 들어올 확률
$T(I)$: $I$를 정렬하는데 걸리는 시간

- 그러나 실제로는 $p(I)$를 모름
- $p(I)$에 관한 적절한 가정을 한 후 분석
- e.g., 모든 입력 인스턴스가 동일한 확률을 가진다면 $p(I) = \frac{1}{n!}$ (입력이 $1$부터 $n$까지의 정수의 permutation이라고 가정)
  
$$A(n) = \frac{2}{n}\sum_{i=0}^{n-1} A(i) + \Theta(n) = \Theta(n\log_2 n)$$


#### Pivot의 선택
- 첫번째 값이나 마지막 값을 피봇으로 선택
  - 이미 정렬된 데이터 혹은 거꾸로 정렬된 데이터가 최악의 경우
  - 현실의 데이터는 랜덤하지 않으므로 정렬된 데이터가 입력으로 들어올 가능성이 매우 높음  
  - 따라서 좋은 방법이라고 할 수 없음
- "Median of Three"
  - 첫번째 값과 마지막 값, 그리고 가운데 값 중에서 중간값(median)을 피벗으로 선택
  - 최악의 경우 시간복잡도가 달라지지는 않음 (여전히 $O(n^2)$)
- Randomized Quicksort
  - 피벗을 랜덤하게 선택
  - no worst case instance, but worst case execution (이전의 두 방법의 경우엔 입력 데이터 - case - 에 따라 최악의 경우가 결정되는 반면, 랜덤의 경우 내가 주사위를 얼마나 잘 굴리냐 - execution - 에 따라 최악이 결정됨) 
  - 평균 시간복잡도 $O(n\log n)$


### 힙 정렬 (heap sort)
 - 최악의 경우 시간복잡도 $O(n \log{2}n)$ (합병정렬과 같음)
 - Sorts in place: 추가 배열 불필요
 - 이진 힙(binary heap) 자료구조를 사용

#### Heap 이란?
1. complete binary tree 이면서
2. (min 혹은 max) heap property를 만족함  
  
#### Tree 
계층적인 구조를 표현하는 비선형 자료구조 - 부모(parent)와 자식(child) 노드로 이루어짐.  
부모가 없는 노드를 root 노드, 자식이 없는 노드를 leaf 노드라고 함.  

- binary tree: 각 노드가 최대 2개의 자식 노드를 가지는 트리. 각각의 자식은 왼쪽 자식이냐 오른쪽 자식이냐가 정해져 있음 (설령 어떤 부모 노드의 자식 노드가 한개더라도 정해져있음).
- full binary tree: 모든 레벨에 노드들이 꽉 차있는 형태
- complete binary tree: 마지막 레벨을 제외하면 완전히 꽉 차있고, 가장 오른쪽부터 연속된 몇개의 노드가 비어있을 수 있음
- max heap property: 부모는 항상 자식보다 크거나 같다
- min heap property: 부모는 항상 자식보다 작거나 같다
- 동일한 데이터를 가진 서로다른 힙이 존재함 - 즉, 힙은 유일하지 않음

- 힙은 1차원 배열로 표현가능: A[1, ..., n]
  - 루트 노드 A[1]
  - A[i]의 부모 = A[i/2]
  - A[i]의 왼쪽 자식 = A[2i]
  - A[i]의 오른쪽 자식 = A[2i + 1]
(왜 이렇게 되는 가는 [여기](https://www.quora.com/In-a-binary-heap-a-node-with-index-i-has-children-at-indices-2i+1-and-2i+2-when-the-array-is-0-indexed-How-is-this-relationship-derived)를 참조)

--> Complete binary tree 이기 때문에 특정 인덱스의 앞이 꽉 차있어서 이처럼 배열로 표현이 가능 
#### Tree의 기본 연산: max-heapify
전제 조건: 
1. 트리의 전체 모양은 complete binary tree
2. 왼쪽 subtree (루트의 왼쪽 자식을 또다시 root로 하는 트리)는 그 자체로 heap이고
3. 오른쪽 subtree도 그 자체로 heap인데
4. 유일하게 루트만이 heap proterty를 만족 안하는 경우
--> 이 트리 전체를 heap으로 만들어주는 연산을 max-heapify라 함

과정:
1. 두 자식들 중 더 큰 쪽이 나보다 크면 exchange 한다.
2. 바꾸지 않았던 반대쪽 자식을 루트로 하는 subtree쪽은 문제가 될 게 없다 (두 자식을 비교해서 큰놈을 올렸기 때문에 heap property는 그대로 유지됨)
3. 따라서 바꾼 쪽 자식을 루트로하는 subtree를 다시 살펴봐야 함
4. exchange에 의해 heap 구조가 망가졌으므로 또다시 exchange가 필요해진다 (무조건 그런건 아니지만) 즉, 처음과 동일한 문제가 반복된다.
5. 과정 1-4 반복...
  
```
[1. Recursive version]
// 힙 A의 특정 노드 i에 대해 MAX-HEAPIFY 연산을 하는 함수
MAX-HEAPIFY(A, i)  // A: heap, i: heapify의 대상이 되는 노드
{
	if there is no child of A[i]  {  // 노드 i가 leaf node라면
		return;
	}
	k <- index of the biggest child of i;
	if A[i] >= A[k]  {  // 이미 i(부모)의 값이 k(자식)보다 크다면
		return;
	}
	exchange A[i] and A[k];
	MAX-HEAPIFY(A, k);  // k에 대해서 heapify를 진행 (recursion)
}


[2. Iterative version]
MAX-HEAPIFY(A, i)
{
	while A[i] has a child  {
		k <- index of the biggest child of i;
		if A[i] >= A[k]  {
			return;
		}
		exchange A[i] and A[k];
		i = k;
	}
}
```

시간 복잡도: 어떠한 경우에도 트리의 높이 $h$보다 작거나 같음. heap은 complete binary tree이기 때문에 노드의 개수를 $n$이라고 했을 때, 시간 복잡도는 항상 $O(h)=\theta(\log{2}n)$이 됨. 


#### 힙정렬 
1. 정렬할 배열을 힙으로 만들기
  - 주어진 배열 A를 complete binary tree로 해석함 (1차원 배열을 *개념적으로* 트리처럼 생각) - 아직 힙은 아님
  - level order의 역순으로 (배열의 마지막 요소부터 처음 요소까지 거꾸로) 노드를 순회하여, leaf node가 아닌 노드들에 대하여:
  	- 이 노드들을 root로 하는 subtree에 대해 생각: 왼쪽/오른쪽 자식 subtree가 heap인지 검사 후 (i.e., heapify 조건을 만족하는지 검사 - 자식 subtree들은 leaf node거나 이미 heapify를 거쳤을테니 사실 heap일 수 밖에 없음)
  	- max-heapify 연산을 진행
```
buildMaxHeap(A)
{
	heap_size[A] <- length[A]  // length[A]: 정렬할 데이터의 개수, heap_size[A]: 힙의 노드의 개수
	for i <- length[A]/2 downto 1  {  // length[A]/2 = n/2 = 첫 부모 노드의 index
		do maxHeapify(A, i);
	}
}
```
시간복잡도: 러프하게 for loop이 $\frac{n}{2}$회 반복, 각 루프마다 maxHeapify의 시간복잡도가 $\log n$이므로 $O(n\log n)$. 그러나, maxHeapify의 시간복잡도가 $\log n$은 heapify의 대상이 되는 root 노드의 subtree의 노드의 개수가 $n$개일 때 기준임. 즉, 초반엔 한 두개의 노드에 대해서 heapify를 하고 마지막에서야 $\log n$의 복잡도의 heapify를 하므로 이는 실제 시간복잡도에 비해 over-estimated된 계산임. 이를 더 정확하게 분석해보면 놀랍게도 시간복잡도는 $O(n)$이 됨 (따로 검색). 다만, 이처럼 힙을 만드는 연산의 시간복잡도가 $O(n \log n)$이라 하더라도, 실제 힙정렬 알고리즘 전체의 시간복잡도에는 영향이 없음. 실제 정렬이 일어나는 다음 단계의 시간복잡도가 어차피 $O(n \log n)$이기 때문.    
  
**왜 이렇게 하는가?**  
힙 구조가 정렬에 있어 이점이 있기 때문: heap property에 의해 부모가 자식노드들 보다 커야하므로 이미 데이터들간의 크기 관계가 어느정도 들어가 있고, 특히 최댓값이 어딨는지 알고 있음 (루트 노드).

2. 힙에서 최댓값(루트)를 가장 마지막 값과 바꾼다.
3. 힙의 크기가 $1$ 줄어든 것으로 간주한다. 즉, 가장 마지막 값은 힙의 일부가 아닌 것으로 간주한다.
4. 루트 노드에 대해서 heapify(1) 한다.
5. 2~4번을 반복한다.

```
HEAPSORT(A)
	BUILD-MAX-HEAP(A)				\\ O(n)
	for i <- heap_size downto 2 do	\\ n-1 times
		exchange A[1] <-> A[i]		\\ O(1)
		heap_size <- heap_size - 1	\\ O(1)
		MAX-HEAPIFY(A, 1)			\\ O(log_2(n))
```
시간복잡도: $O(n\log(2)n)$
