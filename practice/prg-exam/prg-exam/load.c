#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "exam_utils.h"
#include "xwin_sdl.h"


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
void write(char *save_filename, unsigned char *save_img, int img_width, int img_height);
int read(char *file_name, char *save_filename);
int read_new(char *filename);

int main(int argc, char *argv[]) {
    int return_value = 0;
    char *mode = argc > 1 ? argv[1] : NULL;
    char *file_name = argc > 2 ? argv[2] : NULL;
    char *save_filename = argc > 3 ? argv[3] : NULL;

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

    // else if (!strcmp(mode, "write")) {
    //     return_value = write(file_name);
    // }

    else if (!strcmp(mode, "read")) {
        return_value = read(file_name, save_filename);
    } 

    else if (!strcmp(mode, "read_new")) {
        return_value = read_new(file_name);
    } 

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

// int write(char *file_name) {
//     int return_value = file_name ? ERROR_OK : ERROR;
//     if (return_value == ERROR) {
//         fprintf(stderr, "ERROR");
//         return return_value;
//     }

//     size_t s = (1 + N * 2 + 1) * COUNT;
//     size_t d = ceil(sqrt(s / 3.0));

//     int w, h;
//     w = h = d;
//     size_t size = w * h * 3;

//     unsigned char *img = malloc(size * sizeof(unsigned char));
//     my_assert(img != NULL, __func__, __LINE__, __FILE__);

//     size_t c = 0;

//     for (int idx = 0; idx < COUNT; ++idx) {
//         img[c++] = 'n';
//         for (int idy = 0; idy < N; ++idy) {
//             int value = rand() % MAX;
//             img[c++] = (unsigned char)((value & 0xff00) >> 8);
//             img[c++] = (unsigned char)(value & 0xff00);
//         }
//         img[c++] = '\n';
//     }

//     for (; c < size; ++c) {
//         img[c] = 0x0;
//     }

//     for (int idx = 0; idx < w * h; ++idx) {
//         fprintf(stdout, "%d ", img[idx]);
//     }

//     save_image_ppm_now(w, h, img, file_name);
//     free(img);
//     return return_value;
// }

int read(char *file_name, char *save_filename) {
    int return_value = file_name? ERROR_OK : ERROR;
    if (return_value == ERROR) {
        fprintf(stderr, "ERROR: There was a problem when loading file '%s'\n", file_name);
    }

    int img_width, img_height;
    unsigned char *img = xwin_load_image(file_name, &img_width, &img_height);
    my_assert(img != NULL, __func__, __LINE__, __FILE__);

    unsigned char *save_img = malloc(img_width * img_height * sizeof(unsigned char));
    if (save_img == NULL) {
        fprintf(stdout, "tHERE IS A PROBLEM WITH DYNAMICLY ALOCATED MEMORY\n");
    }

    for (int idx = 0; idx < img_width * img_height * 8; idx += 8) {
        int x_axis = img[idx] << 8 | img[idx + 1];
        int y_axis = img[idx + 2] << 8 | img[idx + 3];
        int width = img[idx + 4] << 8 | img[idx + 5];
        int height = img[idx + 6] << 8 | img[idx + 7];

        fprintf(stdout, "X:%5d, Y:%5d, Width:%5d, Height:%5d\n", x_axis, y_axis, width, height);
        save_img[idx] = (x_axis >> 8) & 0xff;
        save_img[idx + 1] = x_axis & 0x00ff;
        save_img[idx + 2] = (y_axis >> 8) &0xff;
        save_img[idx + 3] = y_axis & 0x00ff;
        save_img[idx + 4] = (width >> 8) &0xff;
        save_img[idx + 5] = width & 0x00ff;
        save_img[idx + 6] = (height >> 8) &0xff;
        save_img[idx + 7] = height & 0x00ff;
    }

    write(save_filename, save_img, img_width, img_height); 
    free(img);
    return return_value;
}

void write(char *save_filename, unsigned char *save_img, int img_width, int img_height) {
    save_image_ppm(img_width, img_height, save_img, save_filename);
    free(save_img);
}

int read_new(char *filename) {
    int return_value = 0;
    int img_width, img_height;
    unsigned char *img = xwin_load_image(filename, &img_width, &img_height);
    my_assert(img != NULL, __func__, __LINE__, __FILE__);

    for (int idx = 0; idx < img_width; idx++) {
        for (int idy= 0; idy < img_height; idy++) {
            int cursor = (idx * img_height + idy) * 3;

            int red = img[cursor];
            int green = img[cursor + 1];
            int blue = img[cursor + 2];

            fprintf(stdout, "   RED: %3d, GREEN: %3d, BLUE: %3d   |||", red, green, blue);
        }
        fprintf(stdout, "\n");
    }

    return return_value;
}