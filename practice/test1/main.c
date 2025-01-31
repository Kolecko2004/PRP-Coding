#include <stdio.h>

int main(void) {
    const int num = 10;
    const int *p = &num;

    printf("a: %d, *p: %d\n", num, *p);
    // *p = 14;

    printf("a: %d, *p: %d\n", num, *p);
    return 0;
}