#include <stdio.h>

int main(void){
    int num_cases = 0;
    scanf("%d", &num_cases);
    
    char str1[1001] = "";
    char str2[1001] = "";

    /* 26 means the number of alphabets */
    int alphabet_count1[26] = {0, }; 
    int alphabet_count2[26] = {0, };
    
    for (int i = 0; i < num_cases; i++){
        scanf("%s %s", str1, str2);
        
        for (int j = 0; str1[j] != '\0'; j++) {
            alphabet_count1[str1[j] - 'a']++;
        }
        for (int j = 0; str2[j] != '\0'; j++) {
            alphabet_count2[str2[j] - 'a']++;
        }
        
        for (int j = 0; j < 26; j++) {
            if (alphabet_count1[j] != alphabet_count2[j]) {
                printf("Impossible\n");
                break;
            }
            if (j == 25){
                printf("Possible\n");
            }
        }
        
        for (int j = 0; j < 26; j++) {
            alphabet_count1[j] = 0;   
            alphabet_count2[j] = 0;
        }
    }
    
    return 0;
}
