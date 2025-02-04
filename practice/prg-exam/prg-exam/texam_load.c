#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "exam_utils.h"
#include "save_jpeg.h"
#include "xwin_sdl.h"

bool process_file(FILE *file, unsigned char *img ,int image_w, int image_h, bool anim);
bool copy(unsigned char *img, int image_w, int image_h, int org_x, int org_y, int block_w, int block_h, int unorg_x, int unorg_y);
bool swap(unsigned char *img, int image_w, int image_h, int org_x, int org_y, int block_w, int block_h, int unorg_x, int unorg_y);

int main (int argc, char *argv[]) {
    int return_value = 0;

    char *source_img = argc > 1 ? argv[1] : NULL;
    char *source_txt = argc > 2 ? argv[2] : NULL;
    char *output_img = argc > 3 ? argv[3] : NULL;
    bool anim = argc > 4 && (strcmp(argv[4], "--anim")) == 0;
    my_assert(source_img != NULL && source_txt != NULL && output_img != NULL, __func__, __LINE__, __FILE__);

    int image_w, image_h;
    unsigned char *img = xwin_load_image(source_img, &image_w, &image_h);
    my_assert(img != NULL, __func__, __LINE__, __FILE__);

    FILE *txt_file = fopen(source_txt, "r");
    if (txt_file == NULL) {
        fprintf(stderr, "ERROR: There was a problem when opening file '%s'\n", source_txt);
        free(img);
        exit(100);
    }

    if (anim) {
        xwin_init(image_w, image_h);
    }

    if (!process_file(txt_file, img, image_w, image_h, anim)) {
        fprintf(stderr, "ERROR: There was a problem when processing file '%s'\n", source_txt);
        if (anim) {
            xwin_close();
        }
        free(img);
        fclose(txt_file);
        exit(101);
    }

    if ((output_img && strstr(output_img, ".jpg")) || (output_img && strstr(output_img, ".jpeg"))) {
        save_image_jpeg(image_w, image_h, img, output_img);
    }

    else {
        save_image_ppm(image_w, image_h, img, output_img);
    }

    if (anim) {
        xwin_close();
    }
    free(img);
    fclose(txt_file);

    return return_value;
}

bool process_file(FILE *file, unsigned char *img ,int image_w, int image_h, bool anim) {
    bool return_value = true;

    int org_x, org_y, unorg_x, unorg_y;
    int block_w, block_h;
    char cmd[3];
    int counter = 0;

    while(return_value && !feof(file)) {
        int scan_result = fscanf(file, "%2s %d %d %d %d %d %d\n", cmd, &org_x, &org_y, &block_w, &block_h, &unorg_x, &unorg_y);

        if (scan_result == 7 && strcmp(cmd, "cp") == 0) {
            return_value = copy(img, image_w, image_h, org_x, org_y, block_w, block_h, unorg_x, unorg_y);
        }

        else if (scan_result == 7 && strcmp(cmd, "sw") == 0) {
            return_value = swap(img, image_w, image_h, org_x, org_y, block_w, block_h, unorg_x, unorg_y);
        }

        else {
            return_value = false;
            break;
        }

        counter++;
        if ((anim % 1) == 0) {
            xwin_redraw(image_w, image_h, img);
            delay(1000);
        }
    }

    return return_value;
}

bool copy(unsigned char *img, int image_w, int image_h, int org_x, int org_y, int block_w, int block_h, int unorg_x, int unorg_y) {
    bool return_value = true;
    for (int xi = 0; xi < block_w; ++xi) {
        for (int yi = 0; yi < block_h; ++yi) {
            const int sx = org_x + xi;
            const int sy = org_y + yi;
            const int dx = unorg_x + xi;
            const int dy = unorg_y + yi;
            
            if (dx >= 0 && dx < image_w && dy >= 0 && dy < image_h && sx >= 0 && sx < image_w && sy >= 0 && sy < image_h) {
                for (int idx = 0; idx < 3; ++idx) {
                    img[(dy * image_w + dx) * 3 + idx] = img[(sy * image_w + sx) * 3 + idx]; 
                }
            }
            
            else {
                fprintf(stderr, "ERROR: There was a problem when coordinates from file\n");
                return_value = false;
            }
        }
    }

    return return_value;
}

bool swap(unsigned char *img, int image_w, int image_h, int org_x, int org_y, int block_w, int block_h, int unorg_x, int unorg_y) {
    bool return_value = true;

    for (int xi = 0; xi < block_w; ++xi) {
        for (int yi = 0; yi < block_h; ++yi) {
            const int dx = org_x + xi;
            const int dy = org_y + yi;
            const int sx = unorg_x + xi;
            const int sy = unorg_y + yi;

            for (int idx = 0; idx < 3; ++idx) {
                if (dx >= 0 && dx < image_w && dy >= 0 && dy < image_h && sx >= 0 && sx < image_w && sy >= 0 && sy < image_h) {
                    unsigned char temp = img[(dy * image_w + dx) * 3 + idx];
                    img[(dy * image_w + dx) * 3 + idx] = img[(sy * image_w + sx) * 3 + idx]; 
                    img[(sy * image_w + sx) * 3 + idx] = temp;
                }

                else {
                    fprintf(stderr, "ERROR: There was a problem when coordinates from file\n");
                    return_value = false;
                }
            }
        }
    }

    return return_value;
}
