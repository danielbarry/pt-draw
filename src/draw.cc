#include "draw.hh"

#include <FL/Fl.H>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

void Draw::init(){
  /* TODO: Initialize the window. */
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
