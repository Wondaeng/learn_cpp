/*

데이터 (저장) 형식:

- '#'문자를 필드들 간의 구분자로 사용한다.
- 존재하지 않는 항목의 경우 하나의 공백문자로 표시한다.
- 모든 라인은 반드시 구분자로 끝난다 (strtok 용도).

e.g.:
Beatles#Let it be#C:\\song_collections\beatles\let-it-be.mp3#
Girls Generation#GGG# #
IU#Twenty three#C:\\song_collections\iu\twenty-three.mp3#

*/

/*

자료구조: 연결리스트 (linked list)
1. 가수마다 'Artist' 구조체 생성
- name: 가수의 이름을 저장하기 위한 (char*)
- next: 단방향 연결리스트로 연결하기 위한 링크필드 (Artist*)
- head, tail: 가장 처음과 마지막의 SNode 포인터 (SNode*)

2. 노래마다 'Song' 구조체 생성
- artist: 가수의 Artist 객체의 포인터 (Artist*)
- title: 노래의 제목 (char*)
- path: 노래 파일의 경로 (char*)
- index: 노래가 추가된 순서의 인덱스 (int)

3. 노래들을 연결하기 위해 'SNode'를 별도로 생성
- next, prev: SNode 간의 포인터 (SNode*)
- song: Song 객체에 대한 포인터 (Song*)

Q1. 왜 번거롭게 SNode를 따로 만드는가?
A1. 연결리스트의 노드(SNode)와 실제로 저장되는 데이터(Song) 객체를 분리할 수 있음.
노래를 가수별로 분류할 수도 있지만, 앨범, 플레이리스트 등등 다른 기준별로 분류할 수도 있음.

e.g.: 최근 일주일 내로 재생된 노래의 플레이리스트를 만들고 싶은 상황에
이미 Song 객체들 자체가 Artist를 기준으로 링크필드를 가져 연결되어있다면 상당히 곤란해짐 
반면에, 노드와 데이터를 분리하면 SNode만 따로 다시 생성/연결하면 됨
--> 노래마다 오직 하나의 Song 객체를 가지며, 이 하나의 Song 객체가 서로다른 여러개의 (SNode)연결리스트 안에 소속될 수 있음


4. 가수가 또 여러명일 테니, artist들을 이니셜에 따라 분류하고, 이들을 알파벳 순으로 정렬하여 각 그룹을 하나의 단방향 연결리스트로 저장한다.
이를 'artist_directory'라는 배열에 각각 저장한다 (각 이니셜 그룹의 첫번째 가수에 연결). 
--> 검색 효율 상승

5. Song 들을 "index를 SIZE로 나눈 나머지"가 동일한 것들끼리 분류하여 각 그룹을 하나의 단방향(prev은 사용하지 않는다) 연결리스트로 저장한다. 
정렬은 하지 않는다. 
3번과 동일한 이유로 실제로는 SNode의 연결리스트로 구현한다.
e.g.: SIZE=10 일때, index가 72, 12, 32인 노래 세곡은 같은 그룹. 

*/

/*
* 
이 예제의 핵심 포인트: C 프로그램을 여러 개의 소스 파일들로 구성한다. 
* 관습적으로 각각의 소스파일은 확장자 .c를 가진다.
* 하나의 소스파일은 main이라는 이름의 함수를 가져야 한다.
* 프로그램을 여러 개의 소스 파일로 분할할 경우의 장점: 
- 연관된 함수들과 변수들이 하나의 파일에 있으므로 프로그램의 구조가 좀더 명료해진다 (모듈화, modularity)
- 각각의 소스 파일들이 개별적으로 컴파일 할 수 있으므로 컴파일 시간이 절약된다 (수정된 사항이 있을 경우만 다시 컴파일).
- 소프트웨어 재사용이 용이하다

소스파일 구성:
- 서로 연관된 함수들과 변수들을 하나의 파일에 넣는다:
1. 입력을 라인단위로 읽거나, 문자열/토큰의 처리와 관련된 함수들을 하나의 소스파일에 넣는다 --> string_tools.c
2. 음원 데이터를 추가, 검색, 삭제, 관리하는 일을 하는 함수들을 다른 하나의 소스파일에 넣는다 --> library.c
3. main 함수와 사용자 명령어를 처리하는 process_command 함수 등은 또다른 하나의 소스파일에 넣는다 --> main.c

모듈화시 고려해야 할 포인트:
- 어떻게 다른 파일에 정의되어 있는 함수를 호출할 수 있는가?
- 어떻게 다른 파일에 정의되어 있는 변수(external variable)를 사용할 것인가?
- 어떻게 서로 다른 파일들이 매크로나 타입 정의를 공유할 것인가?

C 프로그램 구성요소:
1. 매크로 (#define)
2. 타입 정의 (struct)
3. 변수
4. 함수

해결책: 각각의 소스파일마다 헤더(header)파일을 만든다. 
헤더파일에 함수의 프로토타입을 정의하면 다른 소스파일에서도 #include로 사용할 수 있음.
#include는 해당 헤더파일을 완전히 복사하여 그 자리에 대입하는 것임 (preprocessing 단계에서)
따라서 컴파일러는 프로토타입이 정의되어있으므로, 컴파일시 불만이 없음.
(다만 실제 해당 함수의 위치를 찾아 연결, 호출하는 것은 linker가 하는 일임.)

e.g.:
<library.c>
#include "library.h"

void add_song() { ... }
void find_song() { ... }
int remove_song() { ... }
...


<library.h>
#define MAX 100
typedef struct song Song;
struct song {
    ...
};

void add_song();
void find_song();
int remove_song();


<main.c>
#include "library.h"

void process_command()
{
    ...
    add_song(arg1, ...);
    ...
}

1. 매크로, 타입정의 공유: 그대로 헤더파일에 넣는다
2. 함수 공유: 헤더파일에는 prototype을 넣고, 실제 구현은 소스파일에 넣는다.
3. 변수 공유:
* 변수의 선언(declaration)과 정의(definition)의 구분:
- 선언: 컴파일러에게 변수의 존재를 알려 줌
- 정의: 실제로 메모리 할당

* 변수는 여러번 선언될 수 있다. 하지만, 정의는 한번만 해야한다.

* 선언과 정의를 동시에 하는 방법: int i;

* extern 키워드를 사용하여 변수를 정의하지 않고 선언만 할 수 있음. 즉, 컴파일러에게 변수 i와 배열 a가 다른 파일에 정의되어있음을 알려주는 역할
extern int i;
extern int a[];

--> 
- 공유 변수의 선언은 헤더파일에 둔다.
- 공유 변수를 사용하는 모든 소스 파일은 헤더파일을 include한다.
- 소스 파일 중 오직 한 곳에서 공유 변수를 정의한다.

e.g.:
<file.h>
extern int global_variable;  // declaration of the variable

<file1.c>
#include "file.h"

int global_variable;  // definition of the variable
...
printf("%d\n", global_variable++);  // use of the variable

<file2.c>
#include "file.h"
...
printf("%d\n", global_variable++);

C프로그래밍에서 변수의 공유는 가능하면 안하는 것이 좋다


중복된 헤더파일 --> 매크로 정의, 함수 프로토타입, 외부(extern) 변수 선언은 중복되어도 상관없다.
하지만, 타입 정의가 중복되는 것은 컴파일러 오류를 발생시킨다. 

중복 방지 --> #ifndef - #endif 지시어 사용

*/
