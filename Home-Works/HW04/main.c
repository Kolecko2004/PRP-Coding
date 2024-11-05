// Prvociselny Rozklad
#include <stdlib.h>
#include <stdio.h>

int prvocisla(int size, int prime_num[]) {
    int prvocisla;
    for (prvocisla = 2; prvocisla <= size; prvocisla++) {
        prime_num[prvocisla] = 1;
    }
    for (prvocisla = 2; prvocisla <= size; prvocisla++) {
        if (prime_num[prvocisla] == 1) {
            for (int i = 2; i < size; i++) {
                if (i % prvocisla == 0 && i != prvocisla && prime_num[i] == 1 ) {
                    prime_num[i] = 0;
                }
            }
        }
    }
}

int get_divider(int index, int prime_num[]) {
    int the_number = 0; // vysledne prvocislo ktere se bude vracet
    int i = 2; // na prochazeni pole

    while (index != 0) {
        if (prime_num[i] == 1) {
            index--;
            the_number = i;
        }
        i++;
    }
    return the_number;
}


int input_test(int scan_res, int loaded_num) {
    if (scan_res == 0 || loaded_num < 0) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }
}

int rozklad(int *loaded_num, int divide) {
    int pocet = 0;
    while (*loaded_num % divide == 0) {
        pocet++;
        *loaded_num /= divide;
    }
    return pocet;
}

int load_numbers() {
    int load_result = 0;
    int number = -1;
    int divisor = 2;
    int num_of_divisor;


    while (number != 0) {
        int s = 0; // pocet cisel kteryma se deli
        load_result = fscanf(stdin, "%d", &number); // nacteme cislo na rozlozeni
        input_test(load_result, number); // otestujeme cislo v tesu
    
        int num_for_math = number; // zalozime promenou se kterou pocitame
        int prime_array[number]; // zalozime promenou kde budou ulozeny prvocisla
        prvocisla(number, prime_array); // najde prvocisla do limitu velikosti daneho cisla

        int index = 1; // vedet kolikatym prvocislem delime

        printf("Prvociselny rozklad cisla %d je: \n", number);

        while (num_for_math != 1) {
            divisor = get_divider(index, prime_array); // chceme ziskat prvocislo ktere pouzijeme na deleni
            num_of_divisor = rozklad(&num_for_math, divisor); // rozkladame cislo a vrac9me kolikrat jsme delili

            if (num_of_divisor > 0) {
                s++;
                s > 1 ? printf(" x ") : index;
                printf("%d", divisor);
                num_of_divisor > 1 ?  printf("^%d", num_of_divisor) : num_of_divisor;
            }

            index++;
        }
        printf("\n");
        divisor = 2;
    }
}

int main() {
    load_numbers();
}