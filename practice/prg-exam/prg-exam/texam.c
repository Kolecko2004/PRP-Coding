/*
 * File name: texam.c
 * Date:      2017/01/16 08:43
 * Author:    Jan Faigl
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "exam_utils.h"
#include "xwin_sdl.h"
#include "save_jpeg.h"

bool process_file(FILE *file, unsigned char *img, int image_w, int image_h, bool anim);
bool copy(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2);
bool swap(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2);
int read_new(char *filename);

int main(int argc, char *argv[]) 
{
   char *img_source = argc > 1 ? argv[1] : NULL; // Test jestli existuije prvni argument - zdrojovy img
   char *command_source = argc > 2 ? argv[2] : NULL; // Test jestli existuije druhy argument - zdrojovy text
   char *output_file = argc > 3 ? argv[3] : NULL; // Test jestli existuije treti argument - output img
   bool anim = argc > 4 && strcmp(argv[4], "--anim") == 0; // Test jestli byl pouzit agument "--anim". strcmp testuje zda to je presne ten argument ktery chceme

   my_assert(img_source != NULL && command_source != NULL && output_file != NULL, __func__, __LINE__, __FILE__);

   // printf("Checking img_source pointer: %s\n", img_source);
   // printf("Checking command_source pointer: %s\n", command_source);
   // printf("Checking output_file pointer: %s\n", output_file);
   // printf("Checking --anim pointer: %d\n", anim);
   // read image

   int image_w, image_h; // deklarace promenych pro sirku a vysku obrazku
   unsigned char *img = xwin_load_image(img_source, &image_w, &image_h); // nacteni sirky a vysky, 
   my_assert(img != NULL, __func__, __LINE__, __FILE__); // otestovani img pointeru

   // printf("Checking width pointer: %d\n", image_w);
   // printf("Checking height pointer: %d\n", image_h);

   if (anim) {
      xwin_init(image_w, image_h); // pokud je animace wotevrani okna
   }

   FILE *file = fopen(command_source, "r"); // otevreni souboru se zadanim pohybu
   if (file == NULL) { // err pokud nastala chyba pri nacitani souboru
      fprintf(stderr, "ERROR: There was an error when loading %s file.\n", command_source);
      free(img);
      if (anim) {
         xwin_close();
         exit(1);
      }
   }

   if (!process_file(file, img, image_w, image_h, anim)) {
      fprintf(stdout, "ERROR: processing file err");
      free(img);
      if (anim) {
         xwin_close();
      }
      exit(-1);
   }

   // save_ppm_image_red(DEFAULT_WIDTH, DEFAULT_HEIGHT, "red.ppm");
   // save_ppm_image_green(DEFAULT_WIDTH, DEFAULT_HEIGHT, "green.ppm");

   if (output_file && (strstr(output_file, ".jpeg") || strstr(output_file, ".jpg"))) {
      save_image_jpeg(image_w, image_h, img, output_file);
   }

   else {
      save_image_ppm(image_w, image_h, img, output_file);
   }

   if (anim) {
      xwin_close();
   }
   free(img);

   return EXIT_SUCCESS;
}

bool process_file(FILE *file, unsigned char *img, int image_w, int image_h, bool anim) { // funkce na nacteni informaci z txt souboru
   bool ret = true; // zalozeni vsech promennych
   int x1, y1, x2, y2;
   int w, h;
   char cmd[3];
   int counter = 0;

   while(ret && !feof(file)) { // cyklus do te doby dokud nemame konec file
      int scan_result = fscanf(file, "%2s %d %d %d %d %d %d\n", cmd, &x1, &y1, &w, &h, &x2, &y2); // fscanf pro cteni vsech dat
      // printf("Read: command='%s', x1=%d, y1=%d, w=%d, h=%d, x2=%d, y2=%d (r=%d)\n", 
      // cmd, x1, y1, w, h, x2, y2, r);
      if (scan_result == 7 && strcmp(cmd, "cp") == 0) { // pokud pocet nactenych dat je 7 a zaroven je cmd hodnota "cp" volame copy
         ret = copy(img, image_w, image_h, x1, y1, w, h, x2, y2);
      }
      else if (scan_result == 7 && strcmp(cmd, "sw") == 0) { // pokud pocet nactenych dat je 7 a zaroven je cmd hodnota "sw" volame swap
         ret = swap(img, image_w, image_h, x1, y1, w, h, x2, y2); 
      }
      else { // pokud ani jedna predchozi podminka neprosla koncime 
         ret = false;
         break;
      }

      counter  += 1; // animace obrazu v anim okne
      if (anim && (counter % 1) == 0) {
         xwin_redraw(image_w, image_h, img);
         delay(1000); xsdce  
      }
   }

   return ret;
}

bool copy(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2) {
   bool ret = true;

   for (int xi = 0; xi < w; ++xi) {
      for (int yi = 0; yi < h; ++yi) {
         const int sx = x1 + xi;
         const int sy = y1 + yi;
         const int dx = x2 + xi;
         const int dy = y2 + yi;

         if (sx >= 0 && sx < image_w && sy >= 0 && sy < image_h && dx >= 0 && dx < image_w && dy >= 0 && dy < image_h) {
            for (int i = 0; i < 3; ++i) {

                img[(dy * image_w + dx) * 3 + i] = img[(sy * image_w + sx) * 3 + i];
            }
         } 
         else {
            fprintf(stderr, "copy of image was unsucesfull - out of range\n");
            return false;
         }
      }
   }
   return ret;
}

bool swap(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2) {
   
   bool ret = true;
   for (int xi = 0; xi < w; ++xi) {
      for (int yi = 0; yi < h; ++yi) {
         const int sx = x1 + xi;
         const int sy = y1 + yi;
         const int dx = x2 + xi;
         const int dy = y2 + yi;

         if (
            sx >= 0 && sx < image_w && sy >= 0 && sy < image_h
            && dx >= 0 && dx < image_w && dy >= 0 && dy < image_h) {
            for (int i = 0; i < 3; ++i) {
               unsigned char t = img[(sy * image_w + sx) * 3 + i];
               img[(sy * image_w + sx) * 3 + i] = img[(dy * image_w + dx) * 3 + i];
               img[(dy * image_w + dx) * 3 + i] = t;
            }
         } 
         else {
            fprintf(stderr, "swap of image was unsuccessful - out of range\n");
            return false;
         }
      }
   }
   return ret;
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

/* end of texam.c */
