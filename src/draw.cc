#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>

/**
 * main()
 *
 * The main entry method for the GUI.
 *
 * @return The exit code of the draw GUI.
 **/
int main(int argc, char** argv){
  Fl_Window *window = new Fl_Window(640, 480);
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
