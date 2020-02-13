#include "draw.hh"

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

void Draw::init(){
  /* TODO: Initialize the browser window. */
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
  Fl_Window* win = new Fl_Window(WIN_WIDTH, WIN_HEIGHT, "Pine Time Draw Editor");
  /* Create the browser */
  Draw* d = new Draw(10, 40, win->w() - 20, win->h() - 50);
  /* Finish up definition and close the window */
  win->end();
  win->show(argc, argv);
  return Fl::run();
}
