// Caesars Cipher
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

#define INICIAL_LENGTH 5

struct memory_values {
    char * pointer;
    size_t capacity;
    size_t size;
} memory_values;

struct memory_values str_1_struct;
struct memory_values str_2_struct;
struct memory_values arr_of_shift;

void memory_alloc(struct memory_values *prt) {
    prt->pointer = malloc(INICIAL_LENGTH * sizeof(char));

    if (prt->pointer == NULL) {
        fprintf(stderr, "Allocation of memory was unsuccessful!\n");
        exit(1);
    }

    prt->capacity = INICIAL_LENGTH;
    prt->size = 0;
}

void memory_realloc(struct memory_values *prt) {
    prt->pointer = realloc(prt->pointer, prt->capacity * 4 * sizeof(char));
    if (prt->pointer == NULL) {
        fprintf(stderr, "Reallocation of memory was unsuccessful!\n");
        exit(1);
    }
    prt->capacity *= 2;
}

void input() {
    char inp_sign = ' ';
    int first_line = 0;
    int str_1_len = 0;
    int str_2_len = 0;

    while (first_line != 2) {
        if (str_1_len + 1 >= str_1_struct.capacity) {
            memory_realloc(&str_1_struct);
        }
        if (str_2_len + 1 >= str_2_struct.capacity) {
            memory_realloc(&str_2_struct);
        }

        inp_sign = getchar();
        if (first_line == 0) {
            str_1_struct.pointer[str_1_len] = inp_sign;
            str_1_len++;
        }

        else {
            str_2_struct.pointer[str_2_len] = inp_sign;
            str_2_len++;
        }
        
        inp_sign == '\n'? first_line++ : first_line ;
    }
    
    str_1_struct.pointer[str_1_len] = '\0';
    str_2_struct.pointer[str_2_len] = '\0';

    str_1_struct.size = str_1_len;
    str_2_struct.size = str_2_len;
}

void string_input_test() {
    int err1 = 0;
    int err2 = 0;

    for (int i = 0; str_1_struct.pointer[i] != '\n'; i++) {
        err1 = isalpha(str_1_struct.pointer[i]);

        if (err1 == 0) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            exit(100);
        }
    }
        
    for (int i = 0; str_2_struct.pointer[i] != '\n'; i++) {
        err2 = isalpha(str_2_struct.pointer[i]);

        if (err2 == 0) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            exit(100);
        }
    }

    if (str_1_struct.size != str_2_struct.size) {
        fprintf(stderr, "Error: Chybna delka vstupu!\n");
        exit(101);
    }
}

int most_frequent_shift() {
    // int max_count = 0, most_frequent = arr_of_shift.pointer[0];

    // for (int i = 0; i <= arr_of_shift.size - 1; i++) {
    //     int count = 0;

    //     for (int j = 0; j <= arr_of_shift.size - 1; j++) {
    //         if (arr_of_shift.pointer[j] == arr_of_shift.pointer[i]) {
    //             count++;
    //         }
    //         fprintf(stdout, "shift: %d, count shift: %d\n", );
    //     }
    //     if (count > max_count) {
    //         max_count = count;
    //         most_frequent = arr_of_shift.pointer[i];
    //     }
    // } 

    int max_count = 0, most_frequent = 0, all_shifts[256] = {0};

    for (int i = 0; i < arr_of_shift.size; i++) {
        all_shifts[(int)arr_of_shift.pointer[i]]++;
        if (all_shifts[(int)arr_of_shift.pointer[i]] > max_count) {
            max_count = all_shifts[(int)arr_of_shift.pointer[i]];
            most_frequent = arr_of_shift.pointer[i];
        }
    }

    return most_frequent;
}

void shift_all_letters(int shift) {
    fprintf(stdout, "#################################################################################\n");
    int j = shift;
    for (int i = 0; i <= arr_of_shift.size - 1; i++) {
        while (j != 0) {
            shift > 0 ? str_1_struct.pointer[i]++ : str_1_struct.pointer[i]--;
            if (isalpha(str_1_struct.pointer[i])) {
                shift > 0 ? j-- : j++;
            }
        }
        j = shift;

        fprintf(stdout, "%c", str_1_struct.pointer[i]);
    }
    
    fprintf(stdout, "\n");
}

void print_output() {

}

void abc_shift() {
    int idx = 0;

    while (str_1_struct.pointer[idx] != '\n') {
        char plus = 0, minus = 0;

        while (str_1_struct.pointer[idx] + plus != str_2_struct.pointer[idx]) {
            plus++;
            if (isalpha(str_1_struct.pointer[idx] + plus) == 0) {
                minus++;
            }
        }
        arr_of_shift.pointer[idx] = plus - minus;

        arr_of_shift.size++;

        if (arr_of_shift.size >= arr_of_shift.capacity) {
            memory_realloc(&arr_of_shift);
        }

        plus = 0, minus = 0;
        idx++;
    }   
}

int main () {
    memory_alloc(&str_1_struct);
    memory_alloc(&str_2_struct);
    memory_alloc(&arr_of_shift);
    input();
    string_input_test();
    abc_shift();
    int shift = most_frequent_shift();
    shift_all_letters(shift);


    free(str_1_struct.pointer);
    free(str_2_struct.pointer);
    free(arr_of_shift.pointer);
    return 0;
}
