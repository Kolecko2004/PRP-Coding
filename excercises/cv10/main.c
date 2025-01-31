#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/* Reads queue size from user */
int get_input() {
    int capacity = 0;
    int result = fscanf(stdin, "%d", &capacity);
    if (result != 1) {
        fprintf(stderr, "Error reading queue size\n");
        exit(1);
    }
    return capacity;
}

/* Executes commands on the queue */
void performing_commands(queue_t *queue, char command, int data) {
    if (command == 'a') {
        if (!push_to_queue(queue, &data)) {
            fprintf(stdout, "Queue is full\n");
        }

        fprintf(stdout, "Before program result\n");
        for (int i = 0; i < queue->capacity; i++) {
            fprintf(stdout, "num:%d at idx: %d\n", queue->queue[queue->head_idx + i], queue->head_idx + i);
        }
        fprintf(stdout, "----------------\n");
    } 
    
    else if (command == 'g') {
        void *element = get_from_queue(queue, data);
        if (element == NULL) {
            fprintf(stdout, "NULL\n");
        } 
        
        else {
            fprintf(stdout, "%d\n", *(int *)element);
        }
    } 
    
    else if (command == 'r') {
        void *popped = pop_from_queue(queue);
        if (popped == NULL) {
            fprintf(stdout, "NULL\n");
        } 
        
        else {
            fprintf(stdout, "%d\n", *(int *)popped);
        }
    }
    
    else {
        fprintf(stdout, "Unknown command '%c'. Use 'a', 'g', or 'r'.\n", command);
        exit(100);
    }
}

/* Processes user input commands */
void input_command(queue_t *queue) {
    int scan_result = 0;
    char command;  // Declare the 'command' variable here
    int data;      // Declare the 'data' variable here

    while ((scan_result = fscanf(stdin, " %c %d", &command, &data)) != EOF) {
        if (command == 'r' && scan_result != 1) {
            fprintf(stdout, "Input command has wrong structure\n");
            break;
        }
        if (command != 'r' && scan_result != 2) {
            fprintf(stdout, "Input command has wrong structure\n");
            break;
        }
        performing_commands(queue, command, data);
    }
}

/* Main function */
int main() {
    queue_t *queue = create_queue(get_input());
    input_command(queue);
    delete_queue(queue);
    return 0;
}
