// Dynamická alokace paměti

// Casti pameti jsou: Heap, Stack, Global
// na Stack ulozime kdyz inicializujeme promenne
// Na Stacku je automatick7 managment pameti, kdyz neco nepouzivame tak se to smaze, kdyz skonci metoda tak se promenne z metody smazou atd...

// na HEAP ukladame kdyz nechceme aby se data n2kdy smazala
// Malloc uklada prave na HEAP a vraci misto kde byla data ulozena jako hodnotu
// Dale je Calloc - malloc ale vsechna oamet se inicializuje na 0
// Realloc - Zvetsi jeste pamet pro uz udelany calloc nebo malloc argumenty(co chceme realokovat, a na jakou hodnotu ho chceme realokovat)
// Vsechny pameti uklizet HEAP pomoci Free 
// Valgrim program mi rekne jake delam chyby v alokovani dynamicke pameti
#include <stdlib.h>
#include <stdio.h>

#define INIT_MEMORY_SIZE 8

char * read_line() {
    // Prepare an initial buffer
    size_t memory_capacity = INIT_MEMORY_SIZE; // kapacita pameti
    size_t memory_used = 0; // Kolik z te kapacity jsem uz pouzil
    char* memory = malloc(INIT_MEMORY_SIZE); // Odkaz na heapu kde s kapacitou pracujeme
    printf("Got a memory chung %p of cap %lu \n", memory, memory_capacity);
    if (memory == NULL) {
        return NULL;
    }

    for (char c; (c = getchar()) != '\n';) {
        if (memory_used >= memory_capacity) {
            size_t memory_capacity *= 2;
            char * memory_new = realloc(memory, memory_capacity)
            if (memory_new == NULL) {
                memory[memory_used - 1] = '\0';
                return memory;
            }
            printf("Realloc needed \n", c, memory_capacity, memory_used);
            memory = memory_new;
        }

        memory [memory_used++] = c;
        printf("Loaded %c, cap %lu, Used %lu \n", c, memory_capacity, memory_used);
    }
}

char** loaded_line() {

}

int main () {
    char * the_line = read_line();
}