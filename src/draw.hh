#include <FL/Fl_Bitmap.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>

#include "pt-draw.h"

#define WIN_MARGIN 10
#define WIN_IMG 256
#define WIN_TXT 25
#define WIN_WIDTH (WIN_IMG + (WIN_MARGIN * 2))
#define WIN_HEIGHT (WIN_IMG + (WIN_MARGIN * 4) + (WIN_TXT * 2))

/**
 * draw.hh
 *
 * An editor for drawing images using the library.
 **/
#ifndef DRAW_HH
#define DRAW_HH
  class Draw : public Fl_Double_Window{
    private:
      UINT8 buff[WIN_IMG * WIN_IMG];
      Fl_Input* input;
      Fl_Input* output;
      Fl_Box* box;
      Fl_Bitmap* img;

    public:
      /**
       * Draw()
       *
       * Build the window.
       *
       * @param w The width of the window.
       * @param h The height of the window.
       **/
      Draw(int w, int h, const char* title = 0) : Fl_Double_Window(w, h, title){
        /* Initialize the browser */
        init();
      }

    private:
      /**
       * init()
       *
       * Initialize the browser window.
       **/
      void init();

      /**
       * processInput()
       *
       * Process the input text and regenerate the image.
       **/
      void processInput();
  };
#endif
