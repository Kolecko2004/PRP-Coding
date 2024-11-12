#include <stdio.h>
// Array / Pole
// v C nemůžeme vyjít ven z pole a porušit jeho velikost
// Kdyz se daji prazdne zavorky {} tak se vse inicializuje na 0 -> int array[5] = {}
// 1D pole

void pointed(int * pointer){
    *pointer = 10;
}

int main(void) {
    int array[5]= { 1, 2, 3, 4, 5 };

    printf("Size of array %lu bytes\n", sizeof(array));
    for (int i = 0; i < 5; i++){
        printf("Item[%i] = %i\n", i, array[i]);
    }

    //for (int i = 0; i < 5; i++){
    //    printf("Item[%i] = %i\n", i, array[i]);
    //}
    int ahoj = 0;
    pointed(&ahoj);
    printf("ahoj je: %d\n", ahoj);

    return 0;
}


// Ukazatel / Pointer
// Hodnota pointeru je adresa pameti kterou chceme 
// promenna
// pointer
// 2D pole
// pole v C maji vrstvy
int (m[2])[3] = {{1, 2, 3}, {4, 5, 6}}; // 2x pole prvku 3.
// Textove retezce - jsou pole typu char
char str[] = "123"

