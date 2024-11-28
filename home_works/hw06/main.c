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
int num_of_matrixes = 0;
short arr_of_active_matrixes[100];

// struct matrix_info matrix1;
// struct matrix_info matrix2;
struct matrix_info result_matrix;
struct matrix_info matrices[100];

// void free_all() {
//     free(matrix1.arr);
//     free(matrix2.arr);
//     free(result_matrix.arr);
// }

void input_test(int scan_result) {
    if (scan_result == 0) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        // free_all();
        exit(100);
    }
}

int plus(int val_1, int val_2) {
    return val_1 + val_2;
}

int minus(int val_1, int val_2) {
    return val_1 - val_2;
}

// void scaning_math_operations() {
//     int scan_result = fscanf(stdin, "\n%c", &math_operations);
//     input_test(scan_result);
// }

void memory_alloc(struct matrix_info *arr) {
    arr->arr = malloc((arr->height * arr->width) * sizeof(int));

    // if (arr->pointer == NULL) {
    //     fprintf(stderr, "Allocation of memory was unsuccessful!\n");
    //     exit(1);
    // }

    arr->capacity = arr->height * arr->width;
}

void matrix_plus_minus(char operation, struct matrix_info * matrix1, struct matrix_info * matrix2) {
    for (int i = 0; i < result_matrix.height * result_matrix.width; i++) {
        result_matrix.arr[i] = operation == '-' ? minus(matrix1->arr[i], matrix2->arr[i]) : plus(matrix1->arr[i], matrix2->arr[i]);
    }
}

void matrix_multiplication(struct matrix_info * matrix1, struct matrix_info * matrix2) {
    for (int matrix1_row = 0; matrix1_row < matrix1->height; matrix1_row++) { // Loop over rows of matrix1
        for (int matrix2_col = 0; matrix2_col < matrix2->width; matrix2_col++) { // Loop over columns of matrix2
            result_matrix.arr[matrix1_row * matrix2->width + matrix2_col] = 0; // Initialize result_matrix cell
            for (int matrix1_col = 0; matrix1_col < matrix1->width; matrix1_col++) { // Loop over columns of matrix1 (or rows of matrix2)
                result_matrix.arr[matrix1_row * matrix2->width + matrix2_col] += matrix1->arr[matrix1_row * matrix1->width + matrix1_col] * matrix2->arr[matrix1_col * matrix2->width + matrix2_col];
            }
        }
    }

    // fprintf(stdout, "Printing result arr\n");
    // for (int i = 0; i < result_matrix.width * result_matrix.height; i++) {
    //      fprintf(stdout, "%d ", result_matrix.arr[i]);
    // }

    // fprintf(stdout, "\n");
}



// void matrix_size_test() {
//     if (math_operations == '*') {
//         if (matrix1.width != matrix2.height) {
//             fprintf(stderr, "Error: Chybny vstup!\n");
//             free_all();
//             exit(100);
//         }
//     }

//     else if(math_operations == '-' || math_operations == '+') {
//         if (matrix1.width != matrix2.width || matrix1.height != matrix2.height) {
//             fprintf(stderr, "Error: Chybny vstup!\n");
//             free_all();
//             exit(100);
//         }
//     }
// }

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
    fprintf(stdout, "Printing arr\n");
    for (int i = 0; i < matrix->width * matrix->height; i++) {
         fprintf(stdout, "%d ", matrix->arr[i]);
    }

    fprintf(stdout, "\n");
////////////////////////////////////////////////////////////////////
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

void big_math() {
    int idx = 0;
    for (int i = 0; i < num_of_matrixes; i++) {
        fprintf(stdout, "%d idx\n", i);

        if (math_operations[i] == '*' & arr_of_active_operations[i] == 1) {
            fprintf(stdout, "%d idx\n", i);
            while (arr_of_active_matrixes[idx] != 1) {
                idx++;
            }
            fprintf(stdout, "%d idx\n", i);
            operation('*', &matrices[idx], &matrices[i + 1]);
            matrices[idx] = result_matrix;
            arr_of_active_matrixes[i + 1] = 0;
            
            fprintf(stdout, "Printing result arr\n");
            for (int i = 0; i < result_matrix.width * result_matrix.height; i++) {
                fprintf(stdout, "%d ", result_matrix.arr[i]);
            }

            fprintf(stdout, "\n");
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
        //input_test(scan_result);
        //scan_result = scaning_math_operations();
        idx++;
    }

    fprintf(stdout, "Printing result arr\n");
    for (int i = 0; i < 3; i++) {
        fprintf(stdout, "%d ", math_operations[i]);
        }

    fprintf(stdout, "\n");

    num_of_matrixes = idx + 1;
    big_math();
    // scaning_matrix(&matrix1);
    // scaning_math_operations();
    // fprintf(stdout, "operation |%c|\n", math_operations);
    // scaning_matrix(&matrix2);

    //matrix_size_test();
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

    //operation();

    print_results();

    // free_all();
    
    return 0;
}

