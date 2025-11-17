#include <stdarg.h>
#include <unistd.h>

#include "my_strings.h"

#define ASSERT(expr) assert(expr)

void ft_echo(const char* format_str, ...) {
    write(1, format_str, strlen(format_str));
}


void ft_printf_str(const char* format_str, ...) {
    va_list ap;
    va_start(ap, format_str);
    
    size_t cs_len = strlen(format_str);
    
    for (int i = 0; i < cs_len; i++) {
        if (format_str[i] == '%') {
            i++;
            if (format_str[i] == 's') {
                char* string = va_arg(ap, char*);
                write(1, string, strlen(string));
            }
        }
        else {
            write(1, &format_str[i], 1);
        }
    }
}


int ft_printf(const char* format_str, ...) {
    va_list ap;
    va_start(ap, format_str);

    int bytes = 0;
    size_t cs_len = strlen(format_str);

    for (int i = 0; i < cs_len; i++) {
        if (format_str[i] == '%') { 
            if (format_str[i + 1] == '\0') {
                // undefined behavior (% at the end without conversion specifier)
            }
            
            i++;

            if (format_str[i] == 'c') {
                // 기본형 자동 승격? int <-> char 변환 다시 살펴보기 (글로 정리)
                char character = (char)va_arg(ap, int);
                bytes += (int)write(1, &character, sizeof(character));
            }
            else if (format_str[i] == 's') {
                char* string = va_arg(ap, char*);  // string 이 null 일때 처리 해야 됨
                bytes += (int)write(1, string, strlen(string));
            }
            else if (format_str[i] == 'p') {
                void* ptr = va_arg(ap, void*);
                char* ptr_str = ptr_to_hex(ptr);
                bytes += (int)write(1, ptr_str, strlen(ptr_str));
            }
            else if (format_str[i] == 'd' || format_str[i] == 'i') {  // scanf에선 차이가 있는데... (base 8, 10, 16 알아서 인식)
                int number = va_arg(ap, int);
                char* string = int_to_str(number);
                bytes += (int)write(1, string, strlen(string));
                free(string);
            }
            else if (format_str[i] == 'u') {
                unsigned int number = va_arg(ap, unsigned int);
                char* string = uint_to_str(number);
                bytes += (int)write(1, string, strlen(string));
                free(string);
                
            }
            //else if (format_str[i] == 'x') {

            //}
            //else if (format_str[i] == 'X') {

            //}
            else if (format_str[i] == '%') {
                bytes += (int)write(1, "%", 1);
            }
            //else {
            //    // undefined behavior (incorrect conversion specifier)
            //}
        }
        else {
            bytes += (int)write(1, &format_str[i], 1);
        }
    }

    return bytes;
}


int main()
{   
    char* word1 = "apple";
    char* word2 = "banana";
    int number1 = 42;
    int number2 = -42;

    // int (signed)
    int int_max = 2147483647;
    int int_min = -2147483648;

    // unsigned int
    unsigned int uint_max = 4294967295;
    unsigned int uint_overflow = 4294967296;
    unsigned int uint_min = 0;

    ft_printf("%s and %s. The first character of each word is %c and %c.\n", word1, word2, word1[0], word2[0]);
    ft_printf("The address of word1's first char is %p.\n", word1);
    ft_printf("The address of word1 is %p.\n", &word1);
    ft_printf("I have %d %ss.\n", number1, word1);
    ft_printf("I have %i %ss.\n", number2, word2);

    ft_printf("The maximum value that int type can have is %d & minimum is %d.\n", int_max, int_min);
    ft_printf("The maximum value that uint type can have is %u & minimum is %u.\n", uint_max, uint_min);
    ft_printf("%u looks like zero, but it is the overflow of 4294967206.\n", uint_overflow);

    return 0;
}
