#include "draw.hh"

#include <FL/Fl.H>
#include <FL/Fl_Bitmap.H>
#include <FL/Fl_Box.H>

#include "icons.h"
#include "pt-draw.c"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

void Draw::init(){
  /* TODO: Initialize the window. */
  /* Create the test image */
  UINT8 buff[(256 * 256) / 8];
  UINT8 drawBuff[256 * 256];
  pt_draw_create_bitmap(ICON_BLUETOOTH, ICON_BLUETOOTH_LEN, buff, 256);
  expandImage(buff, 256 * 256, drawBuff);
  /* Draw the test image */
  Fl_Box* box = new Fl_Box(10, 10, 256, 256, "canvas");
  Fl_Bitmap* img = new Fl_Bitmap(buff, 256, 256);
  box->image(img);
  box->show();
}

void Draw::expandImage(unsigned char* a, int aLen, unsigned char* b){
  for(unsigned int i = 0; i < aLen; i++){
    UINT8 r = a[i / 8] & (0b1 << (7 - (i % 8)));
    b[i] = r ? 1 : 0;
  }
}

/**
 * main()
 *
 * The main entry method for the GUI.
 *
 * @return The exit code of the draw GUI.
 **/
int main(int argc, char** argv){
  /* Create the container window */
  Draw* win = new Draw(WIN_WIDTH, WIN_HEIGHT, "Pine Time Draw Editor");
  /* Finish up definition and close the window */
  win->end();
  win->show(argc, argv);
  return Fl::run();
}
