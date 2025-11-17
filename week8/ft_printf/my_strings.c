#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "my_strings.h"

#define ASSERT(expr) assert(expr)
#define LOG10_2 0.30102999566
#define INT_MIN -2147483648

static void reverse(char* s);

size_t strlen(char* str) {
    ASSERT(str != NULL);

    // str[i] == *(s + i)
    size_t len = 0;  // size_t는 바이트 수
    while (str[len] != '\0') {
        len++;  // char은 1바이트 자료형
    }
    return len;
}


char* strjoin(char* str1, char* str2) {
    ASSERT(str1 != NULL && str2 != NULL);

    size_t str1_len = strlen(str1);
    size_t str2_len = strlen(str2);
    size_t newstr_len = str1_len + str2_len;

    char* newstr_ptr = malloc(newstr_len + 1);  // MQ1. (char*) 형 변환 오히려 C표준에서 권장 안된다는데
    if (newstr_ptr == NULL) {
        return NULL;
    }

    size_t i = 0;
    while (str1[i] != '\0') {
        newstr_ptr[i] = str1[i];
        i++;
    }
    size_t j = 0;
    while (str2[j] != '\0') {
        newstr_ptr[i + j] = str2[j];
        j++;
    }
    newstr_ptr[i + j] = '\0';
    return newstr_ptr;
}


char* strdup(char* str) {
    ASSERT(str != NULL);

    size_t len = strlen(str);
    char* new_str = malloc(len + 1);
    if (new_str == NULL) {  // malloc 할당 실패시
        return NULL;
    }

    for (int i = 0; i <= len; i++) {  // 등호로 인해 '\0'까지 복사
        new_str[i] = str[i];
    }

    return new_str;
}


char* strchr(const char* str, int c) {  // const --> 함수 내부에선 이 문자열을 건들지 않겠다. 다만 리턴해서 얻은 포인터로 너가 건드는건 너의 책임
    ASSERT(str != NULL);

    while (*str) {  // str이 가르키는 주소의 값이 '\0'이 아닌 동안
        if (*str == (char)c) {
            return (char*)str;
        }
        str++;
    }
    return NULL;
}


char* strncpy(char* dest, const char* src, size_t n) {
    size_t i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    // src의 길이가 n보다 더 짧았을 경우 남은 공간을 '\0'으로 채움
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return dest;
}


char* ptr_to_hex(void* ptr) {
    ASSERT(ptr != NULL);

    uintptr_t intptr = (uintptr_t)ptr;
    char* hex_str = (char*)malloc(19);

    int counter = 18;
    hex_str[counter--] = '\0';

    while (intptr > 0) {  // 비어있는 자리를 0으로 채워야 하는가?
        char remainder = "0123456789abcdef"[intptr % 16];
        intptr = intptr / 16;
        hex_str[counter--] = remainder;
    }

    hex_str[counter--] = 'x';
    hex_str[counter--] = '0';
    
    return &hex_str[counter + 1];  // 근데 이러면 나중에 malloc free를 못하는데? 다시 생각해보기
}


char* int_to_str(int number) {
    int num_bits = sizeof(int) * CHAR_BIT;
    int max_digits = (int)((num_bits - 1) * LOG10_2) + 1;  // 공식: num_bits * log10_2 + 1 (부호 비트 제외)
    
    char* buf = NULL;  // 예외 처리가 끝난 뒤에 malloc 할 예정

    if (number == 0) {
        buf = strdup("0");
        return buf;
    }

    if (number == INT_MIN) {
        buf = strdup("-2147483648");
        return buf;
    }

    int is_negative = 0;
    if (number < 0) {
        is_negative = 1;
    }

    buf = malloc(max_digits + 2);  // 널문자 +1, 부호 + 1
    number = abs(number);

    int counter = 0;
    while (number != 0) {
        int remainder = number % 10;
        number /= 10;
        buf[counter] = remainder + '0';
        counter++;
    }
    
    if (is_negative) {
        buf[counter] = '-';
        buf[counter + 1] = '\0';
    }
    else {
        buf[counter] = '\0';
    }

    reverse(buf);
    return buf;
}


char* uint_to_str(unsigned int number) {
    int num_bits = sizeof(unsigned int) * CHAR_BIT;
    int max_digits = (int)(num_bits * LOG10_2) + 1;  // 공식: num_bits * log10_2 + 1

    char* buf = NULL;  // 예외 처리가 끝난 뒤에 malloc 할 예정

    if (number == 0) {
        buf = strdup("0");
        return buf;
    }

    buf = malloc(max_digits + 1);  // 널문자 +1

    int counter = 0;
    while (number != 0) {
        int remainder = number % 10;
        number /= 10;
        buf[counter] = remainder + '0';
        counter++;
    }

    buf[counter] = '\0';

    reverse(buf);
    return buf;
}


static void reverse(char* s) {
    int left = 0;
    int right = 0;
    
    while (s[right] != '\0') {
        right++;
    }
    right--;

    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        
        left++;
        right--;
    }
}
