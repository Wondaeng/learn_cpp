#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
* @breif   push numbers to the front (i.e., index = 0) so that no zeroes exist inbetween
*  
* @param   size: length of line 
* @param   line: line array 
*
* @return  pointer of compressed line
*/

int* compress_line(const int size, const int* line) { 
    int* compressed_line = (int*)calloc(size, sizeof(int));
    
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (line[i] != 0) {
            compressed_line[j] = line[i];
            j++;
        }    
    }
    
    return compressed_line;
}


int* move_line(const int size, const int* line) {
    int* compressed_line = compress_line(size, line);
    int* new_line = (int*)calloc(size, sizeof(int));
    
    int i = 0;
    int j = 0;
    while (i < size) {
        if (i < size - 1 && compressed_line[i] == compressed_line[i + 1]) {
            new_line[j++] = 2 * compressed_line[i];
            i += 2;
        }
        else {
            new_line[j++] = compressed_line[i];
            i += 1;
        }
    }
    
    free(compressed_line);
    
    return new_line;
}


int* move_up(const int size, const int* board) {
    int* new_board = (int*)calloc((size * size), sizeof(int));
    
    for (int col = 0; col < size; col++) {
        int* new_line = (int*)calloc(size, sizeof(int));
        for (int row = 0; row < size; row++) {
            new_line[row] = board[row * size + col]; 
        }
        int* moved_line = move_line(size, new_line);
        
        for (int row = 0; row < size; row++) {
            new_board[row * size + col] = moved_line[row];            
        }
        
        free(new_line);
        free(moved_line);
    }
    return new_board;
}


int* move_down(const int size, const int* board) {
    int* new_board = (int*)calloc((size * size), sizeof(int));
    
    for (int col = 0; col < size; col++) {
        int* new_line = (int*)calloc(size, sizeof(int));
        for (int row = size - 1; row >= 0; row--) {
            new_line[size - 1 - row] = board[row * size + col]; 
        }
        int* moved_line = move_line(size, new_line);
        
        for (int row = size - 1; row >= 0; row--) {
            new_board[row * size + col] = moved_line[size - 1 - row];            
        }
        
        free(new_line);
        free(moved_line);
    }
    return new_board;
}



int* move_left(const int size, const int* board) {
    int* new_board = (int*)calloc((size * size), sizeof(int));
    
    for (int row = 0; row < size; row++) {
        int* new_line = (int*)calloc(size, sizeof(int));
        for (int col = 0; col < size; col++) {
            new_line[col] = board[row * size + col]; 
        }
        int* moved_line = move_line(size, new_line);
        
        for (int col = 0; col < size; col++) {
            new_board[row * size + col] = moved_line[col];            
        }
        
        free(new_line);
        free(moved_line);
    }
    return new_board;
}


int* move_right(const int size, const int* board) {
    int* new_board = (int*)calloc((size * size), sizeof(int));
    
    for (int row = 0; row < size; row++) {
        int* new_line = (int*)calloc(size, sizeof(int));
        for (int col = size - 1; col >= 0; col--) {
            new_line[size - 1 - col] = board[row * size + col]; 
        }
        int* moved_line = move_line(size, new_line);
        
        for (int col = size - 1; col >= 0; col--) {
            new_board[row * size + col] = moved_line[size - 1 - col];            
        }
        
        free(new_line);
        free(moved_line);
    }
    return new_board;
}


int* move(const int size, const int* board, const int direction) {
    if (direction == 0) {
        return move_up(size, board); 
    }
    else if (direction == 1) {
        return move_right(size, board);  
    }
    else if (direction == 2) {
        return move_down(size, board);  
    }
    else if (direction == 3) {
        return move_left(size, board);  
    }
    return NULL;
}


int max(const int num1, const int num2) {
    if (num1 > num2) {
        return num1;
    }
    return num2;
}


int find_max_in_array(const int length, const int* arr) {
    int max_val = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        } 
    }
    return max_val;
}


int find_max_recursive(const int size, const int* board, int depth) {
    // 기저 조건: depth가 0이면 현재 보드의 최댓값 반환
    if (depth == 0) {
        return find_max_in_array(size * size, board);
    }
    
    int max_value = 0;
    
    // 4방향(상하좌우)으로 모두 시도
    for (int direction = 0; direction < 4; direction++) {
        int* new_board = move(size, board, direction);
        
        // 재귀 호출로 다음 depth 탐색
        int current_max = find_max_recursive(size, new_board, depth - 1);
        
        // 최댓값 갱신
        if (current_max > max_value) {
            max_value = current_max;
        }
        
        free(new_board);
    }
    
    return max_value;
}


int main() {
    int size = 0;
    scanf("%d", &size);
    getchar();  // scanf 후 입력 스트림에 남아있는 \n 제거
	
	int* board = (int*)malloc((size * size) * sizeof(int));
	
	char buffer[(4 + 1) * 20 + 1] = "";  // 각 숫자 최대 4자리 (1024) * 최대 보드 크기 + 공백 구분자 + 줄바꿈 + 널문자
    
    for (int i = 0; i < size; i++) {
        fgets(buffer, sizeof(buffer), stdin);
        for (int j = 0; j < size; j++) {
            if (j == 0) {
                board[i * size + j] = atoi(strtok(buffer, " "));                
            }
            else {
                board[i * size + j] = atoi(strtok(NULL, " "));
            }
        }
    }
    
    // 5번 움직였을 때 최댓값 구하기
    int result = find_max_recursive(size, board, 5);
    
    printf("%d\n", result);
    
    free(board);
    
    return 0;
    
}
