#ifndef __QUEUE_H__
#define __QUEUE_H__
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
/* Queue structure which holds all necessary data */
typedef struct {
   int head_idx;
   int tail_idx;
   int capacity;
   int num_of_stored_elements;
   int queue[];
} queue_t;
 
/* creates a new queue with a given size */
queue_t* create_queue(int capacity) {
    queue_t * queue = malloc(capacity * sizeof(int));
    if(queue == NULL) {
        fprintf(stderr, "Allocation of memory was unsuccesful\n");
        exit(1);
    }

    queue->head_idx = 0;
    queue->tail_idx = 0;
    queue->capacity = capacity;
    queue->num_of_stored_elements = 0;

    // for (int i = 0; i < queue->capacity; i++) {
    //     queue->queue[i] = i;
    //     fprintf(stdout, "%d\n", queue->queue[i]);
    // }

    return queue;
}
 
/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue);
 
/* 
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data);
 
/* 
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue);
 
/* 
 * gets idx-th element from the queue
 * returns the element that would be popped after idx calls of the pop_from_queue() 
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx);
 
/* gets number of stored elements */
// int get_queue_size(queue_t *queue);
 
int get_input() {
    int capacity = 0;
    fscanf(stdin, "%d", &capacity);
    return capacity;
}

void input_command() {
    char command;
    int data, scan_result = 0;

    while (1) {
        scan_result = fscanf(stdin, " %c %d\n", &command, &data);
        fprintf(stdout, "%c = %d", command, data);
        if (scan_result == EOF) {
            break;
        }
    }
}

#endif /* __QUEUE_H__ */

int main () {
    queue_t * queue = create_queue(get_input());
    for (int i = 0; i < queue->capacity; i++) {
        queue->queue[i] = i;
        queue->num_of_stored_elements += 1;
        fprintf(stdout, "%d\n", queue->queue[i]);
    }
    fprintf(stdout, "Stored elemets: %d\n", queue->num_of_stored_elements);
    input_command();

    return 0;
}
