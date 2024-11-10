// Prvociselny Rozklad
#include <stdlib.h>
#include <stdio.h>
#define SIZE 1000000

int get_divider(int index, int prime_num_arr[]) {
    int prime = 0;
    int i = 2;

    while (index != 0) {
        if (prime_num_arr[i] == 1) {
            index--;
            prime = i;
        }
        i++;
    }

    return prime;
}

void input_test(int scan_result, long loaded_num) {
    if (scan_result == 0 || loaded_num < 0) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }
}

int division(long *loaded_num, int divider) {
    int div_count = 0;

    while (*loaded_num % divider == 0) {
        div_count++;
        *loaded_num /= divider;
    }

    return div_count;
}

void printing_numbers(int div_count, int * num_divisor, int divider) {
    if (div_count > 0) {
        (* num_divisor)++;
        * num_divisor > 1 ? fprintf(stdout, " x ") : * num_divisor;
        fprintf(stdout, "%d", divider);
        div_count > 1 ?  fprintf(stdout, "^%d", div_count) : div_count;
    }
}

void prime_num_generator(int prime_num_arr[]) {
    int arr_size = SIZE;
    int all_num[arr_size + 1];
    

    for (int number = 2; number <= arr_size; number++) {
        all_num[number] = 1;
    }

    for (int devider = 2; devider * devider <= arr_size; devider++) {
        if (all_num[devider] == 1) {
            for (int i = devider * devider; i <= arr_size; i += devider) {
                all_num[i] = 0;
            }
        }
    }
    
    int index = 0;
    for (int i = 2; i <= arr_size; i++) {
        if (all_num[i] == 1) {
            prime_num_arr[index] = i;
            (index)++;
        }
    }
}

int main() {
    int prime_num_arr[SIZE];
    prime_num_generator(prime_num_arr);

    int scan_result = 0, div_count, bigIndex = 0;
    long original_num = -1;

    while (1) {
        bigIndex = 0;
        int num_divisor = 0;

        scan_result = fscanf(stdin, "%ld", &original_num);
        if (original_num == 0) {
            break;
        }
        input_test(scan_result, original_num);
    
        long num_for_math = original_num;

        if (original_num == 1) {
            fprintf(stdout, "Prvociselny rozklad cisla %ld je:\n", original_num);
            fprintf(stdout, "1");
        }

        else {
            fprintf(stdout, "Prvociselny rozklad cisla %ld je:\n", original_num);

            while (num_for_math != 1) {
                div_count = division(&num_for_math, prime_num_arr[bigIndex]);

                printing_numbers(div_count, &num_divisor, prime_num_arr[bigIndex]);

                bigIndex++;
            }
        }
        fprintf(stdout, "\n");
    }
    
    return 0;
}
