#include <stdio.h>

int main(void) {
	char string[101] = "";
	int count = 0;

	scanf("%s", &string);

	while (string[count] != '\0') {
		count += 1;
	}

	printf("%d", count);
	return 0;
}
