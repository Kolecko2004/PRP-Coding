#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

queue_t* create_queue(int capacity) {
    queue_t *queue = malloc(sizeof(queue_t));
    if (!queue) {
        fprintf(stderr, "Allocation of memory was unsuccessful\n");
        exit(1);
    }

    queue->queue = malloc(capacity * sizeof(void*));
    if (!queue->queue) {
        fprintf(stderr, "Allocation of queue array was unsuccessful\n");
        free(queue);
        exit(1);
    }

    queue->head_idx = 0;
    queue->tail_idx = 0;
    queue->capacity = capacity;
    queue->num_of_stored_elements = 0;
    return queue;
}

void delete_queue(queue_t *queue) {
    if (queue) {
        free(queue->queue);
        free(queue);
    }
}

void queue_capacity_increase(queue_t *queue) {
    int new_capacity = queue->capacity * 2;
    
    void **new_queue = malloc(new_capacity * sizeof(void*));
    if (!new_queue) {
        fprintf(stdout, "Memory allocation failed here\n");
        exit(100);
    }

    for (int i = 0; i < queue->num_of_stored_elements; i++) {
        new_queue[i] = queue->queue[(queue->head_idx + i) % queue->capacity];
    }

    free(queue->queue);

    queue->queue = new_queue;
    queue->capacity = new_capacity;
    queue->head_idx = 0;
    queue->tail_idx = queue->num_of_stored_elements;
}

void queue_capacity_decrease(queue_t *queue) {
    int new_capacity = queue->capacity / 3;

    if (new_capacity < queue->num_of_stored_elements) {
        return;
    }

    void ** new_queue = malloc( new_capacity * sizeof(void *));
    if (!new_queue) {
        fprintf(stdout, "Memory allocation failed\n");
        exit(100);
    }

    for (int i = 0; i < queue->num_of_stored_elements; i++) {
        new_queue[i] = queue->queue[(queue->head_idx + i) % queue->capacity];
    }

    free(queue->queue);

    queue->queue = new_queue;
    queue->capacity = new_capacity;
    queue->head_idx = 0;
    queue->tail_idx = queue->num_of_stored_elements;
}


bool push_to_queue(queue_t *queue, void *data) {

    if (queue->num_of_stored_elements >= queue->capacity) {
        queue_capacity_increase(queue);
    }

    if (queue->num_of_stored_elements < queue->capacity) {
        queue->queue[queue->tail_idx] = data; 
        queue->num_of_stored_elements += 1;
        queue->tail_idx = (queue->tail_idx + 1) % queue->capacity;

        return true;
    }

    return false;
}

void* pop_from_queue(queue_t *queue) {

    if (queue->num_of_stored_elements == 0) {
        return NULL;
    }

    void *popped_value = queue->queue[queue->head_idx];
    queue->num_of_stored_elements -= 1;
    queue->head_idx = (queue->head_idx + 1) % queue->capacity;

    if (queue->num_of_stored_elements < queue->capacity / 3 && queue->capacity > 3) {
        queue_capacity_decrease(queue);
    }

    return popped_value;
}

void* get_from_queue(queue_t *queue, int idx) {
    if (idx < 0 || idx >= queue->num_of_stored_elements) {
        return NULL;
    }

    return queue->queue[(queue->head_idx + idx) % queue->capacity];
}

int get_queue_size(queue_t *queue) {
    return queue->num_of_stored_elements;
}
