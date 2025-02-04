#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "exam_utils.h"
#include "xwin_sdl.h"
#include "save_jpeg.h"


bool process_file(FILE *file, unsigned char *img, int image_w, int image_h, bool anim);
bool copy(unsigned char *img, int image_w, int image_h, int org_x, int org_y, int block_w, int block_h, int unorg_x, int unorg_y);
bool swap(unsigned char *img, int image_w, int image_h, int org_x, int org_y, int block_w, int block_h, int unorg_x, int unorg_y);

int main(int argc, char *argv[]) {
    int return_value = 0;
    // Load arguments
    char * img_source = argc > 1 ? argv[1] : NULL;
    char * txt_source = argc > 2 ? argv[2] : NULL;
    char * img_output = argc > 3 ? argv[3] : NULL;
    bool anim = argc > 4 && (strcmp(argv[4], "--anim")) == 0;

    // Test arguments
    my_assert(img_source != NULL && txt_source != NULL && img_output != NULL, __func__, __LINE__, __FILE__);

    // image values
    int image_w, image_h;
    unsigned char *img = xwin_load_image(img_source, &image_w, &image_h);
    my_assert(img != NULL, __func__, __LINE__, __FILE__);

    if (anim) {
        xwin_init(image_w, image_h);
    }

    // Get txt file
    FILE *txt_file = fopen(txt_source, "r");

    // Test file
    if (txt_file == NULL) {
        fprintf(stderr, "ERROR: There was a problem loading file: '%s'\n", txt_source);
        if (anim) {
            xwin_close();
        }
        free(img);
        exit(101);
    }

    if (!process_file(txt_file, img, image_w, image_h, anim)) {
        fprintf(stderr, "ERROR: There was a problem with processing file: '%s'\n", txt_source);
        if (anim) {
            xwin_close();
        }
        free(img);
        fclose(txt_file);
        exit(102);
    }

    if ((img_output && strstr(img_output, ".jpg")) || (img_output && strstr(img_output, ".jpeg"))) {
        save_image_jpeg(image_w, image_h, img, img_output);
    }

    else {
        save_image_ppm(image_w, image_h, img, img_output);
    }

    if (anim) {
        xwin_close();
    }

    free(img);
    
    return return_value;
}

bool process_file(FILE *file, unsigned char *img, int image_w, int image_h, bool anim) {
    // deklarace vsech potrebnych promenych
    bool return_value = true;
    int org_x, org_y, unorg_x, unorg_y;
    int block_w, block_h;
    char cmd[3];
    int counter = 0;

    // cyklus pro nactani hodnot z txt_souboru a volani funkci pro zmenu obrazku
    while (return_value && !feof(file)) {
        int scan_result = fscanf(file, "%2s %d %d %d %d %d %d", cmd, &org_x, &org_y, &block_w, &block_h, &unorg_x, &unorg_y);
        if (scan_result == 7 && strcmp(cmd, "cp") == 0) {
            return_value = copy(img, image_w, image_h, org_x, org_y, block_w, block_h, unorg_x, unorg_y);
        }

        else if (scan_result == 7 && strcmp(cmd, "sw") == 0) {
            return_value = swap(img, image_w, image_h, org_x, org_y, block_w, block_h, unorg_x, unorg_y);
        }

        // Konec scanovani
        else {
            return_value = false;
            break;
        }

        // kontrola animace
        counter += 1;
        if (anim && (counter % 1) == 0) {
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

            if (sx >= 0 && sx < image_w && sy >= 0 && sy < image_h && dx >= 0 && dx < image_w && dy >= 0 && dy < image_h) {
                for (int idx = 0; idx < 3; ++idx) {
                    img[(dy * image_w + dx) * 3 + idx] = img[(sy * image_w + sx) * 3 + idx];
                }
            }

            else {
                fprintf(stderr, "ERROR: There was an error in coordinates\n");
                fprintf(stderr, "ERROR: COPY of image was unsucesfull\n");
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
            const int sx = org_x + xi;
            const int sy = org_y + yi;
            const int dx = unorg_x + xi;
            const int dy = unorg_y + yi;

            if (sx >= 0 && sx < image_w && sy >= 0 && sy < image_h && dx >= 0 && dx < image_w && dy >= 0 && dy < image_h) {
                
                for (int idx = 0; idx < 3; ++idx) {
                    unsigned char temp = img[(sy * image_w + sx) * 3 + idx];

                    img[(sy * image_w + sx) * 3 + idx] = img[(dy * image_w + dx) * 3 + idx];
                    img[(dy * image_w + dx) * 3 + idx] = temp;
                }
            }

            else {
                fprintf(stderr, "ERROR: There was an error in coordinates\n");
                fprintf(stderr, "ERROR: SWAP of image was unsucesfull\n");
                return_value = false;
            }

        }
    }

    return return_value;
}