#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

struct all_values {
    char * pattern ;
    char * file_name;
    int * lps;
    FILE * file;
    long file_length;
    char * txt_arr;
    long pattern_len;
} all_values;

struct all_values all_values;

int file_text_arr_alloc() {
    all_values.txt_arr = malloc(all_values.file_length + 1);
    if (all_values.txt_arr == NULL) {
        fprintf(stderr, "Allocation of memory was unsuccessful!\n");
        return 100;
    }

    return 0;
}

int input_test(int num_of_arguments, char ** arguments) {
    if (num_of_arguments != 3) {
        printf("Expected 3 arguments, instead program got more or less than that\n");
        return 100;
    }

    all_values.pattern = arguments[1];
    all_values.file_name = arguments[2];
    return 0;
}

void open_file() {
    printf("PATTERN: %s\n", all_values.pattern);
    printf("FILE: %s\n", all_values.file_name);

    all_values.file = fopen(all_values.file_name, "r");
    if (all_values.file == NULL) {
        fprintf(stderr, "Opening the file was unsucesfull");
        exit(100);
    }
}

void lps_for_search() {
    int length = 0;
    int lps[all_values.pattern_len];
    all_values.lps = lps;
    all_values.lps[0] = 0;
    int idx = 1;

    while (idx < all_values.pattern_len) {
        if (all_values.pattern[idx] == all_values.pattern[length]) {
            length++;
            all_values.lps[idx] = length;
            idx++;
        }

        else {
            if (length != 0) {
                length = all_values.lps[length - 1];
            }

            else {
                all_values.lps[idx] = 0;
                idx++;
            }
        }
    }

    for (int i = 0; i < all_values.pattern_len; i++) {
        fprintf(stdout, "%d", all_values.lps[i]);
    }
    fprintf(stdout, "\n");
}

void get_file_size_and_save_text() {
    fseek(all_values.file, 0, SEEK_END);
    all_values.file_length = ftell(all_values.file);
    file_text_arr_alloc();
    rewind(all_values.file);

    fread(all_values.txt_arr, 1, all_values.file_length, all_values.file);
    all_values.txt_arr[all_values.file_length] = '\0';

    while (all_values.pattern[all_values.pattern_len] != '\0') {
        all_values.pattern_len++;
    }

    // fprintf(stdout, "%ld\n", all_values.file_length);

    // int idx = 0;
    // char ch;

    // while ((ch = fgetc(all_values.file)) != EOF) {
    //     all_values.txt_arr[idx] = ch;
    //     idx++;
    // }
    // all_values.txt_arr[idx] = '\0';
}

int main (int argc, char *argv[]) {
    all_values.pattern_len = 0;
    input_test(argc, argv);

    open_file();
    
    get_file_size_and_save_text();

    // find_pattern_in_file();
    lps_for_search();
    // KMP();

    fclose(all_values.file);

    return 0;
}

