#include <stdio.h>

int main() {
    int num_testcase;
    scanf("%d", &num_testcase);
    for (int i = 0; i < num_testcase; i++) {
        int num_repeat;
        char string[21];  /* maximum length (20) + 1 for '\0' */
        
        scanf("%d %s", &num_repeat, string);
        
        /* count the length of the char array */
        int len = 0;
        while (string[len] != '\0') {
            len++;
        }
        
        char new_string[len * num_repeat + 1];  /* length after repeatition + 1 for '\0' */
        
        /* repeat same char for num_repeat, for all char in original string */
        for (int j = 0; j < len; j++) {
            for (int k = 0; k < num_repeat; k++) {
                new_string[j * num_repeat + k] = string[j];
            }
        }
        
        new_string[len * num_repeat] = '\0';  /* add '\0' at the end*/
        printf("%s\n", new_string);
    }
    return 0;
}
