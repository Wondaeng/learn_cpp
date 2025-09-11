#include <stdio.h>


int my_strlen(char str[]){
    int counter = 0;
    while (str[counter] != '\0'){
        counter++;
    }
    return counter;
}


int main(void) {
    char number_str[6] = "";
    scanf("%s", number_str);
    while (number_str[0] != '0') {
        
        int len = my_strlen(number_str);
        
        int is_palindrom = 1; 
        for (int i = 0; i < (len / 2); i++) {
            if (number_str[i] != number_str[(len - 1) - i]) {
                is_palindrom = 0;
                break;
            }
        }
        
        if (is_palindrom) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
        scanf("%s", number_str);
    }
}
