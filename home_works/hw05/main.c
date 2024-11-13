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
    prt->pointer = realloc(prt->pointer, prt->capacity * 2 * sizeof(char));
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
        str_1_len == str_1_struct.capacity? memory_realloc(&str_1_struct) : str_1_len;
        str_2_len == str_2_struct.capacity? memory_realloc(&str_2_struct) : str_2_len;

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

    for (int i = 0; str_1_struct.pointer[i] != '\n'; i++) {
        printf("1: %c\n", str_1_struct.pointer[i]);
    }

    for (int i = 0; str_2_struct.pointer[i] != '\n'; i++) {
        printf("2: %c\n", str_2_struct.pointer[i]);
    }
}

int string_input_test() {
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

void print_output() {

}

void input_compare() {

}

void abc_shift() {
    int idx = 0;

    while (str_1_struct.pointer[idx] != '\n') {
        char plus = str_1_struct.pointer[idx], minus = str_1_struct.pointer[idx];

        while (plus != str_2_struct.pointer[idx] && minus != str_2_struct.pointer[idx]) {
            plus++;
            minus--;
            //fprintf(stdout, "pluschar: %d, minuschar: %d, want: %d\n", str_1_struct.pointer[idx] + plus, str_1_struct.pointer[idx] - minus, str_2_struct.pointer[idx]);
            fprintf(stdout, "char str1: %c, char str2: %c, index: %d, minus: %d, plus: %d\n", str_1_struct.pointer[idx], str_2_struct.pointer[idx], idx, minus, plus);
        }
        fprintf(stdout, "GG\n");
        str_1_struct.pointer[idx] = (plus == str_2_struct.pointer[idx] ? plus : minus);

        minus = 0, plus = 0;
        idx++;
    }   
}

int main () {
    memory_alloc(&str_1_struct);
    memory_alloc(&str_2_struct);
    input();
    string_input_test();
    abc_shift();


    free(str_1_struct.pointer);
    free(str_2_struct.pointer);
    return 0;
}