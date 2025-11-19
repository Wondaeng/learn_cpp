# 권오흠 교수님의 알고리즘 [제 1강](youtube.com/watch?v=ln7AfppN7mY&list=PL52K_8WQO5oUuH06MLOrah4h05TZ4n38l&index=1&pp=iAQB)
## Recursion vs. Iteration

- 모든 순환함수는 반복문(iteration)으로 변경 가능
- 그 역도 성립함. 즉, **모든 반복문은 recursion으로 표현 가능함**
- 순환함수는 *(경우에 따라)* 복잡한 알고리즘을 단순하고 알기쉽게 표현하는 것을 가능하게 함
- 하지만 함수 호출에 따른 오버헤드가 있음 (매개변수 전달, 액티베이션 프레임 생성 등)

### 예제 보러 가기

1. [문자열의 길이 구하기](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/strlen.c)
2. [문자열 출력하기](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/print_by_char.c)
3. [문자열 거꾸로 출력하기](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/print_by_char_reverse.c)
4. [이진수로 변환하기](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/print_as_binary.c)
5. [배열의 합 구하기](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/sum_of_array.c)

## Designing Recursion (순환 알고리즘의 설계)
### 순환적 알고리즘 설계
1. 기본 조건의 만족
  - 적어도 하나의 base case: 순환되지 않고 종료되는 case가 있어야 함 (조건 1)
  - 모든 case는 결국 base case로 수렴해야 함 (조건 2)

2. 암시적(implicit) 매개변수를 **명시적(explicit) 매개변수**로 바꾸어라.
   
   [(예제 1) 순차 탐색](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/sequential_search.c):
   반복문 버전 함수의 역할은 인덱스 범위 $[0, n-1]$ 사이에서 target을 검사하는 것.
   이 때, 끝 인덱스 $n-1$는 함수 파라미터 $n$에 의해 **명시적**으로 표현 되어 있음.
   반면, 시작 인덱스 $0$은 명시적으로 표현된 것이 아님 (배열의 데이터가 $n$개니까, 당연히 인덱스 $0$부터 출발해야 할 것이다... 라는 가정에 의해 **암시적**으로 표현된 것).

   재귀 버전 함수의 경우엔, 검색 구간의 시작점 또한 명시적으로 지정한다.

   *교수님의 강의에선 반복문 버전의 경우, 시작 인덱스에 대한 변수가 암시적 변수라 했는데, 내 생각은 조금 다르다. 내 생각엔 for 루프 구문안에 int i로써 제대로 명시적으로 선언되어 있는 상태다. (교수님의 기준에선 for loop 버전 함수의 경우에도 i는 암시적 변수다. 왜냐하면 함수의 파라미터에 드러나 있지 않기 떄문이다.) 이때 이 변수 i가 바로 반복을 끝내기 위한 경계 조건이며 (i < n) 이것이 곧 재귀함수에서 base case의 조건에 대응되는 것이다 (begin < end). 따라서 "암시적 변수를 명시적 변수로 바꿔라" 라는 표현보다 "base case의 조건이 어떤 변수에 의해 좌우 되는지를 명확히 이해하라" 라는 표현이 더 맞을 것 같다. 이에 대한 이해는 특정 변수를 함수의 파라미터로 (교수님이 말하는 뜻에서의) "명시화"하는 과정에서 따라오기 때문에 이렇게 표현이 된 것 아닐까 싶다.*


**재귀에서 추가 인자(e.g., begin)가 필요한 경우는, 각 호출이 처리해야 할 데이터의 범위가 달라지는 경우다.**
루프 버전에선 없었던 변수가 생기는 이유? 루프에선 지역변수를 이용해 변하는 상태를 계속 저장할 수 있지만, 재귀함수는 각 호출마다 프레임이 달라져서 인자로 전달해줘야함.


## 멱집합 (powerset)
멱집합: 어떤 집합의 모든 부분집합들을 원소로 가지는 집합
($n$개의 원소를 가지는 집합의 모든 가능한 부분집합의 개수는 $2^n$)

### Recursion을 이용하여 멱집합을 구하는 방법
e.g., 
1. ${a, b, c, d, e, f}$의 모든 부분집합을 나열하려면...
- $a$를 제외한 ${b, c, d, e, f}$의 모든 부분집합들을 나열하고
- ${b, c, d, e, f}$의 모든 부분집합에 ${a}$를 추가한 집합들을 나열한다

2. ${b, c, d, e, f}$의 모든 부분집합에 ${a}를 추가한 집합들을 나열하려면...
- ${c, d, e, f}$의 모든 부분집합들을 ${a}$를 추가한 집합들을 나열하고
- ${c, d, e, f}$의 모든 부분집합에 ${a, b}$를 추가한 집합들을 나열한다

<Pseudo code 1>  
powerSet(S):  
if S is an empty set  
&nbsp;&nbsp;print nothing;  
else  
&nbsp;&nbsp;let t be the first element of S;  
&nbsp;&nbsp;find all subsets of S - {t} by calling powerSet(S - {t});  
&nbsp;&nbsp;print the subsets;  
&nbsp;&nbsp;print the subsets with adding t;  

위 수도 코드의 몇가지 문제점들: return vs print
- 결국 powerSet()이라는 함수가 모든 부분집합들을 구해서 **return을 해줘야 함**. 어떤 함수가 여러개의 집합을 return하게 만드는 것이 (가능은 하나) 간단하지 않음.
- 그렇다면, 현재 함수에서처럼 print로 끝날 것이 아니라 return을 하게끔 해야 함.
- 우리의 목적은 멱집합의 출력이므로, 이렇게 될 경우 2^n개의 집합들을 저장해야 하며 이는 메모리 낭비가 될 수 있음.

<Pseudo code 2>  
powerSet(P, S):  // S의 멱집합을 구한 후, 각각의 부분집합에 P를 합하여 출력  
if S is an empty set  
&nbsp;&nbsp;print P;  
else  
&nbsp;&nbsp;let t be the first element of S;  
&nbsp;&nbsp;powerSet(P, S - {t});  
&nbsp;&nbsp;powerset(P U {t}, S - {t});  
  
[실제 구현 코드](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/powerset.c)

### 상태공간트리 (state space tree): 
- 해를 찾기 위해 탐색할 필요가 있는 모든 후보들을 포함하는 트리
- 트리의 모든 노드들을 방문하면 해를 찾을 수 있다.
- 루트에서 출발하여 체계적으로 모든 노드를 방문하는 절차를 기술한다.

e.g. k: 트리 상에서 나의 위치 (탐색 깊이), if (k==n): 만약 내 위치가 리프 노드라면, 
include[k] = false, powerSet(k+1): 먼저 왼쪽으로 내려갔다가
include[k] = true, powerSet(k+1): 다시 올라와서 오른쪽으로 내려가기 
