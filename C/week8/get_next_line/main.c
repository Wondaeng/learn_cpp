#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("/home/jowon/test.txt", O_RDONLY);
    if (fd < 0) {
        perror("파일 열기 실패");
        return 1;
    }

    char* line = NULL;
    while (get_next_line(fd, &line) > 0) {
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}