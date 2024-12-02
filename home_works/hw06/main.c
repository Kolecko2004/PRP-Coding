#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

struct matrix_info {
    int * arr;
    int width;
    int height;
    size_t capacity;
} matrix_info;

char math_operations[99];
short arr_of_active_operations[99];
int num_of_operations = 0;
short arr_of_active_matrixes[100];

struct matrix_info result_matrix;
struct matrix_info matrices[100];

void free_all() {
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

void memory_alloc(struct matrix_info *arr) {
    arr->arr = malloc((arr->height * arr->width) * sizeof(int));
    if (arr->arr == NULL) {
        fprintf(stderr, "Allocation of memory was unsuccessful!\n");
        free_all();
        exit(1);
    }

    arr->capacity = arr->height * arr->width;
}

void matrix_plus_minus(char operation, struct matrix_info * matrix1, struct matrix_info * matrix2) {
    for (int i = 0; i < result_matrix.height * result_matrix.width; i++) {
        result_matrix.arr[i] = operation == '-' ? minus(matrix1->arr[i], matrix2->arr[i]) : plus(matrix1->arr[i], matrix2->arr[i]);
    }
}

void matrix_multiplication(struct matrix_info * matrix1, struct matrix_info * matrix2) {
    for (int matrix1_row = 0; matrix1_row < matrix1->height; matrix1_row++) {
        for (int matrix2_col = 0; matrix2_col < matrix2->width; matrix2_col++) {
            result_matrix.arr[matrix1_row * matrix2->width + matrix2_col] = 0;
            for (int matrix1_col = 0; matrix1_col < matrix1->width; matrix1_col++) {
                result_matrix.arr[matrix1_row * matrix2->width + matrix2_col] += matrix1->arr[matrix1_row * matrix1->width + matrix1_col] * matrix2->arr[matrix1_col * matrix2->width + matrix2_col];
            }
        }
    }
}

void plus_minus_size_test(struct matrix_info * matrix1, struct matrix_info * matrix2) {
    if (matrix1->width != matrix2->width || matrix1->height != matrix2->height) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        free_all();
        exit(100);
    }
}

void multiplication_size_test(struct matrix_info * matrix1, struct matrix_info * matrix2) {
    if (matrix1->width != matrix2->height) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        free_all();
        exit(100);
    }
}

void scaning_matrix(struct matrix_info * matrix) {
    int scan_result = 0;

    scan_result = fscanf(stdin, "%d", &matrix->height);
    scan_result = fscanf(stdin, "%d", &matrix->width);
    
    memory_alloc(&*matrix);

    for (int idx = 0; idx < matrix->height * matrix->width; idx++) {
        scan_result = fscanf(stdin, "%d", &matrix->arr[idx]);

        input_test(scan_result);
    }
}

void operation(char operation, struct matrix_info * matrix1, struct matrix_info * matrix2) {
    if (operation == '+' || operation == '-') {
        result_matrix.width = matrix1->width;
        result_matrix.height = matrix1->height;
        memory_alloc(&result_matrix);
        matrix_plus_minus(operation, &*matrix1, &*matrix2);
    }

    else {
        result_matrix.width = matrix2->width;
        result_matrix.height = matrix1->height;
        memory_alloc(&result_matrix);
        matrix_multiplication(&*matrix1, &*matrix2);
    }
}

void solving_matrixes() {
    for (int i = 0; i < num_of_operations; i++) {
        if (math_operations[i] == '*' && arr_of_active_operations[i] == 1) {
            int idx = i;
            while (arr_of_active_matrixes[idx] != 1) {
                idx--;
            }

            multiplication_size_test(&matrices[idx], &matrices[i + 1]);
            operation('*', &matrices[idx], &matrices[i + 1]);
            free(matrices[idx].arr);
            free(matrices[i + 1].arr);
            matrices[idx] = result_matrix;
            arr_of_active_matrixes[i + 1] = 0;
        }
    }

    for (int i = 0; i < num_of_operations; i++) {
        if ((math_operations[i] == '-' || math_operations[i] == '+') && arr_of_active_operations[i] == 1) {
            int idx = i;
            while (arr_of_active_matrixes[idx] != 1) {
                idx--;
            }
            plus_minus_size_test(&matrices[idx], &matrices[i + 1]);
            math_operations[i] == '+'? operation('+', &matrices[idx], &matrices[i + 1]) : operation('-', &matrices[idx], &matrices[i + 1]);
            free(matrices[idx].arr);
            free(matrices[i + 1].arr);
            matrices[idx] = result_matrix;
            arr_of_active_matrixes[i + 1] = 0;
        }
    }


}

void input() {
    int scan_result = 1;
    int idx = 0;
    while (scan_result != -1) {
        scaning_matrix(&matrices[idx]);
        arr_of_active_matrixes[idx] = 1;
        scan_result = fscanf(stdin, "\n%c", &math_operations[idx]);
        arr_of_active_operations[idx] = 1;
        input_test(scan_result);
        idx++;
    }
    arr_of_active_operations[idx] = -1;

    num_of_operations = idx;
}

void print_results() {
    fprintf(stdout, "%d %d\n", result_matrix.height, result_matrix.width);
    int lines = 1;
    for (int i = 0; i < result_matrix.height * result_matrix.width; i++) {
        if (i == lines * (result_matrix.width)) {
            lines++;
            fprintf(stdout, "\n");
        }
        if (i == (lines * result_matrix.width) - 1) {
            fprintf(stdout, "%d", result_matrix.arr[i]);
        } else {
            fprintf(stdout, "%d ", result_matrix.arr[i]);
        }
        
    }
    fprintf(stdout, "\n");
}

int main () {
    input();
    solving_matrixes();

    print_results();

    free_all();
    
    return 0;
}

