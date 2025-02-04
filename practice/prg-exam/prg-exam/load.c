#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "exam_utils.h"

#ifndef COUNT
#define COUNT 100
#endif

#ifndef N
#define N 6
#endif

#define MAX 1920

enum {
    ERROR_OK = EXIT_SUCCESS,
    ERROR = EXIT_FAILURE
};

void print(void);
void print_hex(void);
int write(char *file_name);
// int read(char *file_name);

int main(int argc, char *argv[]) {
    int return_value = 0;
    char *mode = argc > 1 ? argv[1] : NULL;
    char *file_name = argc > 2 ? argv[2] : NULL;

    if (!mode) {
        fprintf(stderr, "ERROR: At least one argument must be given\n");
        return_value = ERROR;
    } 
    
    else if (!strcmp(mode, "print")) {
        print();
    }

    else if (!strcmp(mode, "hex")) {
        print_hex();
    }

    else if (!strcmp(mode, "write")) {
        return_value = write(file_name);
    }

    // else if (!strcmp(mode, "read")) {
    //     return_value = read(file_name);
    // } 

    else {
        fprintf(stderr, "ERROR: Unknown mode is given: %s\n", mode);
        return_value = ERROR;
    }



    return return_value;
}

void print(void) {
    for (int idx = 0; idx < COUNT; ++idx) {
        putchar('n');
        for (int idy = 0; idy < N; ++idy) {
            fprintf(stdout, " %d", rand() % MAX);
        }
        putchar('\n');
    }
}

void print_hex(void) {
    for (int idx = 0; idx < COUNT; ++idx) {
        fprintf(stdout, "0x%02x", 'n');
        for (int idy = 0; idy < N; ++idy) {
            int value = rand() % MAX;
            unsigned char v1 = (unsigned char)((value & 0xff00) >> 8);
            unsigned char v2 = (unsigned char)((value & 0xff00) >> 8);
            fprintf(stdout, " 0x%02x", v1);
            fprintf(stdout, " 0x%02x\n", v2);

        }
        putchar('\n');
    }
}

int write(char *file_name) {
    int return_value = file_name ? ERROR_OK : ERROR;
    if (return_value == ERROR) {
        fprintf(stderr, "ERROR");
        return return_value;
    }
    size_t s = (1 + N * 2 + 1) * COUNT;
    size_t d = ceil(sqrt(s / 3.0));

    int w, h;
    w = h = d;
    size_t size = w * h * 3;

    unsigned char *img = malloc(size * sizeof(unsigned char));
    my_assert(img != NULL, __func__, __LINE__, __FILE__);

    size_t c = 0;

    for (int idx = 0; idx < COUNT; ++idx) {
        img[c++] = 'n';
        for (int idy = 0; idy < N; ++idy) {
            int value = rand() % MAX;
            img[c++] = (unsigned char)((value & 0xff00) >> 8);
            img[c++] = (unsigned char)(value & 0xff00);
        }
        img[c++] = '\n';
    }

    for (; c < size; ++c) {
        img[c] = 0x0;
    }

    save_image_ppm_now(w, h, img, file_name);
    free(img);
    return return_value;
}


// int read(char *file_name) {
//     int return_value = ERROR_OK;

//     return return_value;
// }