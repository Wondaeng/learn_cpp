#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include "my_strings.h"


void ft_echo(const char* cs, ...) {
    write(1, cs, strlen(cs));
}


void ft_printf_str(const char* cs, ...) {
    va_list ap;
    va_start(ap, cs);
    
    size_t cs_len = strlen(cs);
    
    for (int i = 0; i < cs_len; i++) {
        if (cs[i] == '%') {
            i++;
            if (cs[i] == 's') {
                char* string = va_arg(ap, char*);
                write(1, string, strlen(string));
            }
        }
        else {
            write(1, &cs[i], 1);
        }
    }
}


int ft_printf(const char* cs, ...) {
    va_list ap;
    va_start(ap, cs);

    int bytes = 0;
    size_t cs_len = strlen(cs);

    for (int i = 0; i < cs_len; i++) {
        if (cs[i] == '%') {  // % 뒤에 아무것도 안오는 경우 e.g., "hello %" 처리
            i++;
            if (cs[i] == 'c') {
                // 기본형 자동 승격? int <-> char 변환 다시 살펴보기 (글로 정리하자)
                char character = (char)va_arg(ap, int);
                bytes += (int)write(1, &character, sizeof(character));
            }
            else if (cs[i] == 's') {
                char* string = va_arg(ap, char*);  // string 이 null 일때 처리
                bytes += (int)write(1, string, strlen(string));
            }
            else if (cs[i] == 'p') {
                void* ptr = va_arg(ap, void*);
                char* ptr_str = ptr_to_hex(ptr);
                bytes += (int)write(1, ptr_str, strlen(ptr_str));
            }
        }
        else {
            bytes += (int)write(1, &cs[i], 1);
        }
    }

    return bytes;
}


int main()
{   
    char* word1 = "apple";
    char* word2 = "banana";

    ft_printf("%s and %s. The first character of each word is %c and %c.\n", word1, word2, word1[0], word2[0]);
    ft_printf("The address of word1's first char is %p.\n", word1);
    ft_printf("The address of word1 is %p.\n", &word1);

    return 0;
}
