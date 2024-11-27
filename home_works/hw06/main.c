#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

struct matrix_info {
    int * arr;
    int width;
    int height;
    size_t capacity;
} matrix_info;

struct matrix_info matrix1;
struct matrix_info matrix2;
struct matrix_info result_matrix;

int plus(int val_1, int val_2) {
    return val_1 + val_2;
}

int minus(int val_1, int val_2) {
    return val_1 - val_2;
}

void memory_alloc(struct matrix_info *arr) {
    arr->arr = malloc((arr->height * arr->width) * sizeof(int));

    // if (arr->pointer == NULL) {
    //     fprintf(stderr, "Allocation of memory was unsuccessful!\n");
    //     exit(1);
    // }

    arr->capacity = arr->height * arr->width;
}

void matrix_subtraction(char operation) {
    for (int i = 0; i < result_matrix.height * result_matrix.width; i++) {
        if (operation == '-') {
            result_matrix.arr[i] = minus(matrix1.arr[i], matrix2.arr[i]);
        }
        
        else if(operation == '+') {
            result_matrix.arr[i] = plus(matrix1.arr[i], matrix2.arr[i]);
        }
    }

    fprintf(stdout, "Printing arr result |%c|\n", operation);
    for (int i = 0; i < result_matrix.height * result_matrix.width; i++) {
        fprintf(stdout, "%d ", result_matrix.arr[i]);
    }

    fprintf(stdout, "\n");
}

int hahfunc(int radek_mtrx_1, int sloupec_mtrx_1, int sloupec2xx) {
    int radek_mtrx_2 = 0;
    int result = 0;
    int sloupec2 = sloupec2xx;

    for (int i = sloupec_mtrx_1; i < (radek_mtrx_1 * matrix1.width) + matrix1.width; i++) {
        result += matrix1.arr[i] * matrix2.arr[sloupec2];
        fprintf(stdout, "Printing inside hahafunc result |%d| in idx |%d|\n", result, radek_mtrx_1);
        fprintf(stdout, "i |%d| radek_mtrx_1 |%d| sloupec2 |%d| sloupec_mtrx_1|%d|\n", i, radek_mtrx_1, sloupec2, sloupec_mtrx_1);
        sloupec2 += matrix2.width;
    }
    fprintf(stdout, "\n");
    return result;
}

void matrix_multiplication() {
    int radek = 0;
    int sloupec = 0;
    int sloupec2 = 0;
    for (int idx = 0; idx < result_matrix.width * result_matrix.height; idx++) {

        if (idx >= (radek * matrix1.width) + matrix1.width) {
            radek++;
            sloupec += matrix1.width;
            sloupec2 = 0;
        }

        fprintf(stdout, "Printing hahafunc result |%d| in idx |%d|\n", hahfunc(radek, sloupec,sloupec2), idx);
        result_matrix.arr[idx] = hahfunc(radek, sloupec,sloupec2);

        if (idx < (radek * matrix1.width) + matrix1.width) {
            sloupec2++;
        }
    }

    fprintf(stdout, "Printing arr result |*|\n");
    for (int i = 0; i < result_matrix.height * result_matrix.width; i++) {
        fprintf(stdout, "%d ", result_matrix.arr[i]);
    }

    fprintf(stdout, "\n");
}

void matrix_size_test() {
    if (matrix1.width != matrix2.width || matrix1.height != matrix2.height) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }

    result_matrix.width = matrix1.width;
    result_matrix.height = matrix1.height;
}

void input_test(int scan_result) {
    if (scan_result == 0) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }
}

void scaning_matrix(struct matrix_info * matrix) {
    int scan_result = 0;

    fscanf(stdin, "%d", &matrix->height);
    //fprintf(stdout, "height %d\n", matrix->height);////////////////////////////////////////////////////////////////////

    fscanf(stdin, "%d", &matrix->width);
    //fprintf(stdout, "width %d\n", matrix->width);////////////////////////////////////////////////////////////////////

    memory_alloc(&*matrix);


    int idx_y = 0, idx_x = 0;
    for (int idx = 0; idx < matrix->height * matrix->width; idx_x++) {
        scan_result = fscanf(stdin, "%d", &matrix->arr[idx_x][idx_y]);
        if (idx > (matrix->width - 1)) {
            idx_y++;
            idx_x = 0;
        }

        else {
            idx_x++;
        }
        input_test(scan_result);
        //fprintf(stdout, "%d\n", matrix->arr[idx_size]);
    }

////////////////////////////////////////////////////////////////////
    fprintf(stdout, "Printing arr\n");
    int x = 0, y = 0;
    for (int i = 0; i < matrix->width * matrix->height; i++) {
        fprintf(stdout, "%d ", matrix->arr[x][y]);
        if (i > matrix->width) {
            y++;
            x = 0;
            fprintf(stdout, "\n");
        }

        else {
            x++;
        }
    }

    fprintf(stdout, "\n");
////////////////////////////////////////////////////////////////////
}

void input() {
    scaning_matrix(&matrix1);

//    scaning_matrix(&matrix2);

    //matrix_size_test();

//    memory_alloc(&result_matrix);
}

int main () {
    input();
    
    //matrix_subtraction('-');
    // matrix_addition('+');
    //matrix_multiplication();
    
    return 0;
}

