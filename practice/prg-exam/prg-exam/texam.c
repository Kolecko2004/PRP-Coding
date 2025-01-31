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

bool process_file(FILE *fd, unsigned char *img, int image_w, int image_h, bool anim);
bool copy(unsigned char *img, int image_w, int image_h, int y1, int w, int h, int x2, int y2);
bool swap(unsigned char *img, int image_w, int image_h, int y1, int w, int h, int x2, int y2);

int main(int argc, char *argv[]) 
{
   char *img_source = argc > 1 ? argv[1] : NULL; // Test jestli existuije prvni argument - zdrojovy img
   my_assert(img_source != NULL, __func__, __LINE__, __FILE__);

   char *txt_source = argc > 2 ? argv[2] : NULL; // Test jestli existuije druhy argument - zdrojovy text
   my_assert(txt_source != NULL, __func__, __LINE__, __FILE__);

   char *output_file = argc > 3 ? argv[3] : NULL; // Test jestli existuije treti argument - output img
   my_assert(output_file != NULL, __func__, __LINE__, __FILE__);

   bool anim = (argc > 4 && !strcmp(argv[4], "--anim")) ? true : false; // Test jestli byl pouzit agument "--anim". strcmp testuje zda to je presne ten argument ktery chceme
   // bool jpeg = (strstr(output_file, "jpeg") || strstr(output_file, ".jpg"));

   int image_w, image_h;
   unsigned char *img = xwin_load_image(img_source, &image_w, &image_h);
   my_assert(img != NULL, __func__, __LINE__, __FILE__);

   if (anim) {
      xwin_init(image_w, image_h);
   }

   xwin_redraw(image_w, image_h, img);
   delay(100);

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

   save_ppm_image_red(DEFAULT_WIDTH, DEFAULT_HEIGHT, "red.ppm");
   save_ppm_image_green(DEFAULT_WIDTH, DEFAULT_HEIGHT, "green.ppm");

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

   bool ret = false;
   int x1, y1, x2, y2;
   char cmd[3];
   int counter = 0;

   while(!feof(fd)) {
      int r = fscanf(file, "%2s, %d, %d, %d, %d, %d, %d\n", cmd, &x1, &y1, &w, &h, &x2, &y2);
      if (r == 7 && strcmp(cmd, "cp") == 0) {

      }

      else if (r == 7 && strcmp(cmd, "sw") == 0) {

      }

      else {
         ret = false;
         break;
      }

      counter  += 1;
      if (anim && (counter % 15) == 0) {
         xwin_redraw(img, image_w, image_h);
         delay(10);
      }
   }

   return ret;
}

bool copy(unsigned char *img, int image_w, int image_h, int y1, int w, int h, int x2, int y2) {

   bool ret = false;

   return ret;
}


bool swap(unsigned char *img, int image_w, int image_h, int y1, int w, int h, int x2, int y2) {
   bool ret = false;

   return ret;
}

/* end of texam.c */
