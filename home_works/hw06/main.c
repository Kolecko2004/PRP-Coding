#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

struct matrix_info {
    int width;
    int height;
    int arr[];
} matrix_info;

struct matrix_info matrix1;
struct matrix_info matrix2;

void input_test() {}

void scaning_matrix(struct matrix_info * matrix) {
    int scan_result = 0;

    fscanf(stdin, "%d", &matrix->height);
    fprintf(stdout, "height %d\n", matrix->height);

    fscanf(stdin, "%d", &matrix->width);
    fprintf(stdout, "width %d\n", matrix->width);
    
    for (int idx_size = 0; idx_size < matrix->height * matrix->width; idx_size++) {
        scan_result = fscanf(stdin, "%d", &matrix->arr[idx_size]);
        fprintf(stdout, "%d\n", matrix->arr[idx_size]);
    }

    fprintf(stdout, "Printing arr\n");
    for (int i = 0; i < matrix->width + matrix->height; i++) {
        fprintf(stdout, "%d ", matrix->arr[i]);
    }
    fprintf(stdout, "\n");
}

void input() {
    scaning_matrix(&matrix1);
    scaning_matrix(&matrix2);
}

int main () {
    input();

    return 0;
}

