#include <stdlib.h>
#include <stdio.h>

void prime_num_generator1(int prime_num_arr[], int *prime_count) {
    int size = 1000000;
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
    int prime_num_arr[1000000];
    int prime_count = 0;

    prime_num_generator1(prime_num_arr, &prime_count);

    for (int i = 0; i < prime_count; i++) {
        printf("%d\n", prime_num_arr[i]);
    }
    printf("pocet prime: %d\n", prime_count);
    return 0;
}