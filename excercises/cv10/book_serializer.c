#include <serializer.h>

void serialize_book(FILE* f, Book* p) {
    
    fwrite(p, sizeof(*p), 1, f);    
}
// Book* deserialize_book(FILE* f);

// void serialize_book_list(FILE* f, BookList* pl);
// BookList* deserialize_book_list(FILE* f);