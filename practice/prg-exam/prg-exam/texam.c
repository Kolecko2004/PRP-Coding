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

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

bool process_file(FILE *file, unsigned char *img, int image_w, int image_h, bool anim);
bool copy(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2);
bool swap(unsigned char *img, int image_w, int image_h, int x1, int y1, int w, int h, int x2, int y2);

int main(int argc, char *argv[]) 
{
   char *img_source = argc > 1 ? argv[1] : NULL; // Test jestli existuije prvni argument - zdrojovy img
   char *txt_source = argc > 2 ? argv[2] : NULL; // Test jestli existuije druhy argument - zdrojovy text
   char *output_file = argc > 3 ? argv[3] : NULL; // Test jestli existuije treti argument - output img
   bool anim = argc > 4 && !strcmp(argv[4], "--anim") == 0; // Test jestli byl pouzit agument "--anim". strcmp testuje zda to je presne ten argument ktery chceme

   my_assert(img_source != NULL && txt_source != NULL && output_file != NULL, __func__, __LINE__, __FILE__);

   // printf("Checking img_source pointer: %s\n", img_source);
   // printf("Checking txt_source pointer: %s\n", txt_source);
   // printf("Checking output_file pointer: %s\n", output_file);
   // printf("Checking --anim pointer: %d\n", anim);
   // read image
   int image_w, image_h;
   unsigned char *img = xwin_load_image(img_source, &image_w, &image_h);
   my_assert(img != NULL, __func__, __LINE__, __FILE__);

   if (anim) {
      xwin_init(image_w, image_h);
   }

   FILE *file = fopen(txt_source, "r");
   if (file == NULL) {
      fprintf(stderr, "ERROR: There was an error when loading %s file.\n", txt_source);
      free(img);
      if (anim) {
         xwin_close();
         exit(1);
      }
   }

   my_assert(process_file(file, img, image_w, image_h, anim), __func__, __LINE__, __FILE__);

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

bool process_file(FILE *file, unsigned char *img, int image_w, int image_h, bool anim) {
   bool ret = true;
   int x1, y1, x2, y2;
   int w, h;
   char cmd[3];
   int counter = 0;

   while(ret && !feof(file)) {
      int r = fscanf(file, "%2s %d %d %d %d %d %d\n", cmd, &x1, &y1, &w, &h, &x2, &y2);
      // printf("Read: command='%s', x1=%d, y1=%d, w=%d, h=%d, x2=%d, y2=%d (r=%d)\n", 
      // cmd, x1, y1, w, h, x2, y2, r);
      if (r == 7 && strcmp(cmd, "cp") == 0) {
         ret = copy(img, image_w, image_h, x1, y1, w, h, x2, y2);
      }
      else if (r == 7 && strcmp(cmd, "sw") == 0) {
         ret = swap(img, image_w, image_h, x1, y1, w, h, x2, y2);
      }
      else {
         ret = false;
         break;
      }

      counter  += 1;
      if (anim && (counter % 15) == 0) {
         xwin_redraw(image_w, image_h, img);
         delay(10);
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
            fprintf(stderr, "copy of image was unsuccessful - out of range\n");
            return false;
         }
      }
   }
   return ret;
}

/* end of texam.c */
