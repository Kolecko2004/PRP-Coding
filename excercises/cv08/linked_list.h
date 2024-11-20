// header file whichc can be inplemented as either queue or stack
#ifndef LINKED_LIST_H_GUARD
#define LINKED_LIST_H_GUARD

struct linked_node {
    struct linked_node * next = NULL;
    struct linked_node * prev = NULL;
    void * payload = NULL;
}

struct linked_list {
    struct linked_node * next = NULL;
    struct linked_node * prev = NULL;
    size_t size;
}

struct linked_list * linked_list__create ();
void linked_list__destory (struct linked_list * self);
void linked_list__push (struct linked_list * self, void * payload);
void * linked_list__pop (struct linked_list * self, int * err_code);
void * linked_list__peek (struct linked_list * self);
void linked_list__print (struct linked_list * self);

#endif