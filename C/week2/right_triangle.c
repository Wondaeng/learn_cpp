#include <stdio.h>

int main() {
	int side_arr[3] = {-1, -1, -1};
	scanf("%d %d %d", &side_arr[0], &side_arr[1], &side_arr[2]);
	
	while((side_arr[0] != 0) && (side_arr[1] != 0) && (side_arr[2] != 0)) {
	    /* find the side of maximum length and its index */
	    /* and get the sum of lengths of the sides */
	    int max_index = 0;
	    int max_len = 0;
	    int sum = 0;
	    
	    for (int i = 0; i < 3; i++) {
	        sum +=  side_arr[i];
	        if (side_arr[i] >= max_len) {
	            max_len = side_arr[i];
	            max_index = i;
	        }
	    }
	    
	    /* check for triangle inequality */
	    if ((sum - max_len) <= max_len) {
	        printf("wrong\n");
	        continue;
	    }

		/* calculate the sum of squares of the other two sides*/
	    int sum_of_square = 0;
	    for (int i = 0; i < 3; i++) {
	        if (i != max_index) {
	            sum_of_square += side_arr[i] * side_arr[i];	            
	        }
	    }

		/* check for Pythagorean theorem */
	    if (sum_of_square == (side_arr[max_index] * side_arr[max_index])){
	        printf("right\n");
	    } else {
	        printf("wrong\n");
	    }
	    scanf("%d %d %d", &side_arr[0], &side_arr[1], &side_arr[2]);
	}
	return 0;
}
