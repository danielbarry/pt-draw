#include <FL/Fl_Browser.H>

/**
 * draw.hh
 *
 * An editor for drawing images using the library.
 **/
#ifndef DRAW_HH
#define DRAW_HH
  class Draw : public Fl_Browser{
    public:
      /**
       * Draw()
       *
       * Build the browser window.
       *
       * @param X The X location of the browser window.
       * @param Y The Y location of the browser window.
       * @param W The width of the browser window.
       * @param H The height of the browser window.
       * @param L The length of the browser window.
       **/
      Draw(int X, int Y, int W, int H, const char* L = 0) : Fl_Browser(X, Y, W, H, L){
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
