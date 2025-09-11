#include <stdio.h>


int my_strlen(char str[]){
    int counter = 0;
    while (str[counter] != '\0'){
        counter++;
    }
    return counter;
}


int get_gcd(int num1, int num2){
    while (num2 != 0) {
        int temp = num2;
        num2 = num1 % num2;
        num1 = temp;
    }
    return num1;
}


int main() {
	char str1[2501] = "";
    char str2[2501] = "";
    
    scanf("%s", str1);
    scanf("%s", str2);
    
    int len_str1 = my_strlen(str1);
    int len_str2 = my_strlen(str2);
    
    int gcd = get_gcd(len_str1, len_str2);
    int lcm = len_str1 * len_str2 / gcd;
    
    int multiplier1 = lcm / len_str1;
    int multiplier2 = lcm / len_str2;
    
    char new_str1[151] = "";
    char new_str2[151] = "";
    
    for (int i = 0; i < multiplier1; i++) {
        for (int j = 0; j < len_str1; j++) {
            new_str1[i * len_str1 + j] = str1[j];
        }
    }
    
    for (int i = 0; i < multiplier2; i++) {
        for (int j = 0; j < len_str2; j++) {
            new_str2[i * len_str2 + j] = str2[j];
        }
    }
    
    for (int i = 0; i < lcm; i++) {
        if (new_str1[i] != new_str2[i]) {
            printf("0\n");
            return 0;
        }
    }
    printf("1\n");
    return 0;
}
