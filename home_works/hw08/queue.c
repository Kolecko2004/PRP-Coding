#ifndef __QUEUE_H__
#define __QUEUE_H__
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
 
/* Queue structure which holds all necessary data */
typedef struct {
   int head_idx;
   int tail_idx;
   int capacity;
   int num_of_stored_elements;
   int * queue;
} queue_t;
 
/* creates a new queue with a given size */
queue_t* create_queue(int capacity) {
    queue_t * queue = malloc(sizeof(queue_t));
    queue->queue = malloc(capacity * sizeof(int));

    if(queue == NULL) {
        fprintf(stderr, "Allocation of memory was unsuccesful\n");
        exit(1);
    }

    else {
        memset(queue->queue, -1, capacity * sizeof(int));
    }

    queue->head_idx = 0;
    queue->tail_idx = 0;
    queue->capacity = capacity;
    queue->num_of_stored_elements = 0;
    
    fprintf(stdout, "Before program result\n");
    for (int i = 0; i < queue->capacity; i++) {
        fprintf(stdout, "num:%d at idx: %d\n", queue->queue[queue->head_idx + i], queue->head_idx + i);
    }
    fprintf(stdout, "----------------\n");

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
bool push_to_queue(queue_t *queue, void *data) {
    fprintf(stdout, "Push: ");
    int * int_data = data;
    // fprintf(stdout, "stored: %d, idx: %d, capacity: %d\n",queue->num_of_stored_elements, queue->tail_idx, queue->capacity);
    if (queue->num_of_stored_elements < queue->capacity) {
        queue->queue[queue->tail_idx] = *int_data;
        // fprintf(stdout, "1 - data: %d at idx: %d\n",  queue->queue[queue->tail_idx], queue->tail_idx);
        queue->num_of_stored_elements += 1;
        queue->tail_idx += 1;

        // fprintf(stdout, "2 - data: %d at idx: %d\n",  queue->queue[queue->tail_idx], queue->tail_idx);

        return (true);
    }

    else {
        fprintf(stdout, "idk\n");
        return (false);
    }
}
 
/* 
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue) {
    fprintf(stdout, "Pop: ");
    void * poped_value = &queue->queue[queue->head_idx];
    // fprintf(stdout, "poped value%d\n", *(int*)poped_value);
    if (queue->head_idx >= queue->capacity - 1) {
        queue->head_idx = queue->head_idx % queue->capacity;
    }

    if (queue->queue[queue->head_idx] != -1) {
        fprintf(stdout, "%d\n", *(int*)poped_value);
        // fprintf(stdout, "BEF Removed: %d at idx: %d\n",  queue->queue[queue->head_idx], queue->head_idx);
        queue->queue[queue->head_idx] = -1;
        // fprintf(stdout, "AFT Removed: %d at idx: %d\n",  queue->queue[queue->head_idx], queue->head_idx);
        queue->num_of_stored_elements -= 1;
        queue->head_idx += 1;

        // fprintf(stdout, "Data of HEAD: %d at idx: %d\n", queue->queue[queue->head_idx], queue->head_idx);
        
    }

    else {
        fprintf(stdout, "NULL\n");
    }


    
    return poped_value;
}
 
/* 
 * gets idx-th element from the queue
 * returns the element that would be popped after idx calls of the pop_from_queue() 
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx) {
    if (idx >= queue->capacity) {
        idx = idx % queue->capacity;
    }

    else if (idx < 0) {
        idx = idx
    }
    fprintf(stdout, "Get value: ");
    void * idx_th_element = &queue->queue[idx];
    fprintf(stdout, "Got: %d on idx: %d\n", *(int *)idx_th_element, idx);
    if (idx_th_element == NULL || *(int*)idx_th_element == -1) {
        fprintf(stdout, "NULL\n");
        return NULL;
    }

    else {
        fprintf(stdout, "%d\n", *(int *)idx_th_element);
    }

    return idx_th_element;
}
 
/* gets number of stored elements */
// int get_queue_size(queue_t *queue);
 
int get_input() {
    int capacity = 0;
    fscanf(stdin, "%d", &capacity);
    return capacity;
}

void performing_commands(queue_t *queue, char command, int data) {
    if (command == 'a') {
        push_to_queue(queue, &data);
    }

    else if(command == 'g') {
        get_from_queue(queue, data);
    }

    else if (command == 'r') {
        pop_from_queue(queue);
    }

    else {
        fprintf(stdout, "I dont know this char command try 'a', 'g', or 'r'\n");
        exit(100);
    }
}

void input_command(queue_t *queue) {
    int scan_result = 0;
    int idx = 0; // erase before odevzdani ukolu

    while (scan_result != EOF) {
        char command;
        int data;
        scan_result = fscanf(stdin, " %c %d", &command, &data);

        if (scan_result == EOF) {
            break;
        }

        if (command != 'r' && scan_result != 2) {
            fprintf(stdout, "Input command has wrong structure\n");
            break;
        }

        if (command == 'r' && scan_result != 1) {
            fprintf(stdout, "Input command has wrong structure\n");
            break;
        }

        // fprintf(stdout, "%c = %d, idx %d\n", command, data, idx);
        
        performing_commands(queue, command, data);

        idx++;
    }
}

#endif /* __QUEUE_H__ */

int main () {
    queue_t * queue = create_queue(get_input());

    // fprintf(stdout, "Stored elemets: %d\n", queue->num_of_stored_elements);
    input_command(queue);


    fprintf(stdout, "----------------\n");
    fprintf(stdout, "After program result\n");
    for (int i = 0; i < queue->num_of_stored_elements; i++) {
        fprintf(stdout, "num:%d at idx: %d\n", queue->queue[queue->head_idx + i], queue->head_idx + i);
    }
    
    free(queue);

    return 0;
}
