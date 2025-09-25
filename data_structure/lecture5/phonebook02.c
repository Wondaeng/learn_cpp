#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define BUFFER_SIZE 100

/* 각각의 이름 or 전화번호는 string = char 배열 --> char 배열의 배열 = char 포인터(*)의 배열 */
char* names[CAPACITY];    /* names */
char* numbers[CAPACITY];    /* phone numbers */
int n = 0;    /* number of people in phone directory */

/*
전화번호부 v2.0의 경우, 자료를 알파벳 순서로 "정렬" 해야한다:

1. bubblesort 등의 정렬(sorting) 알고리즘을 사용하는 방법?
--> 새로운 데이터가 계속적으로 추가되는 우리의 상황에서는 부적절

2. 새로운 데이터가 추가될 때 마다 제자리를 찾아서 삽입하는 방법? --> 적절

맨 뒤에서 부터 검사하여, 추가하려는 자료보다 큰것들을 전부 한 칸씩 뒤로 이동한다.
E 보다 작은 것이 나오거나, 배열의 시작을 지나치면 그 다음 자리에 E를 저장한다.
*/


void add() {
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1);
	scanf("%s", buf2);

	int i = n - 1;
	while (i >= 0 && strcmp(names[i], buf1) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i + 1] = _strdup(buf1);
	numbers[i + 1] = _strdup(buf2);
	n++;

	printf("%s was added successfully.\n", buf1);
}


void find() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int index = search(buf);
	if (index == -1) {
		printf("No person named '%s' exists.\n", buf);
	} else {
		printf("%s\n", numbers[index]);
	}
}


void status() {
	int i;
	for (i = 0; i < n; i++) {
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons,\n", n);
}


void load() {
	char file_name[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	scanf("%s", file_name);

	FILE* fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		names[n] = _strdup(buf1);
		numbers[n] = _strdup(buf2);
		n++;
	}

	fclose(fp);    /* 볼일이 끝난 파일은 반드시 닫아 주어야 한다 */
}


void save() {
	int i;
	char file_name[BUFFER_SIZE];
	char tmp[BUFFER_SIZE];

	scanf("%s", tmp);    /* "as"를 넘기기 위한 입력 */
	scanf("%s", file_name);

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


void remove_person() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int index = search(buf);  /* returns -1 if not exists */
	if (index == -1) {
		printf("No person named '%s' exsits.\n", buf);
		return;
	}
  /* 
  MQ1. 이 방식으로 삭제하면 실질적으로 기존의 감소되기 이전의 인덱스 n에 대한 값은 그대로 남아있는 것이 아닌가? 
  (단지 status 함수에서 접근하지 않게 되므로 보이지 않을 뿐)
  */
	int j = index;
	for (; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully.\n", buf);
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


int main() {
	char command[BUFFER_SIZE];
	while (1) {

		printf("$ ");
		scanf("%s", command);

		if (strcmp(command, "read") == 0) {
			load();
		}
		else if (strcmp(command, "add") == 0) {
			add();
		}
		else if (strcmp(command, "find") == 0) {
			find();
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "remove") == 0) {
			remove_person();
		}
		else if (strcmp(command, "save") == 0) {
			save();
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
	}
	return 0;
}
