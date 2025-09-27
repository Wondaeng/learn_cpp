#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define BUFFER_LENGTH 100

/*
전화번호부 v4.0:
- 전화번호 뿐만 아니라 여러 항목을 받을 수 있음 (비워둘 수도 있음)
- 이름이 하나 이상의 단어로 구성 될 수 있음
*/


/*
파일형식: 한줄에 한명씩 저장
1. # 문자를 구분자(delimeter)로 사용 
2. 값이 존재하지 않는 항목의 경우 하나의 공백문자로 표시
3. 모든 라인은 반드시 구분자로 끝난다. 
e.g., directory.txt
David K.#0517778888# #Friend#
Hong Gil-Dong# #henry@gmail.com# #
John Doe# # # #
Sean#01067356574#sean@naver.com#colleague#
*/


typedef struct person {  /* 소문자 person은 생략가능! */
	char* name;
	char* number;
	char* email;
	char* group;
} Person;


Person directory[CAPACITY];  /* Person 구조체의 배열 (한칸 = 한사람의 정보의 묶음) */

int n = 0;


/*
read_line이 유저의 커맨드 입력을 읽어오는 것에서 기능이 하나 추가됨 
--> 파일로부터 load할 때, 한 줄(한 사람의 정보)를 읽을 때도 사용
(MQ1. 이게 과연 좋은 방식인가?)
*/
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


/*
n - 1 번째의 이름(directory 배열의 최대 크기는 n이기 때문에, 최대 n - 1 번째 까지만 기존에 존재할 수 있음)부터 현재 추가하려는 이름과 비교를 시작
만약 기존의 것이 알파벳 순으로 더 뒤라면 한칸 뒤로 밀고, 다음/한 칸 앞(-1)의 이름과 비교 --> i--;
따라서 현재 인덱스 i는 비교의 대상이 되는 이름의 자리고, i + 1은 비교가 이미 끝나 하나 밀린 이름이 있던 자리로 비어있게됨
만약 i번째 이름과 비교후 새로 추가하려는 이름이 알파벳 순으로 더 뒤라면, 비어있는 i + 1 번째 자리에 넣음
*/
void add(char* name, char* number, char* email, char* group) {
	int i = n - 1;
	while (i >= 0 && strcmp(directory[i].name, name) > 0) {
		directory[i + 1] = directory[i];
		i--;
	}
	/* 없는 항목의 경우 하나의 공백문자로 저장 됨 */
	directory[i + 1].name = _strdup(name);
	directory[i + 1].number = _strdup(number);
	directory[i + 1].email = _strdup(email);
	directory[i + 1].group = _strdup(group);

	n++;
}


void load(char* file_name) {
	/* tokenize 된 정보들을 담을 변수 선언 */
	char buffer[BUFFER_LENGTH];
	char* name;
	char* number;
	char* email;
	char* group;

	FILE* fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	while (1) {
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0) {
			break;
		}
		name = strtok(buffer, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		add(name, number, email, group);  /* add함수 내부적으로 strdup을 사용하여 diretory에 할당함 */
	}
	fclose(fp);
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


void handle_add(char* name) {
	char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
	char empty[] = " ";

	printf(" Phone: ");
	read_line(stdin, number, BUFFER_LENGTH);

	printf(" Email: ");
	read_line(stdin, email, BUFFER_LENGTH);

	printf(" Group: ");
	read_line(stdin, group, BUFFER_LENGTH);

	/* 
	입력이 없을 경우를 처리하기 위해 조금 길어짐 
	(조건) ? A : B --> 조건이 만족 되면 A, 아니면 B

	MQ3. char*로 캐스팅은 왜? 배열은 알아서 char*로 decay 되는것 아닌가?
	*/
	add(name, (char*)(strlen(number) > 0 ? number : empty),
		(char*)(strlen(email) > 0 ? email : empty),
		(char*)(strlen(group) > 0 ? group : empty));

	//add(name, (strlen(number) > 0 ? number : empty),
	//	(strlen(email) > 0 ? email : empty),
	//	(strlen(group) > 0 ? group : empty));
}


void save(char* file_name) {
	int i;
	FILE* fp = fopen(file_name, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	for (i = 0; i < n; i++) {
		fprintf(fp, "%s#", directory[i].name);
		fprintf(fp, "%s#", directory[i].number);
		fprintf(fp, "%s#", directory[i].email);
		fprintf(fp, "%s#\n", directory[i].group);
	}
	fclose(fp);
}


int search(char* name) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, directory[i].name) == 0) {
			return i;
		}
	}
	return -1;
}

void print_person(Person p) {
	printf("%s:\n", p.name);
	printf("    Phone: %s\n", p.number);
	printf("    Email: %s\n", p.email);
	printf("    Group: %s\n", p.group);
}


void remove_person(char* name) {
	int i = search(name);
	if (i == -1) {
		printf("No person named '%s' exists.\n", name);
		return;
	}

	int j = i;
	for (; j < n - 1; j++) {
		directory[j] = directory[j + 1];  /* 구조체 변수간의 치환연산이 지원되므로 멤버 항목들을 따로따로 치환할 필요가 없다 */
	}
	n--;
	printf("'%s' was deleted successfully.\n", name);
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


int main() {
	char command_line[BUFFER_LENGTH];
	char* command, * argument;  /* command와 argument를 동적할당 받기 위한 포인터 변수 */
	char name_str[BUFFER_LENGTH];

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
