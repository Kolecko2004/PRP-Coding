// co je to zasobnik
// LIFO
// FIFO

#include <stdio.h>
#include <stdlib.h>
#include "linkde_list.h"

int main() {
    struct linked_list * my_list = linked_list__create();
    linked_list__push(my_list, 0x01);
    linked_list__push(my_list, 0x02);
    linked_list__push(my_list, 0x03);

    ljnked_list__print(my_list);

    linked_list__pop();
    linked_list__pop();
    linked_list__pop();
    linked_list__pop();

    return 0;
}