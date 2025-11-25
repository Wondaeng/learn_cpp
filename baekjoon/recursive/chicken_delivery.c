#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point {
    int r;
    int c;
};
typedef struct point Point;

int get_distance(Point pos1, Point pos2) {
    return (abs(pos1.r - pos2.r) + abs(pos1.c - pos2.c));
}

int get_city_chicken_distance(int home_count, int* selected, int num_chicken, Point* home_arr, Point* chicken_arr) {
    int city_distance = 0;
    for (int i = 0; i < home_count; i++) {
        int min_distance = 999999;
        for (int j = 0; j < num_chicken; j++) {
            int distance = get_distance(home_arr[i], chicken_arr[selected[j]]);
            if (distance < min_distance) {
                min_distance = distance;
            }
        }
        city_distance += min_distance;
    }
    return city_distance;
}

int min_result = 999999;

void find_combination(int start, int depth, int num_chicken, int chicken_count,
    int* selected, int home_count, Point* home_arr, Point* chicken_arr) {
    if (depth == num_chicken) {
        int distance = get_city_chicken_distance(home_count, selected, num_chicken, home_arr, chicken_arr);
        if (distance < min_result) {
            min_result = distance;
        }
        return;
    }

    for (int i = start; i < chicken_count; i++) {
        selected[depth] = i;
        find_combination(i + 1, depth + 1, num_chicken, chicken_count, selected, home_count, home_arr, chicken_arr);
    }
}

Point create_point(int r, int c) {
    Point p = { r, c };
    return p;
}

int main() {
    int size = 0;
    int num_chicken = 0;
    scanf("%d %d", &size, &num_chicken);
    getchar();

    char* buffer = (char*)malloc((size * 2 + 10) * sizeof(char));
    Point* home_arr = (Point*)malloc((2 * size) * sizeof(Point));
    Point* chicken_arr = (Point*)malloc(13 * sizeof(Point));
    int* selected = (int*)malloc(13 * sizeof(int));

    int home_counter = 0;
    int chicken_counter = 0;

    for (int i = 0; i < size; i++) {
        fgets(buffer, size * 2 + 10, stdin);
        int col = 0;
        int j = 0;
        while (col < size && buffer[j] != '\0' && buffer[j] != '\n') {
            if (buffer[j] == '1') {
                Point pos = create_point(i, col);
                home_arr[home_counter++] = pos;
                col++;
            }
            else if (buffer[j] == '2') {
                Point pos = create_point(i, col);
                chicken_arr[chicken_counter++] = pos;
                col++;
            }
            else if (buffer[j] == '0') {
                col++;
            }
            j++;
        }
    }

    find_combination(0, 0, num_chicken, chicken_counter, selected, home_counter, home_arr, chicken_arr);

    printf("%d", min_result);

    free(buffer);
    free(home_arr);
    free(chicken_arr);
    free(selected);

    return 0;
}
