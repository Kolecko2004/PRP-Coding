// Rekurzivni funkce je funkce ktera v sobe vola sama sebe
// Knihovny jsou nastroje pro dekompozici
// 

#include <stdio.h>
#include "fib.h"

int greet (int remaining_calls) {
    fprintf(stdout, "Hello world \n");
    if (remaining_calls > 1) {
        greet(remaining_calls - 1);
    }
}

// void revert(char str[], int num) {
//     if (num > -1) {
//         putchar(str[num]);
//         revert(str, num);
//     }
// }

// void str_len(char str, int * str_length) {
//     if (str[*str_length] != '\0') {
//         (*str_length)++;
//         str_len(str);
//     }
// }

int main () {
    int num = 0;
    //char str[];
    // int str_length = 0;

    fscanf(stdin, "%d", &num);
    greet(num);
    // fprintf(stdout, "%d", str_length);
    // int i = 0;

    // while (s != 0) {
    //     char s = getchar(str[i]);
    //     i++;
    // }

    // revert(str, i);
    int i = 20;

    printf("fib number : #%03d = %d\n", i, fib(i));
    
    
    return 0;
}