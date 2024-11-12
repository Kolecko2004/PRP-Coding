// soubor je mnozstvi jednicek a nul ktere maji urcitou 
// fflush pro ulozeni z bufferu primo na disk

// readline
// readlines
// permute
// struct

#include <stdio.h>

int main () {
    char * filename = "text.txt";
    FILE * fp = fopen(filename, "r");

    char * c;
    readline(filename, * c);
    putchar(* c);
    putchar('\n');

    return 0;
}