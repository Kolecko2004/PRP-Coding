#include <stdlib.h>
#include <stdio.h>
#define SIZE 1000000  // Limit the number of primes to reduce memory usage

void prime_num_generator(int prime_num_arr[]) {
    int size = SIZE;
    int all_num[size + 1];
    int prime_count = 0;

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
            prime_num_arr[prime_count] = i;
            prime_count++;
        }
    }
}

// Function to check if the character array is divisible by a given number
int is_divisible(char num[], int devider[], int index) {
    int remainder = 0;
    for (int i = 0; num[i] != '\0'; i++) {
        int digit = num[i] - '0';
        remainder = (remainder * 10 + digit) % devider[index];
    }
    return remainder;
}

// Function to divide the character array by the divisor
void devide_string(char num[], int divisor[], int size, int index) {
    int temp = 0;
    char result[101];
    int result_idx = 0;

    for (int i = 0; i < size; i++) {
        temp = temp * 10 + (num[i] - '0');
        if (temp < divisor[index] && result_idx == 0) continue;

        result[result_idx++] = (temp / divisor[index]) + '0';
        temp %= divisor[index];
    }

    result[result_idx] = '\0';
    for (int i = 0; i <= result_idx; i++) {
        num[i] = result[i];
    }
}

int main() {
    char str_num[101];
    char str_num_math[101];
    int size_of_arr = 0;
    int prime_num_arr[SIZE];
    prime_num_generator(prime_num_arr);

    // Read input from user
    printf("Enter a number: ");
    fgets(str_num, sizeof(str_num), stdin);

    while (str_num[size_of_arr] != '\0' && str_num[size_of_arr] != '\n') {
        size_of_arr++;
    }
    str_num[size_of_arr] = '\0';

    for (int i = 0; i < size_of_arr; i++) {
        str_num_math[i] = str_num[i];
    }
    str_num_math[size_of_arr] = '\0';

    int indexlol = 0;
    int devided_by[100];
    int bugindex = 0;

    // Printing the input number
    fprintf(stdout, "Prvociselny rozklad cisla ");
    size_of_arr = 0;
    while (str_num[size_of_arr] != '\0') {
        fprintf(stdout, "%d", str_num[size_of_arr] - '0');
        size_of_arr++;
    }
    fprintf(stdout, " je:\n");

    // Prime factorization
    int number_usage = 0;

    while (size_of_arr > 1 || (size_of_arr == 1 && str_num_math[0] != '1')) {
        int remainder = is_divisible(str_num_math, prime_num_arr, indexlol);

        if (remainder == 0) {
            devide_string(str_num_math, prime_num_arr, size_of_arr, indexlol);
            devided_by[bugindex] = prime_num_arr[indexlol];
            bugindex++;

            size_of_arr = 0;
            while (str_num_math[size_of_arr] != '\0') {
                size_of_arr++;
            }
            number_usage++;
        } else {
            
            if (number_usage > 1) {
                fprintf(stdout, "%d ^ %d", prime_num_arr[indexlol], number_usage);
            }

            else {
                fprintf(stdout, "%d", prime_num_arr[indexlol]);
            }

            number_usage = 0;
            indexlol++;
        }
    }

    return 0;
}
