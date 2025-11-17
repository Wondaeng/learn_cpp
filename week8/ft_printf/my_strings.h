#pragma once
#ifndef MY_STRINGS_H
#define MY_STRINGS_H

#include <stdlib.h>
#include <assert.h>

size_t strlen(char* str);
char* strdup(char* str);
char* strjoin(char* str1, char* str2);
char* strchr(const char*, int c);
char* strncpy(char* dest, const char* src, size_t n);
char* ptr_to_hex(void* ptr);
char* int_to_str(int number);
char* uint_to_str(unsigned int number);

#endif
