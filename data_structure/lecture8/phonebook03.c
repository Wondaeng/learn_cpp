#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 3  /* 배열 재할당 테스트를 위해 작은 값으로 정의 */
#define BUFFER_SIZE 50

/*
전화번호부 v3.0:
1. 조금 더 유연한 명령어 입력 받기 / 오류 처리
--> 명령을 단어 단위가 아닌, 라인 단위로 받아야 가능 (사용자의 엔터 입력 기준)

2. 저장된 사람의 수가 배열의 용량을 초과할 경우
--> 동적 메모리 할당으로 배열의 크기를 키운다
*/

/*
char* names[CAPACITY] vs char** names
전자:
- 문자열을 가르키는 포인터들의 배열 (배열은 포인터가 아니다!) --> * 한개
- 컴파일 시점에 메모리 고정

후자:
- 문자열 포인터들을 모아둔 배열의 시작 주소 --> 포인터의 포인터 --> ** 두개
- 동적 메모리 할당(malloc)으로 런타임에 크기 결정/조절 가능
*/

char** names;
char** numbers;

int capacity = INIT_CAPACITY;  /* size of arrays */
int n = 0;  /* number of people in phonebook */

char delim[] = " ";


void reallocate() {
	int i;

	capacity *= 2;
	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
	char** tmp2 = (char**)malloc(capacity * sizeof(char*));

	for (i = 0; i < n; i++) {
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}

	free(names);
	free(numbers);

	names = tmp1;
	numbers = tmp2;
}


void add(char* name, char* number) {
	if (n >= capacity) {
		reallocate();
	}

	int i = n - 1;
	while (i >= 0 && strcmp(names[i], name) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}

	names[i + 1] = _strdup(name);
	numbers[i + 1] = _strdup(name);
	n++;
}


void load(char* file_name) {
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE* fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		add(buf1, buf2);
	}

	fclose(fp);
}


int search(char* name) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0) {
			return i;
		}
	}
	return -1;
}


void status() {
	int i;
	for (i = 0; i < n; i++) {
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", n);
}


void find(char* name) {
	int index = search(name);
	if (index == -1) {
		printf("No person named '%s' exists.\n", name);
	}
	else {
		printf("%s\n", numbers[index]);
	}
}


void remove_person(char* name) {
	int i = search(name);
	if (i == -1) {
		printf("No person named '%s' exists.\n", name);
		return;
	}

	int j = i;
	for (; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully.\n", name);
}


void save(char* file_name) {
	int i;
	FILE* fp = fopen(file_name, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	for (i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}

	fclose(fp);
}


int read_line(char str[], int limit) {
	int ch, i = 0;
	/* TO DO: getchar()가 입력 버퍼에서 어떻게 읽는지 공부하기*/
	while ((ch = getchar()) != '\n') {
		if (i < limit - 1) {
			str[i++] = ch;
		}
	}

	str[i] = '\0';

	return i;
}


void init_directory() {
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}


void process_command() {
	char command_line[BUFFER_SIZE];
	char* command;
	char* argument1;
	char* argument2;

	while (1) {
		printf("$ ");

		if (read_line(command_line, BUFFER_SIZE) <= 0) {
			continue;
		}

		command = strtok(command_line, delim);
		/* 이미 검사 했지만 한번 그냥 더 함..*/
		if (command == NULL) {
			continue;
		}

		if (strcmp(command, "read") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("File name required.\n");
				continue;
			}
			load(argument1);
		}
		else if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);

			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}

			add(argument1, argument2);
			printf("%s was added successfully.\n", argument1);
		}
		else if (strcmp(command, "find") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			find(argument1);
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "delete") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			remove_person(argument1);
		}
	}
}


int main() {

	init_directory();  /* 이 함수에서 배열 names와 numbers를 생성*/
	process_command();  /* 사용자의 명령을 처리하는 함수를 별개로 정의 */

	return 0;
}
