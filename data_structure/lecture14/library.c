#define _CRT_SECURE_NO_WARNINGS

#include "library.h"
#include "string_tools.h"
#include <windows.h>

#define NUM_CHARS 256  // 2^8 = 256 (1byte의 모든 서로 다른 값의 경우의 수, 분류는 이니셜 한글자로만 함)
#define SIZE_INDEX_TABLE 100
#define BUFFER_LENGTH 200


Artist* artist_directory[NUM_CHARS];
SNode* index_directory[SIZE_INDEX_TABLE];


int num_index = 0;


void insert_node(Artist* ptr_artist, SNode* ptr_snode);
void insert_to_index_directory(Song* ptr_song);
void print_artist(Artist* p);
void print_song(Song* ptr_song);
void save(FILE* fp);
void save_artist(Artist* p, FILE* fp);
void save_song(Song* ptr_song, FILE* fp);
void destroy_song(Song* ptr_song);
void remove_snode(Artist* ptr_artist, SNode* ptr_snode);
Artist* find_artist(char* name);
SNode* find_snode(Artist* ptr_artist, char* title);


void initialize() {
	for (int i = 0; i < NUM_CHARS; i++) {
		artist_directory[i] = NULL;
	}
	for (int i = 0; i < SIZE_INDEX_TABLE; i++) {
		index_directory[i] = NULL;
	}
}


void load(FILE* fp) {
	char buffer[BUFFER_LENGTH];
	char* name;
	char* title;
	char* path;

	while (1) {  // infinite loop
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0) {  // get user input as a line
			break;
		}

		name = strtok(buffer, "#");
		if (strcmp(name, " ") == 0) {
			name = NULL;
		}
		else {
			name = _strdup(name);
		}

		title = strtok(NULL, "#");
		if (strcmp(title, " ") == 0) {
			title = NULL;
		}
		else {
			title = _strdup(title);
		}

		path = strtok(NULL, "#");
		if (strcmp(path, " ") == 0) {
			path = NULL;
		}
		else {
			path = _strdup(path);
		}

		// printf("%s %s %s\n", name, title, path);
		add_song(name, title, path);
	}
}


void search_song_with_title(char* artist, char* title) {
	
	Artist* ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {
		printf("No such artist exists.\n");
		return;
	}

	SNode* ptr_snode = find_snode(ptr_artist, title);

	if (ptr_snode != NULL) {
		printf("Found:\n");
		print_song(ptr_snode->song);
	}
	else {
		printf("No such song exists.\n");
		return;
	}

}


void search_song(char* artist) {

	Artist* ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {
		printf("No such artist exists.\n");
		return;
	}
	printf("Found:\n");
	print_artist(ptr_artist);

}


SNode* find_snode(Artist* ptr_artist, char* title) {

	SNode* ptr_snode = ptr_artist->head;
	while (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0) {
		ptr_snode = ptr_snode->next;
	}

	if (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) == 0) {
		return ptr_snode;
	}
	else {
		return NULL;
	}

}


Artist* create_artist_instance(char* name) {

	Artist* ptr_artist = (Artist*)malloc(sizeof(Artist));
	ptr_artist->name = name;
	ptr_artist->head = NULL;
	ptr_artist->tail = NULL;
	ptr_artist->next = NULL;

	return ptr_artist;

}


Artist* add_artist(char* name) {
	
	
	Artist* ptr_artist = create_artist_instance(name);

	Artist* p = artist_directory[(unsigned char)name[0]];  // 새롭게 만든 Artist를 삽입할 연결리스트의 첫번째 주소

	Artist* q = NULL;

	while (p != NULL && strcmp(p->name, name) < 0) {
		q = p;
		p = p->next;
	}

	if (p == NULL && q == NULL) {  // case 1. empty list
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else if (q == NULL) { // case 2. add before head
		ptr_artist->next = artist_directory[(unsigned char)name[0]];
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else {  // case 3. add after q
		ptr_artist->next = p;
		q->next = ptr_artist;
	}

	return ptr_artist;

}


Song* create_song_instance(Artist* ptr_artist, char* title, char* path) {
	
	Song* ptr_song = (Song*)malloc(sizeof(Song));
	ptr_song->artist = ptr_artist;
	ptr_song->title = title;
	ptr_song->path = path;
	ptr_song->index = num_index;
	num_index++;
	
	return ptr_song;

}


void add_song(char* artist, char* title, char* path) {
	// check if the artist already exists
	// return NULL if does not exists, otherwise return the pointer of the artist
	Artist* ptr_artist = find_artist(artist);  
	if (ptr_artist == NULL) {
		ptr_artist = add_artist(artist);
	}
	
	// add the song to the artist pointed by ptr_artist
	Song* ptr_song = create_song_instance(ptr_artist, title, path);
	SNode* ptr_snode = (SNode*)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;
	ptr_snode->next = NULL;
	ptr_snode->prev = NULL;

	// insert node
	insert_node(ptr_artist, ptr_snode);
	insert_to_index_directory(ptr_song);
}


void insert_to_index_directory(Song* ptr_song) {

	SNode* ptr_snode = (SNode*)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;
	ptr_snode->next = NULL;
	ptr_snode->prev = NULL;  // will not be used

	int index = ptr_song->index % SIZE_INDEX_TABLE;
	
	// add SNode into single linked list of index_directory[index]
	SNode* p = index_directory[index];
	SNode* q = NULL;
	while (p != NULL && strcmp(p->song->title, ptr_song->title) < 0) {
		q = p;
		p = p->next;
	}

	if (q == NULL) { // add_first
		ptr_snode->next = p;
		index_directory[index] = ptr_snode;
	}
	else { // add_after_q
		ptr_snode->next = p;
		q->next = ptr_snode;
	}

}


void insert_node(Artist* ptr_artist, SNode* ptr_snode) {

	SNode* p = ptr_artist->head;

	while (p != NULL && strcmp(p->song->title, ptr_snode->song->title) < 0) {
		p = p->next;
	}

	if (ptr_artist->head == NULL) {  // case 1. empty
		ptr_artist->head = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else if (p == ptr_artist->head) {  // case 2. at the front
		ptr_snode->next = ptr_artist->head;
		ptr_artist->head->prev = ptr_snode;
		ptr_artist->head = ptr_snode;
	}
	else if (p == NULL) {  // case 3. at the end
		ptr_snode->prev = ptr_artist->tail;
		ptr_artist->tail->next = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else {  // case 4. in between (general case: add before p)
		ptr_snode->next = p;
		ptr_snode->prev = p->prev;
		p->prev = ptr_snode;
	}
}


Artist* find_artist(char* name) {
	/*
	name[0]: 00000000 ~ 11111111 이진수를 정수로 바로 넣음

	문제점: 부호가 있는 signed integer의 경우, 첫비트가 1이면 음수임
	11001111 -> 00000000000000000000000011001111 같이 char -> int 변환이 될 것 같지만 아님
	첫 비트가 0이면 다 0으로 채우지만, 첫 비트가 1이면 다 1로 채움 -> 11111111111111111111111111001111
	*/
	Artist* p = artist_directory[(unsigned char)name[0]];  // pointer of first artist with initial name[0]
	while (p != NULL && strcmp(p->name, name) < 0) {  // 내가 찾는 이름보다 현재 노드의 이름이 더 같거나 크다(알파벳 순으로 뒤)면 더이상 순회할 필요 없음
		p = p->next;
	}
	if (p != NULL && strcmp(p->name, name) == 0) {
		return p;
	}
	else {
		return NULL;
	}
}


void status() {
	for (int i = 0; i < NUM_CHARS; i++) {
		Artist* p = artist_directory[i];
		while (p != NULL) {
			print_artist(p);
			p = p->next;
		}
	}
}


void print_artist(Artist* p) {
	printf("%s\n", p->name);
	SNode* ptr_snode = p->head;
	while (ptr_snode != NULL) {
		print_song(ptr_snode->song);
		ptr_snode = ptr_snode->next;
	}
}


void print_song(Song* ptr_song) {
	printf("    %d: %s, %s\n", ptr_song->index, ptr_song->title, ptr_song->path);
}


SNode* find_song(int index) {

	SNode* ptr_snode = index_directory[index % SIZE_INDEX_TABLE];
	while (ptr_snode != NULL && ptr_snode->song->index != index) {
		ptr_snode = ptr_snode->next;
	}

	return ptr_snode;

}


void play(int index) {

	SNode* ptr_snode = find_song(index);
	if (ptr_snode == NULL) {
		printf("No such song exists.\n");
	}

	printf("Found the song: %s\n", ptr_snode->song->title);

	// ShellExcute(GetDesktopWindow(), "open", ptr_snode->song->path, NULL, NULL, SW_SHOW);

}


void save(FILE* fp) {
	for (int i = 0; i < NUM_CHARS; i++) {
		Artist* p = artist_directory[i];
		while (p != NULL) {
			save_artist(p, fp);
			p = p->next;
		}
	}
}


void save_artist(Artist* p, FILE* fp) {
	SNode* ptr_snode = p->head;
	while (ptr_snode != NULL) {
		save_song(ptr_snode->song, fp);
		ptr_snode = ptr_snode->next;
	}
}


void save_song(Song* ptr_song, FILE* fp) {
	
	if (ptr_song->artist != NULL) {
		fprintf(fp, "%s#", ptr_song->artist->name);
	}
	else {
		fprintf(fp, " #");
	}


	if (ptr_song->title != NULL) {
		fprintf(fp, "%s#", ptr_song->title);
	}
	else {
		fprintf(fp, " #");
	}


	if (ptr_song->path != NULL) {
		fprintf(fp, "%s#\n", ptr_song->path);
	}
	else {
		fprintf(fp, " #\n");
	}

}


void remove_song(int index) {

	// find the song
	SNode* p = index_directory[index % SIZE_INDEX_TABLE];  // 내가 검색해야하는 연결리스트의 head 노드의 주소
	SNode* q = NULL;  // p의 이전 노드
	while (p != NULL && p->song->index != index) {
		q = p;
		p = p->next;
	}


	if (p == NULL) {  // empty list OR not exsit
		printf("No such song exists.\n");
		return;
	}

	Song* ptr_song = p->song;
	if (q == NULL) {  // remove first node (head) 
		index_directory[index % SIZE_INDEX_TABLE] = p->next;
	}
	else {  // remove after q
		q->next = p->next;  // q->next = q->next->next;
	}
	free(p);

	Artist* ptr_artist = ptr_song->artist;


	// find SNode (of the song) of double linked list of ptr_artist 
	SNode* ptr_snode = find_snode(ptr_artist, ptr_song->title);
	
	if (ptr_snode == NULL) {
		printf("Not found SNode - something went wrong,\n");
		return;
	} 

	remove_snode(ptr_artist, ptr_snode);
	destroy_song(ptr_song);

}


void remove_snode(Artist* ptr_artist, SNode* ptr_snode) {

	SNode* first = ptr_artist->head;
	SNode* last = ptr_artist->tail;
	if (first == ptr_snode && last == ptr_snode) {  // only one node in linked list
		ptr_artist->head = NULL;
		ptr_artist->tail = NULL;
	}
	else if (first == ptr_snode) {  // remove first node (head)
		ptr_artist->head = first->next;
		ptr_artist->head->prev = NULL;
	}
	else if (last == ptr_snode) {  // remove last node (tail)
		ptr_artist->tail = last->prev;
		ptr_artist->tail->next = NULL;
	}
	else {  // remove in-between (general case)
		ptr_snode->prev->next = ptr_snode->next;
		ptr_snode->next->prev = ptr_snode->prev;
	}

	free(ptr_snode);

}


void destroy_song(Song* ptr_song) {
	if (ptr_song->title != NULL) {
		free(ptr_song->title);
	}
	if (ptr_song->path != NULL) {
		free(ptr_song->path);
	}
	free(ptr_song);
}