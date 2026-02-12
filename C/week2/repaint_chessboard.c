#include <stdio.h>

int main(void){
    int num_row;
    int num_col;
    
    scanf("%d %d", &num_row, &num_col);
    
    /* initialize the chessboard as the given condition */
    char chessboard[num_row][num_col];  /* NULL로 초기화 어떻게? */
    char row[num_col];
    
    for (int i = 0; i < num_row; i++) {
        scanf("%s", row);
        for (int j = 0; j < num_col; j++) {
            chessboard[i][j] = row[j];
        }
    }
    
   
    
    /* count the number of squares repaint for each index */
    /* and find the one with the minimum squares */
    int min_count = 64;
    
    for (int i = 0; i <= (num_row - 8); i++) {
        for (int j = 0; j <= (num_col - 8); j++) {
            int count_W = 0;
            int count_B = 0; 
            for (int row_counter = 0; row_counter < 8; row_counter++) {
                for (int col_counter = 0; col_counter < 8; col_counter ++) {
                    char current = chessboard[i + row_counter][j + col_counter];
                    if ((row_counter + col_counter) % 2 == 0) { 
                        if (current != 'W') {
                            count_W++;
                        }
                        if (current != 'B') {
                            count_B++;
                        }
                    } else { 
                        if (current != 'B') {
                            count_W++;
                        }
                        if (current != 'W') {
                            count_B++;
                        }
                    }
                }
            }
            
            if (count_B > count_W) {
                if (min_count >= count_W) {
                    min_count = count_W;
                }
            } else {
                if (min_count >= count_B) {
                    min_count = count_B;
                }                
            }
        }
    }
    printf("%d", min_count);
}
