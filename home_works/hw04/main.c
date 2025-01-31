#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 1000000

void prime_num_generator(int prime_num_arr[], int *prime_count) {
    int size = SIZE;
    int *all_num = (int *)calloc(size + 1, sizeof(int));
    *prime_count = 0;

    for (int number = 2; number <= size; number++) {
        all_num[number] = 1;
    }

    for (int devider = 2; devider * devider <= size; devider++) {
        if (all_num[devider] == 1) {
            for (int idx = devider * devider; idx <= size; idx += devider) {
                all_num[idx] = 0;
            }
        }
    }

    for (int idx = 2; idx <= size; idx++) {
        if (all_num[idx] == 1) {
            prime_num_arr[*prime_count] = idx;
            (*prime_count)++;
        }
    }

    free(all_num);
}

int is_divisible(const char num[], int devider) {
    int remainder = 0;
    for (int idx = 0; num[idx] != '\0'; idx++) {
        int digit = num[idx] - '0';
        remainder = (remainder * 10 + digit) % devider;
    }
    return remainder == 0;
}

void devide_string(char num[], int divisor) {
    char result[101] = {0};
    int temp = 0;
    int result_idx = 0;
    int leading_zeros = 1;
    int size = strlen(num);

    for (int idx = 0; idx < size; idx++) {
        temp = temp * 10 + (num[idx] - '0');
        int digit = temp / divisor;
        
        if (digit != 0 || !leading_zeros) {
            result[result_idx++] = digit + '0';
            leading_zeros = 0;
        }
        temp %= divisor;
    }

    if (result_idx == 0) {
        result[result_idx++] = '0';
    }
    
    result[result_idx] = '\0';
    strcpy(num, result);
}

int is_one(const char *num) {
    return (num[0] == '1' && num[1] == '\0');
}

void process_number(char str_num[], int prime_num_arr[], int prime_count) {
    char str_num_math[101];
    strcpy(str_num_math, str_num);

    fprintf(stdout, "Prvociselny rozklad cisla %s je:\n", str_num);

    if (is_one(str_num_math)) {
        fprintf(stdout, "1\n");
        return;
    }

    int first_factor = 1;
    
    for (int idx = 0; idx < prime_count && !is_one(str_num_math); idx++) {
        int count = 0;
        while (is_divisible(str_num_math, prime_num_arr[idx])) {
            devide_string(str_num_math, prime_num_arr[idx]);
            count++;
        }
        
        if (count > 0) {
            if (!first_factor) {
                fprintf(stdout, " x ");
            }
            if (count > 1) {
                fprintf(stdout, "%d^%d", prime_num_arr[idx], count);
            } else {
                fprintf(stdout, "%d", prime_num_arr[idx]);
            }
            first_factor = 0;
        }
    }

    if (!is_one(str_num_math)) {
        if (!first_factor) {
            fprintf(stdout, " × ");
        }
        fprintf(stdout, "%s", str_num_math);
    }
    
    fprintf(stdout, "\n");
}

int main() {
    char str_num[101];
    int prime_num_arr[SIZE];
    int prime_count;
    
    prime_num_generator(prime_num_arr, &prime_count);

    while (1) {
        if (fgets(str_num, sizeof(str_num), stdin) == NULL) {
            return 0;
        }

        int len = strlen(str_num);
        if (str_num[len-1] == '\n') {
            str_num[len-1] = '\0';
            len--;
        }
        
        for (int i = 0; i < len; i++) {
            if (str_num[i] < '0' || str_num[i] > '9') {
                fprintf(stderr, "Error: Chybny vstup!\n");
                exit(100);
            }
        }

        if (len == 1 && str_num[0] == '0') {
            break;
        }

        process_number(str_num, prime_num_arr, prime_count);
    }

    return 0;
}
