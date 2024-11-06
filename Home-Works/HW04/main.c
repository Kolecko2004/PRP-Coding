// Prvociselny Rozklad
#include <stdlib.h>
#include <stdio.h>

void prime_num_generator(int size, int prime_num_arr[], int * arr_size, int * index) {
    if (size > * arr_size) {
        int all_num[size];
        for (int prime_num = * arr_size; prime_num <= size; prime_num++) {
            all_num[prime_num] = 1;
        }
    
        for (int j = * arr_size; j <= size; j++) {
            if (all_num[j] == 1) {
                for (int i = * arr_size; i < size; i++) {
                    if (i % j == 0 && i != j && all_num[i] == 1 ) {
                        (* index)++;
                        all_num[i] = 0;
                        prime_num_arr[* index] = i;
                    }
                }
            }
        }
        * arr_size < size ? * arr_size = size : size;
    }
    
}

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

int main() {
    int scan_result = 0, arr_size = 0, original_num = -1, divider = 2, div_count, bigIndex = 0;

    while (1) {
        int num_divisor = 0;
        scan_result = fscanf(stdin, "%d", &original_num);

        if (original_num == 0) {
            break;
        }

        input_test(scan_result, original_num);
    
        int num_for_math = original_num;
        int prime_arr[original_num];
        int index = 1;
        
        prime_num_generator(original_num, prime_arr, &arr_size, &bigIndex);

        if (original_num == 1) {
            fprintf(stdout, "Prvociselny rozklad cisla %d je:\n", original_num);
            fprintf(stdout, "1");
        }

        else {
            fprintf(stdout, "Prvociselny rozklad cisla %d je:\n", original_num);

            while (num_for_math != 1) {
                divider = prime_arr[index];
                div_count = rozklad(&num_for_math, divider);

                printing_numbers(&div_count, &index, &num_divisor, &divider);

                index++;
            }
        }
        fprintf(stdout, "\n");
        divider = 2;
    }
    
    return 0;
}
