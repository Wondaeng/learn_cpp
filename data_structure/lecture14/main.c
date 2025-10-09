#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_tools.h"
#include "library.h"

#define BUFFER_LENGTH 200


void handle_add();
void process_command();
void handle_load();
void handle_search();
void handle_play();
void handle_save();
void handle_remove();


int main() {

	initialize();  // initialize directories
	handle_load();  // load data file
	process_command();

}


void handle_load() {

	char buffer[BUFFER_LENGTH];

	printf("Data file name? ");

	if (read_line(stdin, buffer, BUFFER_LENGTH) <= 0) {
		return;
	}

	FILE* fp = fopen(buffer, "r");
	if (fp == NULL) {
		printf("No such file exists.\n");
		return;
	}
	
	load(fp);
	fclose(fp);

}


void process_command() {
	
	char command_line[BUFFER_LENGTH];  // char array to store command string
	char* command;

	while (1) {  // infinite loop
		printf("$ ");  // prompt

		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) {  // get user input as a line
			continue;
		}

		command = strtok(command_line, " ");
		if (strcmp(command, "add") == 0) {
			handle_add();
		}
		else if (strcmp(command, "search") == 0) {
			handle_search();
		}
		else if (strcmp(command, "remove") == 0) {
			handle_remove();
		} 
		else if (strcmp(command, "play") == 0) {
			handle_play();
		}
		else if (strcmp(command, "save") == 0) {
			char* tmp = strtok(NULL, " ");
			if (strcmp(tmp, "as") != 0) {
				continue;
			}
			handle_save();
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
	}
	return 0;
}


void handle_remove() {

	char* id_str = strtok(NULL, " ");
	int index = atoi(id_str);
	remove_song(index);

}


void handle_save() {
	
	char* file_name = strtok(NULL, " ");
	FILE* fp = fopen(file_name, "w");
	save(fp);
	fclose(fp);

}


void handle_play() {

	char* id_str = strtok(NULL, " ");
	int index = atoi(id_str);
	play(index);

}


void handle_search() {

	char* name[BUFFER_LENGTH];
	char* title[BUFFER_LENGTH];

	printf("    Artist: ");
	if (read_line(stdin, name, BUFFER_LENGTH) <= 0) {
		printf("    Artist name required.\n");
		return;
	}

	printf("    Title: ");
	int title_len = read_line(stdin, title, BUFFER_LENGTH);

	if (title_len <= 0) {
		search_song(name);  /* C언어는 매개변수의 개수가 다르면 이름이 같아도 다른 함수로 인식된다? 안되는듯 */
	}
	else {
		search_song_with_title(name, title);
	}

}


void handle_add() {

	char buffer[BUFFER_LENGTH];
	char* artist = NULL;
	char* title = NULL;
	char* path = NULL;

	printf("    Artist: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) {
		artist = _strdup(buffer);
	}

	printf("    Title: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) {
		title = _strdup(buffer);
	}

	printf("    Path: ");
	if (read_line(stdin, buffer, BUFFER_LENGTH) > 0) {
		path = _strdup(buffer);
	}

	printf("%s %s %s\n", artist, title, path);

	/* add to the music library */

	add_song(artist, title, path);

}