#ifndef __BOOK_H__
#define __BOOK_H__
 
#include <stdio.h>
 
#define MAX_NAME_SIZE 19
 
struct Book {
    int year;
    char title[MAX_NAME_SIZE];
    char* abstract;
};
typedef struct Book Book;
 
 
struct BookList {
    Book** books;
    size_t size;
};
typedef struct BookList BookList;
 
Book* create_book(int year, const char* title, const char* abstract);
void destroy_book(Book* b);
void print_book(Book* b);
 
BookList* create_book_list();
void destroy_book_list(BookList* bl);
void add_book(BookList* bl, Book* b);
void print_book_list(BookList* bl);
 
 
#endif