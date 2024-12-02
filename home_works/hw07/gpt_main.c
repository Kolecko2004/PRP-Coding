#include <stdlib.h>
#include <stdio.h>

struct all_values {
    char *pattern;
    char *file_name;
    FILE *file;
    long file_length;
    char *txt_arr;
} all_values;

struct all_values all_values;

int file_text_arr_alloc() {
    all_values.txt_arr = malloc(all_values.file_length + 1);
    if (all_values.txt_arr == NULL) {
        fprintf(stderr, "Allocation of memory was unsuccessful!\n");
        return 100;
    }
    return 0; // Return 0 on success
}

int input_test(int num_of_arguments, char **arguments) {
    if (num_of_arguments != 3) {
        printf("Expected 3 arguments, instead program got more or less than that\n");
        return 100;
    }

    all_values.pattern = arguments[1];
    all_values.file_name = arguments[2];
    return 0; // Return 0 on success
}

void open_file() {
    printf("PATTERN: %s\n", all_values.pattern);
    printf("FILE: %s\n", all_values.file_name);

    all_values.file = fopen(all_values.file_name, "r");
    if (all_values.file == NULL) {
        perror("Error opening file");
        exit(1);
    }
}

void get_file_size_and_save_text() {
    fseek(all_values.file, 0, SEEK_END);
    all_values.file_length = ftell(all_values.file);
    file_text_arr_alloc();
    rewind(all_values.file);

    fread(all_values.txt_arr, 1, all_values.file_length, all_values.file);
    all_values.txt_arr[all_values.file_length] = '\0'; // Null-terminate the string
}

// Compute the LPS (Longest Prefix Suffix) array
void compute_lps(const char *pattern, int *lps, int m) {
    int length = 0; // Length of previous longest prefix suffix
    lps[0] = 0; // First element is always 0
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search for pattern in a line
int kmp_search(const char *line, const char *pattern) {
    int n = 0, m = 0;
    while (line[n] != '\0') n++; // Calculate line length
    while (pattern[m] != '\0') m++; // Calculate pattern length

    int lps[m];
    compute_lps(pattern, lps, m);

    int i = 0; // Index for line
    int j = 0; // Index for pattern

    while (i < n) {
        if (line[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            return 1; // Pattern found
        } else if (i < n && line[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return 0; // Pattern not found
}

// Parse lines and use KMP to search for the pattern
void find_pattern_in_file() {
    int i = 0, line_start = 0;

    while (all_values.txt_arr[i] != '\0') {
        if (all_values.txt_arr[i] == '\n' || all_values.txt_arr[i + 1] == '\0') {
            // Identify the end of the current line
            int line_end = (all_values.txt_arr[i] == '\n') ? i : i + 1;

            // Extract the line
            char line[1024]; // Buffer for the line
            int k = 0;
            for (int j = line_start; j < line_end; j++) {
                line[k++] = all_values.txt_arr[j];
            }
            line[k] = '\0'; // Null-terminate the extracted line

            // Check if pattern exists in the current line using KMP
            if (kmp_search(line, all_values.pattern)) {
                printf("Line containing pattern: %s\n", line);
            }

            // Move to the next line
            line_start = i + 1;
        }
        i++;
    }
}

int main(int argc, char *argv[]) {
    if (input_test(argc, argv) != 0) {
        return 100;
    }

    open_file();

    get_file_size_and_save_text();

    find_pattern_in_file();

    fclose(all_values.file);
    free(all_values.txt_arr);

    return 0;
}
