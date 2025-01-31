#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define INICIAL_LENGTH 20

struct all_values {
    char * pattern ;
    long pattern_len;

    FILE * file;
    char * file_name;
    long file_length;
    char * txt_arr;

    int * longest_pattern_prefix;
} all_values;

struct special_sign {
    int index;
    char type;
    int exist;
} special_sign;

struct all_values all_values;
struct special_sign special_sign;

int text_arr_alloc() {
    all_values.txt_arr = malloc(all_values.file_length + 1);
    if (all_values.txt_arr == NULL) {
        fprintf(stderr, "Allocation of memory was unsuccessful!\n");
        return 100;
    }

    return 0;
}

void load_n_save_text() {
    fread(all_values.txt_arr, 1, all_values.file_length, all_values.file);
    all_values.txt_arr[all_values.file_length] = '\0';
}

void get_file_n_pattern_size() {
    fseek(all_values.file, 0, SEEK_END);
    all_values.file_length = ftell(all_values.file);
    text_arr_alloc();
    rewind(all_values.file);
    
    while (all_values.pattern[all_values.pattern_len] != '\0') {
        all_values.pattern_len++;
    }

    load_n_save_text();
}

void open_file() {
    all_values.file = fopen(all_values.file_name, "r");
    if (all_values.file == NULL) {
        fprintf(stderr, "Opening the file was unsucesfull\n");
        exit(100);
    }

    get_file_n_pattern_size();
}

<<<<<<< Updated upstream
void memory_increase(struct all_values *prt) {
    prt->txt_arr = realloc(prt->txt_arr, prt->file_length * 2 * sizeof(char));
    if (prt->txt_arr == NULL) {
        fprintf(stderr, "Reallocation of memory was unsuccessful!\n");
        exit(1);
    }
    prt->file_length *= 2;
}

void read_from_stdin() {
    int scan_result = 0, idx = 0;
    char sign;

    all_values.txt_arr = malloc(INICIAL_LENGTH);
    if (all_values.txt_arr == NULL) {
        fprintf(stderr, "Allocation of memory was unsuccessful!\n");
    }
    all_values.file_length = INICIAL_LENGTH;

    while (scan_result != -1) {
        if (idx >= all_values.file_length) {
            memory_increase(&all_values);
        }
        scan_result = fscanf(stdin, "%c", &sign);
        all_values.txt_arr[idx] = sign;
        idx++;
    }

    all_values.txt_arr[idx] = '\0';
    all_values.file_length = idx;

    while (all_values.pattern[all_values.pattern_len] != '\0') {
        all_values.pattern_len++;
    }
}

void input_test(int num_of_arguments, char ** arguments) {
    if (num_of_arguments != 3 && num_of_arguments != 2 && num_of_arguments != 4) {
        printf("Expected 3 arguments, instead program got more or less than that\n");
        exit(100);
    }

    if (num_of_arguments == 3 || num_of_arguments == 2) {
        all_values.pattern = arguments[1];
    }

    else if (num_of_arguments == 4) {
        all_values.pattern = arguments[2];
        all_values.file_name = arguments[3];
        open_file();
    }
    

    if (num_of_arguments == 3) {
        all_values.file_name = arguments[2];
        open_file();
    }

    else if (num_of_arguments == 2)
    {
        read_from_stdin();
    }
}

=======
>>>>>>> Stashed changes
void longest_pattern_prefix_for_search() {
    int length = 0, idx = 1;
    all_values.longest_pattern_prefix = malloc(all_values.pattern_len * sizeof(int));
    if (all_values.longest_pattern_prefix == NULL) {
        fprintf(stderr, "Allocation of memory was unsuccessful!\n");
<<<<<<< Updated upstream
        exit(100);
    }
    all_values.longest_pattern_prefix[0] = 0;

    for (int i = 0; i < all_values.pattern_len; i++) {
        if (all_values.pattern[i] == '*' || all_values.pattern[i] == '+' || all_values.pattern[i] == '?') {
            special_sign.index = i;
            special_sign.type = all_values.pattern[i];
            special_sign.exist = 1;
        }
    }
=======
        return 100;
    }
    all_values.longest_pattern_prefix[0] = 0;
>>>>>>> Stashed changes

    while (idx < all_values.pattern_len) {
        if (all_values.pattern[idx] == all_values.pattern[length]) {
            length++;
            all_values.longest_pattern_prefix[idx] = length;
            idx++;
        }
        
        else {
            if (length != 0) {
                length = all_values.longest_pattern_prefix[length - 1];
            }

            else {
                all_values.longest_pattern_prefix[idx] = 0;
                idx++;
            }
        }
    }
}

<<<<<<< Updated upstream
void print_line_w_pattern(char * line) {
=======
void print_pattern_line(char * line) {
>>>>>>> Stashed changes
    for (int i = 0; line[i] != '\n'; i++) {
        fprintf(stdout, "%c", line[i]);
    }
    fprintf(stdout, "\n");
}

int get_line_length(char *line) {
    int line_length = 0;
    while(line[line_length] != '\n') {
        line_length++;
    }

    return line_length;
}

int kmp_search_in_line(char *line) {
    int line_length = get_line_length(line), idx_line = 0, idx_pattern = 0;

<<<<<<< Updated upstream
    while (idx_line < line_length) { 
=======
    while (idx_line < line_length) {
>>>>>>> Stashed changes
        if (line[idx_line] == all_values.pattern[idx_pattern]) {
            idx_line++;
            idx_pattern++;
        }

        if ((all_values.pattern[idx_pattern] == special_sign.type || idx_line == special_sign.index - 1) && special_sign.exist == 1) {
            if (special_sign.type == '*') {
                char repeat_char = all_values.pattern[idx_pattern - 1];
                while (idx_line < line_length && line[idx_line] == repeat_char) {
                    idx_line++;
                }
                idx_pattern++;
                continue;
            }

            else if (special_sign.type == '?') {
                char optional_char = all_values.pattern[idx_pattern - 1];

                if (idx_line < line_length && line[idx_line] == optional_char) {
                    idx_line++;
                }

                idx_pattern++;
                continue;
            }

            else if (special_sign.type == '+') {
                char repeat_char = all_values.pattern[idx_pattern - 1];
                
                if (line[idx_line - 1] != repeat_char) {
                    while (idx_line < line_length && line[idx_line] != repeat_char) {
                        idx_line++;
                    }
                }

                while (idx_line < line_length && line[idx_line] == repeat_char) {
                    idx_line++;
                }

                idx_pattern++;
                continue;
            }
        }

        if (idx_pattern == all_values.pattern_len) {
<<<<<<< Updated upstream
            print_line_w_pattern(line);
=======
            print_pattern_line(line);
>>>>>>> Stashed changes
            return 0;
        }

        else if(idx_line < line_length && line[idx_line] != all_values.pattern[idx_pattern]) {

            if (idx_pattern != 0) {
                idx_pattern = all_values.longest_pattern_prefix[idx_pattern - 1];
            }

            else {
                idx_line++;
            }
        }
    }

    return 1;
}

<<<<<<< Updated upstream
=======
void get_file_n_pattern_size() {
    fseek(all_values.file, 0, SEEK_END);
    all_values.file_length = ftell(all_values.file);
    text_arr_alloc();
    rewind(all_values.file);
    
    while (all_values.pattern[all_values.pattern_len] != '\0') {
        all_values.pattern_len++;
    }
}

void load_n_save_text() {
    fread(all_values.txt_arr, 1, all_values.file_length, all_values.file);
    all_values.txt_arr[all_values.file_length] = '\0';
}

>>>>>>> Stashed changes
int search_for_pattern() {
    int return_value = 1, last_line = -1;

    for (int idx = 0; all_values.txt_arr[idx] != '\0'; idx++) {
        
        if (all_values.txt_arr[idx] == '\n' || all_values.txt_arr[idx + 1] == '\0') {
            char line[idx - last_line];
            int idy = 0;

            while (all_values.txt_arr[last_line + 1 + idy] != '\n' && all_values.txt_arr[last_line + 1 + idy] != '\0') {
                line[idy] = all_values.txt_arr[last_line + 1 + idy];
                idy++;
            }

            line[idy] = '\n';
            last_line = idx;

            if (kmp_search_in_line(line) == 0) {
                return_value = 0;
            }
        }
    }

    return return_value;
}

<<<<<<< Updated upstream
void close_program(int num_of_arguments) {
    if (num_of_arguments == 3) {
        fclose(all_values.file);
    }
=======
void close_program() {
    fclose(all_values.file);
>>>>>>> Stashed changes
    free(all_values.txt_arr);
    free(all_values.longest_pattern_prefix);
}

int main (int argc, char *argv[]) {
    all_values.pattern_len = 0;
    input_test(argc, argv);
<<<<<<< Updated upstream
    
    longest_pattern_prefix_for_search();

    int return_value = search_for_pattern();

    close_program(argc);
=======

    open_file();

    get_file_n_pattern_size();

    load_n_save_text();
    
    longest_pattern_prefix_for_search();

    int return_value = search_for_pattern();

    close_program();
>>>>>>> Stashed changes

    return return_value;
}
