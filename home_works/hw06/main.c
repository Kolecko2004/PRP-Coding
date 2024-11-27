#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

struct matrix_info {
    int * arr;
    int width;
    int height;
    size_t capacity;
} matrix_info;

char math_operation;

struct matrix_info matrix1;
struct matrix_info matrix2;
struct matrix_info result_matrix;

void free_all() {
    free(matrix1.arr);
    free(matrix2.arr);
    free(result_matrix.arr);
}

void input_test(int scan_result) {
    if (scan_result == 0) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        free_all();
        exit(100);
    }
}

int plus(int val_1, int val_2) {
    return val_1 + val_2;
}

int minus(int val_1, int val_2) {
    return val_1 - val_2;
}

void scaning_math_operation() {
    int scan_result = fscanf(stdin, "\n%c", &math_operation);
    input_test(scan_result);
}

void memory_alloc(struct matrix_info *arr) {
    arr->arr = malloc((arr->height * arr->width) * sizeof(int));

    // if (arr->pointer == NULL) {
    //     fprintf(stderr, "Allocation of memory was unsuccessful!\n");
    //     exit(1);
    // }

    arr->capacity = arr->height * arr->width;
}

void matrix_plus_minus(char operation) {
    for (int i = 0; i < result_matrix.height * result_matrix.width; i++) {
        result_matrix.arr[i] = operation == '-' ? minus(matrix1.arr[i], matrix2.arr[i]) : plus(matrix1.arr[i], matrix2.arr[i]);
    }
}

// int hahfunc(int radek_mtrx_1, int sloupec_mtrx_1, int sloupec2xx) {
//     int radek_mtrx_2 = 0;
//     int result = 0;
//     int sloupec2 = sloupec2xx;

//     for (int i = sloupec_mtrx_1; i < (radek_mtrx_1 * matrix1.width) + matrix1.width; i++) {
//         result += matrix1.arr[i] * matrix2.arr[sloupec2];
//         fprintf(stdout, "Printing inside hahafunc result |%d| in idx |%d|\n", result, radek_mtrx_1);
//         fprintf(stdout, "i |%d| radek_mtrx_1 |%d| sloupec2 |%d| sloupec_mtrx_1|%d|\n", i, radek_mtrx_1, sloupec2, sloupec_mtrx_1);
//         sloupec2 += matrix2.width;
//     }
//     fprintf(stdout, "\n");
//     return result;
// }

void matrix_multiplication() {
    for (int matrix1_row = 0; matrix1_row < matrix1.height; matrix1_row++) { // Loop over rows of matrix1
        for (int matrix2_col = 0; matrix2_col < matrix2.width; matrix2_col++) { // Loop over columns of matrix2
            result_matrix.arr[matrix1_row * matrix2.width + matrix2_col] = 0; // Initialize result_matrix cell
            for (int matrix1_col = 0; matrix1_col < matrix1.width; matrix1_col++) { // Loop over columns of matrix1 (or rows of matrix2)
                result_matrix.arr[matrix1_row * matrix2.width + matrix2_col] += matrix1.arr[matrix1_row * matrix1.width + matrix1_col] * matrix2.arr[matrix1_col * matrix2.width + matrix2_col];
            }
        }
    }
}

void matrix_size_test() {
    if (math_operation == '*') {
        if (matrix1.width != matrix2.height) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            free_all();
            exit(100);
        }
    }

    else if(math_operation == '-' || math_operation == '+') {
        if (matrix1.width != matrix2.width || matrix1.height != matrix2.height) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            free_all();
            exit(100);
        }
    }
}

void scaning_matrix(struct matrix_info * matrix) {
    int scan_result = 0;

    fscanf(stdin, "%d", &matrix->height);
    //fprintf(stdout, "height %d\n", matrix->height);////////////////////////////////////////////////////////////////////

    fscanf(stdin, "%d", &matrix->width);
    //fprintf(stdout, "width %d\n", matrix->width);////////////////////////////////////////////////////////////////////

    memory_alloc(&*matrix);

    for (int idx = 0; idx < matrix->height * matrix->width; idx++) {
        scan_result = fscanf(stdin, "%d", &matrix->arr[idx]);

        input_test(scan_result);
        //fprintf(stdout, "%d\n", matrix->arr[idx_size]);
    }

////////////////////////////////////////////////////////////////////
    // fprintf(stdout, "Printing arr\n");
    // for (int i = 0; i < matrix->width * matrix->height; i++) {
    //     fprintf(stdout, "%d ", matrix->arr[i]);
    // }

    // fprintf(stdout, "\n");
////////////////////////////////////////////////////////////////////
}

void input() {
    scaning_matrix(&matrix1);
    scaning_math_operation();
    //fprintf(stdout, "operation |%c|\n", math_operation);
    scaning_matrix(&matrix2);

    matrix_size_test();
}

void operation() {
    if (math_operation == '+' || math_operation == '-') {
        result_matrix.width = matrix1.width;
        result_matrix.height = matrix1.height;
        memory_alloc(&result_matrix);
        matrix_plus_minus(math_operation);
    }

    else {
        result_matrix.width = matrix1.height;
        result_matrix.height = matrix2.width;
        memory_alloc(&result_matrix);
        matrix_multiplication();
    }
}

void print_results() {
    fprintf(stdout, "%d %d\n", result_matrix.height, result_matrix.width);
    int lines = 1;
    for (int i = 0; i < result_matrix.height * result_matrix.width; i++) {
        if (i >= lines * (result_matrix.height)) {
            lines++;
            fprintf(stdout, "\n");
        }
        fprintf(stdout, "%d ", result_matrix.arr[i]);
    }
    fprintf(stdout, "\n");
}

int main () {
    input();

    operation();

    print_results();

    free_all();
    
    return 0;
}

