#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 100
#define BUFFER_LENGTH 100

/*
C 프로그래밍에서 구조체의 배열을 만들어 사용하는 것은 일반적인 스타일이 아님

e.g., phonebook04.c의 print_person() 함수
call-by-value (pass-by-assignment): 함수에 전달되는 인자의 값이 "복사되어" 매개변수에 전달 됨
--> 기존의 변수와 다른 메모리 공간을 가짐 

문제: 구조체를 전달시 모든 멤버들이 복사됨 --> 큰 구조체의 경우 매번 모든 멤버의 값을 다른 구조체의 값에 복사를 하는 것은 바람직하지 않음 (왜?)

v5.0에선, 구조체의 "포인터들"의 배열을 사용  --> 모든 멤버가 아니라 그 구조체를 가르키는 포인터만 복사하면 됨
*/


typedef struct person {  /* 소문자 person은 생략가능! */
	char* name;
	char* number;
	char* email;
	char* group;
} Person;


Person** directory;  /* Person 구조체의 포인터들의 배열 */
int capacity;
int n;


void init() {
	directory = (Person**)malloc(INIT_CAPACITY * sizeof(Person*));
	capacity = INIT_CAPACITY;
	n = 0;
}


int read_line(FILE* fp, char str[], int n) {
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		if (i < n) {
			str[i++] = ch;
		}
	}
	str[i] = '\0';
	return i;
}


int compose_name(char str[], int limit) {
	char* ptr;
	int length = 0;

	ptr = strtok(NULL, " ");  /* strtok이 내부적으로 static 포인터를 저장하여 어디까지 toknize 했는지 기억함. 따라서 command_line의 첫 command이후 단어부터 다시 자르기 시작 */
	if (ptr == NULL) {
		return 0;
	}

	strcpy(str, ptr);  /* ptr이 가르키는 주소가 NULL이 아니라면 이름의 첫 단어를 가르키고 있음 */
	length += strlen(ptr);

	/* MQ2. 근데 이러면 맨 마지막에 불필요한 공백이 하나 남는 것 아닌가? */
	while ((ptr = strtok(NULL, " ")) != NULL) {
		if (length + strlen(ptr) + 1 < limit) {  /* buffer overflow 방지*/
			str[length++] = ' ';  /* 널문자를 공백문자로 치환 --> 길이가 1 증가 */
			str[length] = '\0';  /* 두 단어가 널문자로 끝나야 strcat이 정상적으로 동작 */
			strcat(str, ptr);
			length += strlen(ptr);
		}
	}
	return length;
}


void reallocate() {
	capacity *= 2;
	Person** tmp = (Person**)malloc(capacity * sizeof(Person*));
	for (int i = 0; i < n; i++) {
		tmp[i] = directory[i];
	}
	free(directory);
	directory = tmp;
}


void add(char* name, char* number, char* email, char* group) {
	if (n >= capacity) {
		reallocate();
	}

	int i = n - 1;
	while (i >= 0 && strcmp(directory[i]->name, name) > 0) {
		directory[i + 1] = directory[i];
		i--;
	}

	directory[i + 1] = (Person*)malloc(sizeof(Person));  /* Person 구조체를 위한 동적메모리 할당 */

	directory[i + 1]->name = name;
	directory[i + 1]->number = number;
	directory[i + 1]->email = email;
	directory[i + 1]->group = group;

	n++;
}


void release_person(Person* p) {
	free(p->name);
	if (p->number != NULL) {
		free(p->number);
	}
	if (p->email != NULL) {
		free(p->email);
	}
	if (p->group != NULL) {
		free(p->group);
	}
	free(p);
}


void save(char* file_name) {
	int i;
	FILE* fp = fopen(file_name, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	for (i = 0; i < n; i++) {
		fprintf(fp, "%s#", directory[i]->name);
		fprintf(fp, "%s#", directory[i]->number);
		fprintf(fp, "%s#", directory[i]->email);
		fprintf(fp, "%s#\n", directory[i]->group);
	}
	fclose(fp);
}


int search(char* name) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, directory[i]->name) == 0) {
			return i;
		}
	}
	return -1;
}


void print_person(Person* p) {
	printf("%s:\n", p->name);
	printf("    Phone: %s\n", p->number);
	printf("    Email: %s\n", p->email);
	printf("    Group: %s\n", p->group);
}


void status() {
	int i;
	for (i = 0; i < n; i++) {
		print_person(directory[i]);
	}
	printf("Total %d persons.\n", n);
}


void find(char* name) {
	int index = search(name);
	if (index == -1) {
		printf("No person named '%s' exists.\n", name);
	}
	else {
		print_person(directory[index]);
	}
}


void handle_add(char* name) {
	char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];

	printf(" Phone: ");
	read_line(stdin, number, BUFFER_LENGTH);

	printf(" Email: ");
	read_line(stdin, email, BUFFER_LENGTH);

	printf(" Group: ");
	read_line(stdin, group, BUFFER_LENGTH);


	add(_strdup(name), (strlen(number) > 0 ? _strdup(number) : NULL),
		(strlen(email) > 0 ? _strdup(email) : NULL),
		(strlen(group) > 0 ? _strdup(group) : NULL));
}


void load(char* file_name) {
	char buffer[BUFFER_LENGTH];
	char* name, * number, * email, * group;
	char* token;

	FILE* fp = fopen(file_name, "r");\
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	while (1) {
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0) {
			break;
		}
		name = strtok(buffer, "#");

		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0) {
			number = NULL;
		}
		else {
			number = _strdup(token);
		}

		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0) {
			email = NULL;
		}
		else {
			email = _strdup(token);
		}

		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0) {
			group = NULL;
		}
		else {
			group = _strdup(token);
		}
		add(_strdup(name), number, email, group);
	}
	fclose(fp);
}


void remove_person(char* name) {
	int i = search(name);
	if (i == -1) {
		printf("No person named '%s' exists.\n", name);
		return;
	}

	Person* p = directory[i];
	for (int j = i; j < n - 1; j++) {
		directory[j] = directory[j + 1];
	}
	n--;
	release_person(p);
	printf("'%s' was deleted successfully.\n", name);
}


int main() {
	char command_line[BUFFER_LENGTH];
	char* command, * argument;  /* command와 argument를 동적할당 받기 위한 포인터 변수 */
	char name_str[BUFFER_LENGTH];

	init();

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) {
			continue;
		}

		command = strtok(command_line, " ");  /* 사용자가 입력한 첫번째 단어 (공백 구분자 기준) tokenizing */

		if (strcmp(command, "read") == 0) {
			argument = strtok(NULL, " ");  /* 다음 입력 (argument) tokenizing, 파일 이름엔 공백이 들어갈 수 없으므로 그냥 " "을 구분자로 사용 */
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			load(argument);
		}
		else if (strcmp(command, "add") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {  /* 이름에는 공백이 "여러개" 들어갈 수 있음 */
				printf("Name required.\n");
				continue;
			}
			handle_add(name_str);
		}
		else if (strcmp(command, "find") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}

			find(name_str);
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "delete") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Invalid arguments.\n");
				continue;
			}
			remove_person(name_str);
		}
		else if (strcmp(command, "save") == 0) {
			argument = strtok(NULL, " ");
			if (strcmp(argument, "as") != 0) {
				printf("Invalid arguments.\n");
				continue;
			}
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			save(argument);
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
	}
	return 0;
}
