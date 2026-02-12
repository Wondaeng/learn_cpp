# 출력문

## Hello World 출력하기

C는 사용하고 읽기 어려움:
```c
printf("Hello, %s%d\n", "world", 123);
```

C++ 방식은 사용하기도, 읽기도 더 쉬움:
```cpp
std::cout << "Hello, " << "world" << 123 >> std:endl;
```

- cout --> console out
- << --> 이 방향으로 밀어 넣는다
- endl --> end line (C의 `\n`과 비슷하지만 살짝 다른 개념)

### std::cout, std::endl

Q. `std::`이 무엇일까? A. 네임스페이스(namespace).  
  
#### 네임스페이스(namespace)
어떤 공간을 정해주는 건데, 거기에 이름을 정해준다. 이름이 같은 변수가 서로 다른 공간상에 있으면 그건 서로 다른 변수로 취급되는 것. 
  
- Java의 패키지나, C#의 네임스페이스와 비슷
- 아래와 같은 것들의 이름 충돌을 피하기 위해 사용:
  - 함수
  - 클래스
  - 기타 등등...
- 소문자로 정의하는 것이 일반적

```cpp
namespace hello
{
    void PrintHelloWorld();
}
```

- e.g.,
```c
// Hello1.h
void SayHello();

// Hello2.h
void SayHello();

// Main.cpp
#include "Hello1.h"
#include "Hello2.h"

// ...

SayHello(); // 컴파일 오류: 컴파일러가 중복된 함수 정의를 알아채고 오류를 발생시킴

```

```cpp
namespace hello
{
    void SayHello();
}

namespace hi
{
    void SayHello();
}

// ...

hello::SayHello();
hi::SayHello();  // 이런식으로 중복 정의 문제를 피해갈 수 있음

```

#### using 지시문
- Java의 import나 C#의 using과 비슷
- 타이핑의 양을 줄이는 방법일 뿐임 (std::, namespace:: 같은 것을 줄이는 방법)

e.g.,  
&lt;using을 사용하지 않는 경우&gt;
```cpp
#include <iostream>

int main()
{
    std::cout << "hello, world!" << std::endl;

    return 0;
}
```

&lt;using을 사용하는 경우 &gt; --> std를 생략 가능! 
```cpp
#include <iostream>

using namespace std;

int main()
{
    cout << "hello, world!" << endl;

    return 0;
}
```

#### 컴파일러가 namespace를 해석하는 법 (대충)
- namespace는 클래스보다 상위의 전역 영역에 만들어짐
```
파일 (global scope)
 ├─ namespace
 │   ├─ class / struct
 │   │   ├─ 멤버 함수
 │   │   │   └─ 지역 scope ({})
 │   │   └─ 멤버 변수
 │   └─ 함수
 └─ 함수
```

- 컴파일러가 코드를 볼 때의 큰 흐름
  1. Tokenizing & Lexing
  소스코드를 구문들로 쪼개고, 그 의미를 해석하여 어휘(lexicon)에 맞게 분류함
  
  2. Parsing
  문법을 기준으로 구문들을 분리하고 문법 구조(AST)를 만듦
  
  3. Symbol Table을 만듦
  ```
  Global Scope
  ├─ name: foo  → function
  ├─ name: x    → variable
  ├─ name: A    → namespace
  │    ├─ name: x → variable
  │    └─ name: f → function
  ```
  namespace는 symbol table의 node임. 