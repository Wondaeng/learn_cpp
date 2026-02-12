#include <stdio.h>

int main(void){
    int num_participant = 0;
    scanf("%d", &num_participant);

    int num_size_arr[6] = {0, };
    for (int i = 0; i < 6; i++) {
        scanf("%d", &num_size_arr[i]);
    }
    
    
    int shirt_bundle_size = 0;
    int pen_bundle_size = 0;
    
    scanf("%d %d", &shirt_bundle_size, &pen_bundle_size);
    
    int shirt_bundle_count = 0;
    for (int i = 0; i < 6; i++) {
        shirt_bundle_count += num_size_arr[i] / shirt_bundle_size;
        if ((num_size_arr[i] % shirt_bundle_size) != 0) {
            shirt_bundle_count += 1;
        }
    }
    
    int pen_bundle_count = num_participant / pen_bundle_size;
    int pen_piece_count = num_participant % pen_bundle_size;
    
    printf("%d\n", shirt_bundle_count);
    printf("%d %d\n", pen_bundle_count, pen_piece_count);
    return 0;
}
