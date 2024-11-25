#include <stdlib.h>
#include "fib.h"

int fib (int i ) {
    if (i == 2 || i == 1) {
        return 1;
    }

    else {
        return fib(i - 1) + fib(i - 2);
    }
    
}