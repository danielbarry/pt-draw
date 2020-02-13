#include "draw.hh"

#include <FL/Fl.H>
#include <FL/Fl_Bitmap.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>

#include "icons.h"
#include "pt-draw.c"

#define WIN_MARGIN 10
#define WIN_IMG 256
#define WIN_TXT 25
#define WIN_WIDTH (WIN_IMG + (WIN_MARGIN * 2))
#define WIN_HEIGHT (WIN_IMG + (WIN_MARGIN * 4) + (WIN_TXT * 2))

void Draw::init(){
  /* Create text input */
  Fl_Input* input = new Fl_Input(
    WIN_MARGIN,
    WIN_MARGIN,
    WIN_WIDTH - (WIN_MARGIN * 2),
    WIN_TXT
  );
  input->value("Input");
  input->when(FL_WHEN_CHANGED);
  input->callback(
    [](Fl_Widget* sender, void* origin){
      /* TODO: Do something about it. */
    },
    this
  );
  /* Create text output */
  Fl_Input* output = new Fl_Input(
    WIN_MARGIN,
    (WIN_MARGIN * 3) + WIN_IMG + WIN_TXT,
    WIN_WIDTH - (WIN_MARGIN * 2),
    WIN_TXT
  );
  output->value("Output");
  output->when(FL_WHEN_CHANGED);
  output->callback(
    [](Fl_Widget* sender, void* origin){
      /* TODO: Do something about it. */
    },
    this
  );
  /* Create the test image */
  UINT8 buff[(WIN_IMG * WIN_IMG) / 8];
  UINT8 drawBuff[WIN_IMG * WIN_IMG];
  pt_draw_create_bitmap(ICON_BLUETOOTH, ICON_BLUETOOTH_LEN, buff, WIN_IMG);
  expandImage(buff, WIN_IMG * WIN_IMG, drawBuff);
  /* Draw the test image */
  Fl_Box* box = new Fl_Box(
    WIN_MARGIN,
    WIN_TXT + (WIN_MARGIN * 2),
    WIN_IMG,
    WIN_IMG
  );
  Fl_Bitmap* img = new Fl_Bitmap(buff, WIN_IMG, WIN_IMG);
  box->box(FL_BORDER_BOX);
  box->image(img);
  box->redraw();
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
