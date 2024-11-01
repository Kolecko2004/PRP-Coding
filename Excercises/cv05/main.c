#include <stdio.h>

// static je promenna ulozena mimo stack a ani neni ulozena na HEAP (Halda) neboli je ulozena mimo oboje a nesmaze se
// const je neco jineho 

// Pole: spojity blok pameti kde je to interpretovane jako seznam polozek stejneho typu
// pole nekde zacina a my pole identifikujeme adresou prvniho prvku
// i-ty prvek je ZACATEK POLE + I * POCET BYTU (int)

// pointer ma 8 bytu aby se vesla adresa
int main() {
    int array[] = {5, -6, 0, 8, -9, 3, 1, -4};
    int *up  = array;
    int **uup = &up;

    printf("array[1] = %d \n", array[1]);
    printf("array[1] + 4 = %d \n", array[1] + 4);
    printf("(array + 1)[2] = %d \n", (array + 1)[2]);

    printf("*up = %d \n", *up);
    printf("*up + 4 = %d \n", *up + 4);
    printf("*(up + 1) = %d \n", *(up + 1));

    printf("**uup = %2d \n", **uup);
    printf("*(*uup + 2) = %2d \n", *(*uup + 2));
    printf("**uup + 4 = %2d \n", **uup + 4);
}

// textovy retezec je pole znaku ktere konci 0
// Funkce str()
// Prolezt cviceni 5
// Pole variabilni delky / int i = 10