## Recursion vs. Iteration

- 모든 순환함수는 반복문(iteration)으로 변경 가능
- 그 역도 성립함. 즉, **모든 반복문은 recursion으로 표현 가능함**
- 순환함수는 *(경우에 따라)* 복잡한 알고리즘을 단순하고 알기쉽게 표현하는 것을 가능하게 함
- 하지만 함수 호출에 따른 오버헤드가 있음 (매개변수 전달, 액티베이션 프레임 생성 등)

### 예제 보러 가기 ([권오흠 교수님의 자료구조 2015 1-2강](https://www.youtube.com/watch?v=tuzf1yLPgRI&list=PL52K_8WQO5oUuH06MLOrah4h05TZ4n38l&index=2))

1. [문자열의 길이 구하기](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/strlen.c)
2. [문자열 출력하기](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/print_by_char.c)
3. [문자열 거꾸로 출력하기](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/print_by_char_reverse.c)
4. [이진수로 변환하기](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/print_as_binary.c)
5. [배열의 합 구하기](https://github.com/Wondaeng/learn_cpp/blob/main/algorithm/recursion/sum_of_array.c)
