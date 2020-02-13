#include "draw.hh"

#include <FL/Fl.H>

#include "icons.h"
#include "pt-draw.c"

void Draw::init(){
  /* Create text input */
  input = new Fl_Input(
    WIN_MARGIN,
    WIN_MARGIN,
    WIN_WIDTH - (WIN_MARGIN * 2),
    WIN_TXT
  );
  input->value("{LINE | (5 - 1), 0x44, 0xCC, 0x8F, 0x80, 0xC4, 0x4C};");
  input->when(FL_WHEN_CHANGED);
  input->callback(
    [](Fl_Widget* sender, void* origin){
      ((Draw*)origin)->processInput();
    },
    this
  );
  /* Create text output */
  output = new Fl_Input(
    WIN_MARGIN,
    (WIN_MARGIN * 3) + WIN_IMG + WIN_TXT,
    WIN_WIDTH - (WIN_MARGIN * 2),
    WIN_TXT
  );
  output->value("Output");
  /* Draw the test image */
  box = new Fl_Box(
    WIN_MARGIN,
    WIN_TXT + (WIN_MARGIN * 2),
    WIN_IMG,
    WIN_IMG
  );
  box->box(FL_BORDER_BOX);
  box->color(0xFFFFFF00, 0x00000000);
  processInput();
  box->show();
}

void Draw::processInput(){
  /* TODO: Process input. */
  output->value(input->value());
  /* Clear the original buffer */
  memset(buff, 0, WIN_IMG * WIN_IMG);
  /* Create a new image */
  pt_draw_create_bitmap(ICON_BLUETOOTH, ICON_BLUETOOTH_LEN, buff, WIN_IMG);
  /* Reverse pixel bits for FLTK */
  for(unsigned int i = 0; i < (WIN_IMG * WIN_IMG) / 8; i++){
    unsigned char b = buff[i];
    buff[i] = ((b             ) << 7) |
              ((b & 0b00000010) << 5) |
              ((b & 0b00000100) << 3) |
              ((b & 0b00001000) << 1) |
              ((b & 0b00010000) >> 1) |
              ((b & 0b00100000) >> 3) |
              ((b & 0b01000000) >> 5) |
              ((b             ) >> 7);
  }
  /* Reprocess the buffer and draw */
  img = new Fl_Bitmap(buff, WIN_IMG, WIN_IMG);
  box->image(img);
  box->redraw();
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
