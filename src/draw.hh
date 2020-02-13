#include <FL/Fl_Double_Window.H>

/**
 * draw.hh
 *
 * An editor for drawing images using the library.
 **/
#ifndef DRAW_HH
#define DRAW_HH
  class Draw : public Fl_Double_Window{
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

      /**
       * init()
       *
       * Initialize the browser window.
       **/
      void init();
  };
#endif
