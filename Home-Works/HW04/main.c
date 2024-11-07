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

void input_test(int scan_res, int loaded_num) {
    if (scan_res == 0 || loaded_num < 0) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }
}

int rozklad(int *loaded_num, int divide) {
    int div_count = 0;

    while (*loaded_num % divide == 0) {
        div_count++;
        *loaded_num /= divide;
    }

    return div_count;
}

void printing_numbers(int * div_count, int * index, int * num_divisor, int * divider) {

    if (* div_count > 0) {
        (* num_divisor)++;
        * num_divisor > 1 ? fprintf(stdout, " x ") : * index;
        fprintf(stdout, "%d", * divider);
        * div_count > 1 ?  fprintf(stdout, "^%d", * div_count) : * div_count;
    }
}

void prime_num_generator(int prime_num_arr[], int *prime_count) {
    int size = SIZE;
    int all_num[size + 1];
    *prime_count = 0;

    for (int number = 2; number <= size; number++) {
        all_num[number] = 1;
    }

    for (int devider = 2; devider * devider <= size; devider++) {
        if (all_num[devider] == 1) {
            for (int i = devider * devider; i <= size; i += devider) {
                all_num[i] = 0;
            }
        }
    }

    for (int i = 2; i <= size; i++) {
        if (all_num[i] == 1) {
            prime_num_arr[*prime_count] = i;
            (*prime_count)++;
        }
    }
}

int main() {
    int prime_num_arr[SIZE];
    int prime_count = 0;

    prime_num_generator(prime_num_arr, &prime_count);
    int scan_result = 0, original_num = -1, divider = 2, div_count, bigIndex = 0;

    while (1) {
        int num_divisor = 0;
        scan_result = fscanf(stdin, "%d", &original_num);

        if (original_num == 0) {
            break;
        }

        input_test(scan_result, original_num);
    
        int num_for_math = original_num;

        if (original_num == 1) {
            fprintf(stdout, "Prvociselny rozklad cisla %d je:\n", original_num);
            fprintf(stdout, "1");
        }

        else {
            fprintf(stdout, "Prvociselny rozklad cisla %d je:\n", original_num);

            while (num_for_math != 1) {
                divider = prime_num_arr[bigIndex];
                div_count = rozklad(&num_for_math, divider);

                printing_numbers(&div_count, &bigIndex, &num_divisor, &divider);

                bigIndex++;
            }
        }
        fprintf(stdout, "\n");
        divider = 2;
        bigIndex = 0;
    }
    
    return 0;
}
