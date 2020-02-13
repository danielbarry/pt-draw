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

    private:
      /**
       * init()
       *
       * Initialize the browser window.
       **/
      void init();

      /**
       * expandImage()
       *
       * Expand a binary array image to a byte array.
       *
       * @param a The primary array source.
       * @param aLen Teh length of the input array.
       * @param b The secondary array destination.
       **/
      void expandImage(unsigned char* a, int aLen, unsigned char* b);
  };
#endif
