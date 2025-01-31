#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 101
#define SITO_SIZE 1000000

int generate_prime_nuimbers(int primes[]) {
    char *sito = (char *)calloc(SITO_SIZE + 1, sizeof(char));
    int prime_count = 0;
    
    for (int i = 2; i <= SITO_SIZE; i++) {
        sito[i] = 1;
    }
    
    for (int i = 2; i * i <= SITO_SIZE; i++) {
        if (sito[i]) {
            for (int j = i * i; j <= SITO_SIZE; j += i) {
                sito[j] = 0;
            }
        }
    }
    
    for (int i = 2; i <= SITO_SIZE; i++) {
        if (sito[i]) {
            primes[prime_count++] = i;
        }
    }
    
    free(sito);
    return prime_count;
}

int is_divisible(const char *num, int prime) {
    int rest = 0;
    for (int i = 0; num[i] != '\0'; i++) {
        rest = (rest * 10 + (num[i] - '0')) % prime;
    }
    return rest == 0;
}

void divide_by_prime(char *num, int prime) {
    char result[MAX_DIGITS] = {0};
    int carry = 0;
    int jdx = 0;
    int leading_zeros = 1;
    
    for (int idx = 0; num[idx] != '\0'; idx++) {
        int current = carry * 10 + (num[idx] - '0');
        int digit = current / prime;
        carry = current % prime;
        
        if (digit != 0 || !leading_zeros) {
            result[jdx++] = digit + '0';
            leading_zeros = 0;
        }
    }
    
    if (jdx == 0) {
        result[jdx++] = '0';
    }
    result[jdx] = '\0';
    
    strcpy(num, result);
}

int is_one(const char *num) {
    return (num[0] == '1' && num[1] == '\0');
}

void process_number(char *number, int primes[], int prime_count) {
    char working_number[MAX_DIGITS];
    
    fprintf(stdout, "Prvociselny rozklad cisla %s je:\n", number);
    
    if (is_one(number)) {
        fprintf(stdout, "1\n");
        return;
    }
    
    strcpy(working_number, number);
    
    int first_factor = 1;
    for (int i = 0; i < prime_count && !is_one(working_number); i++) {
        int count = 0;
        while (is_divisible(working_number, primes[i])) {
            divide_by_prime(working_number, primes[i]);
            count++;
        }
        
        if (count > 0) {
            if (!first_factor) {
                fprintf(stdout, " × ");
            }
            if (count > 1) {
                fprintf(stdout, "%d^%d", primes[i], count);
            } else {
                fprintf(stdout, "%d", primes[i]);
            }
            first_factor = 0;
        }
    }
    
    if (!is_one(working_number)) {
        if (!first_factor) {
            fprintf(stdout, " × ");
        }
        fprintf(stdout, "%s", working_number);
    }
    
    fprintf(stdout, "\n");
}

int main() {
    char number[MAX_DIGITS];
    int primes[SITO_SIZE];
    int prime_count;
    
    prime_count = generate_prime_nuimbers(primes);
    
    while (1) {
        if (fgets(number, MAX_DIGITS, stdin) == NULL) {
            return 0;
        }
        
        int len = strlen(number);
        if (number[len-1] == '\n') {
            number[len-1] = '\0';
            len--;
        }
        
        for (int i = 0; i < len; i++) {
            if (number[i] < '0' || number[i] > '9') {
                fprintf(stderr, "Error: Chybny vstup!\n");
                exit(100);
            }
        }
        
        if (len == 1 && number[0] == '0') {
            break;
        }
        
        process_number(number, primes, prime_count);
    }
    
    return 0;
}