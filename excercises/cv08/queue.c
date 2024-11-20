struct linked_list * linked_list__create () {
    struct linked_list * ret = malloc (sizeof(struct linked_node));
    if (ret == NULL) {
        return NULL;
    }
    ret->head=NULL;
    ret->tail=NULL;
    ret->size=0;

    return ret
}

struct linked_list * linked_list__push () {
    struct linked_list * element = malloc (sizeof(struct linked_node));
    if (element == NULL) {
        return -1;
    }

    if (self ->tail != NULL) {
        self=>tail.next = element;
        element->prev = self->tail;
    }

    self->tail = element; 
    if (self->head == NULL) {
        self->head = element;
    }
    self->size++;

    return 0;
}


void * payload linked_list__pop (struct linked_list * self, int * ret) {
    if (self -> size == 0) {return -1;}


    struct linked_list * elem = self.head;
    void *ret = elem -> payload;
    
    free(elem);
    self->head->next.prev = NULL;
    self->head = self->head.next;

    if (element == NULL) {
        return -1;
    }

    if (self ->tail != NULL) {
        self=>tail.next = element;
        element->prev = self->tail;
    }

    self->tail = element; 
    if (self->head == NULL) {
        self->head = element;
    }
    self->size++;

    return 0;
}