#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"

BookList* get_example_list();
void test_list_contents();
int main() {
    test_list_contents();
    return 0;
}

void test_write_numbers() {
    int a = 21;
    // int b = 2;
    // int c[] = {3, 4, 5};

    FILE * fp = fopen("demo_numbers", "w");
    if (fp == NULL) {
        fprintf(stderr, "fopen Failed\n");
        return;
    }

    // fprintf(fp, "%d", a);
    fwrite(&a, sizeof(a), 1, fp);

    fclose(fp);
}

BookList* get_example_list() {
    BookList* pl = create_book_list();
    Book* p1 = create_book(2005, "Programming in C", "Programming in C will teach you how to write programs in the C programming language.");
    Book* p2 = create_book(161, "Meditations", NULL);
    Book* p3 = create_book(-1500, "Poor Man of Nipur", "");
    add_book(pl, p1);
    add_book(pl, p2);
    add_book(pl, p3);

    test_write_numbers();
    return pl;
}

void test_list_contents() {
    BookList* pl = get_example_list();
    print_book_list(pl);
    destroy_book_list(pl);
}