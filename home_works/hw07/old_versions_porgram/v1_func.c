#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

struct all_values {
    char * pattern ;
    long pattern_len;

    FILE * file;
    char * file_name;
    long file_length;
    char * txt_arr;

    int * lps;
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
    // printf("PATTERN: %s\n", all_values.pattern);
    // printf("FILE: %s\n", all_values.file_name);

    all_values.file = fopen(all_values.file_name, "r");
    if (all_values.file == NULL) {
        fprintf(stderr, "Opening the file was unsucesfull");
        exit(100);
    }
}

void lps_for_search() {
    int length = 0;
    all_values.lps = malloc(all_values.pattern_len * sizeof(int));
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
/////////////////////////////////////////////////
    // fprintf(stdout, "First lps value print\n");
    // for (int i = 0; i < all_values.pattern_len; i++) {
    //     fprintf(stdout, "%d", all_values.lps[i]);
    // }
    // fprintf(stdout, "\n");
/////////////////////////////////////////////////
}

void print_line(char * line) {
    // fprintf(stdout, "here is line with pattern: ");
    for (int i = 0; line[i] != '\n'; i++) {
        fprintf(stdout, "%c", line[i]);
    }
    fprintf(stdout, "\n");
}

int kmp_search_in_line(char *line) {
    int line_length = 0;
    while(line[line_length] != '\n') {
        line_length++;
    }

    int idx_line = 0, idx_pattern = 0;

    // fprintf(stdout, "line_length: %d\n",  line_length);
    // fprintf(stdout, "patt_length: %ld\n",  all_values.pattern_len);
    // fprintf(stdout, "idx_line: %d\n",  idx_line);
    // fprintf(stdout, "idx_pattern: %d\n",  idx_pattern);
    // fprintf(stdout, "pattern: \n");
    // for (int i = 0; all_values.pattern[i] != '\0'; i++) {
    //     fprintf(stdout, "%c", all_values.pattern[i]);
    // }
    // fprintf(stdout, "\n");
    // fprintf(stdout, "Second lps value print\n");
    // for (int i = 0; i < all_values.pattern_len; i++) {
    //     fprintf(stdout, "|%d|", i);
    //     fprintf(stdout, "%d", all_values.lps[i]);
    // }
    // fprintf(stdout, "\n");
    // fprintf(stdout, "line: \n");
    // for (int i = 0; line[i] != '\0'; i++) {
    //     fprintf(stdout, "%c", line[i]);
    // }
    // fprintf(stdout, "\n");

    while (idx_line < line_length) {
        if (line[idx_line] == all_values.pattern[idx_pattern]) {
            idx_line++;
            idx_pattern++;
        }

        if (idx_pattern == all_values.pattern_len) {
            // fprintf(stdout, "there is the word at idx: %d\n", idx_line - idx_pattern);
            print_line(line);
            return 0;
            // fprintf(stdout, "idx_pat %d, lps pat %d\n", idx_pattern, all_values.lps[idx_pattern - 1]);
            // idx_pattern = all_values.lps[idx_pattern - 1];
        }

        else if(idx_line < line_length && line[idx_line] != all_values.pattern[idx_pattern]) {
            if (idx_pattern != 0) {
                idx_pattern = all_values.lps[idx_pattern - 1];
            }
            else {
                idx_line++;
            }
        }
    }

    return 1;
}

int get_file_size_and_save_text() {
    int return_value = 1;
    fseek(all_values.file, 0, SEEK_END);
    all_values.file_length = ftell(all_values.file);
    file_text_arr_alloc();
    rewind(all_values.file);

    fread(all_values.txt_arr, 1, all_values.file_length, all_values.file);
    all_values.txt_arr[all_values.file_length] = '\0';

    while (all_values.pattern[all_values.pattern_len] != '\0') {
        all_values.pattern_len++;
    }
    // fprintf(stdout, "PATTERN LENGTH %ld\n", all_values.pattern_len);
    lps_for_search();
    int last_line = -1;
    for (int idx = 0; all_values.txt_arr[idx] != '\0'; idx++) {
        
        if (all_values.txt_arr[idx] == '\n') {
            char line[idx - last_line];
            int idy = 0;
            while (all_values.txt_arr[(last_line + 1) + idy] != '\n') {
                
                line[idy] = all_values.txt_arr[(last_line + 1) + idy];
                idy++;
            }
            line[idy] = '\n';
            last_line = idx;
            if (kmp_search_in_line(line) == 0) {
                return_value = 0;
            }
        }

        if (all_values.txt_arr[idx + 1] == '\0') {
            char line[idx - last_line];
            int idy = 0;
            while (all_values.txt_arr[(last_line + 1) + idy] != '\0') {
                line[idy] = all_values.txt_arr[(last_line + 1) + idy];
                idy++;
            }
            line[idy] = '\n';
            if (kmp_search_in_line(line) == 0) {
                return_value = 0;
            }
            last_line = idx;
        }
    }

    return return_value;
}

int main (int argc, char *argv[]) {
    all_values.pattern_len = 0;
    input_test(argc, argv);

    open_file();
    // lps_for_search();

    // find_pattern_in_file();
    
    // KMP();
    int return_value = 0;
    if (get_file_size_and_save_text() == 0) {
        return_value = 0;
    }

    else {
        return_value = 1;
    }

    fclose(all_values.file);
    free(all_values.txt_arr);
    free(all_values.lps);

    //fprintf(stdout, "return: %d\n", return_value);

    return return_value;
}
