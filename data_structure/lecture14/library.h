#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct song Song;
typedef struct snode SNode;
typedef struct artist Artist;


/* ��ȯ���� ���� ���� */
struct song {
	Artist* artist;
	char* title;
	char* path;
	int index;
};


struct snode {
	struct snode* next;  /* MQ1. ���� SNode�� �ȹٲ㵵 ��? */
	struct snode* prev;
	Song* song;
};


struct artist {
	char* name;
	struct artist* next;
	SNode* head;
	SNode* tail;
};


void initialize();
void add_song(char* artist, char* title, char* path);
void status();
void load(FILE* fp);
void search_song(char* artist);
void search_song_with_title(char* artist, char* title);
void play(int index);
void save(FILE* fp);
void remove_song(int index);

#endif