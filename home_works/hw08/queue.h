#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>

typedef struct {
    int head_idx;
    int tail_idx;
    int capacity;
    int num_of_stored_elements;
    void **queue;
} queue_t;

/* Function prototypes */
queue_t* create_queue(int capacity);
void delete_queue(queue_t *queue);
bool push_to_queue(queue_t *queue, void *data);
void* pop_from_queue(queue_t *queue);
void* get_from_queue(queue_t *queue, int idx);
int get_queue_size(queue_t *queue);

#endif /* __QUEUE_H__ */
