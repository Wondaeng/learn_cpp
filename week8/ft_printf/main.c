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


int main()
{
    ft_echo("Hello, world!\n");
    printf("================\n");
    ft_printf_str("%s and %s.\n", "apple", "banana");
    printf("================\n");
    ft_printf_str("apple and banana 2.\n");
    printf("================\n");
    ft_printf_str("apple and %s\n");

    return 0;
}