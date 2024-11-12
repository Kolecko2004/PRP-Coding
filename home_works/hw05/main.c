// Caesars Cipher
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

#define INICIAL_LENGTH 5

char * str_1;
char * str_2;

struct memory_values {
    char * pointer;
    size_t capacity;
} memory_values;

struct memory_values str_1_struct;
struct memory_values str_2_struct;

void memory_alloc() {
    str_1 = malloc(INICIAL_LENGTH * sizeof(char));
    str_2 = malloc(INICIAL_LENGTH * sizeof(char));

    if (str_1 == NULL || str_2 == NULL) {
        fprintf(stderr, "Alocation of memory was unsuccessful!\n");
        exit(1);
    }

    str_1_struct.capacity = INICIAL_LENGTH;
    str_1_struct.pointer = str_1;

    str_2_struct.capacity = INICIAL_LENGTH;
    str_2_struct.pointer = str_2;
}

void memory_realloc(struct memory_values prt) {
    prt.pointer = realloc(prt.pointer,  prt.capacity * 2 * sizeof(char));
}

void input() {
    char inp_sign = ' ';
    int first_line = 0;
    int str_1_len = 0;
    int str_2_len = 0;

    while (first_line != 2) {
        str_1_len == str_1_struct.capacity? memory_realloc(str_1_struct) : str_1_len;
        str_2_len == str_2_struct.capacity? memory_realloc(str_2_struct) : str_2_len;

        inp_sign = getchar();
        
        if (first_line == 0) {
            str_1[str_1_len] = inp_sign;
            str_1_len++;
        }

        else {
            str_2[str_2_len] = inp_sign;
            str_2_len++;
        }
        
        inp_sign == '\n'? first_line++ : first_line ;
    }
    
    str_1[str_1_len] == '\0';
    str_2[str_2_len] == '\0';

    for (int i = 0; str_1[i] != '\n'; i++) {
        printf("1: %c\n", str_1[i]);
    }

    for (int i = 0; str_2[i] != '\n'; i++) {
        printf("2: %c\n", str_2[i]);
    }
}



int string_input_test() {
    int err1 = 0;
    int err2 = 0;
    int length = 0;

    for (int i = 0; str_1[i] != '\n'; i++) {
        err1 = isalpha(str_1[i]);
        length++;

        if (err1 == 0) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            exit(100);
        }
    }
        
    for (int i = 0; str_2[i] != '\n'; i++) {
        err2 = isalpha(str_2[i]);
        length--;

        if (err2 == 0) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            exit(100);
        }
    }

    if (length != 0) {
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

    while (str_1[idx] != '\n') {
        char plus = str_1[idx], minus = str_1[idx];

        while (plus != str_2[idx] && minus != str_2[idx]) {
            plus++;
            minus--;
            //fprintf(stdout, "pluschar: %d, minuschar: %d, want: %d\n", str_1[idx] + plus, str_1[idx] - minus, str_2[idx]);
            fprintf(stdout, "char str1: %c, char str2: %c, index: %d, minus: %d, plus: %d\n", str_1[idx], str_2[idx], idx, minus, plus);
        }
        fprintf(stdout, "GG\n");
        str_1[idx] = (plus == str_2[idx] ? plus : minus);

        minus = 0, plus = 0;
        idx++;
    }
    
}

int main () {
    memory_alloc();
    input();
    string_input_test();
    abc_shift();


    free(str_1);
    free(str_2);
    return 0;
}