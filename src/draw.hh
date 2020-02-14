#include <algorithm>
#include <FL/Fl_Bitmap.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <iomanip>
#include <string>
#include <vector>

#include "pt-draw.h"

#define MAX_BUFF 2048
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
      UINT8 inBuff[MAX_BUFF];
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

      /**
       * removeAll()
       *
       * Remove all occurrences of a specific character.
       *
       * @param str The string to be searched for characters,
       * @param c The character to be replaced.
       * @return The string with the replaced characters.
       **/
      static std::string removeAll(std::string str, char c){
        str.erase(std::remove(str.begin(), str.end(), c), str.end());
        return str;
      }

      /**
       * replaceAll()
       *
       * Replace all instances of one string with another.
       *
       * @param a The string to be have the replace performed upon.
       * @param b The string to be searched for.
       * @param c The string to be inserted upon finding the search string.
       * @return The initial string.
       **/
      static std::string replaceAll(std::string a, std::string b, std::string c){
        int s = a.find(b);
        while(s != std::string::npos){
          a.replace(s, b.size(), c);
          s = a.find(b);
        }
        return a;
      }

      /**
       * split()
       *
       * Split a string by a given delimiter.
       *
       * @param str The string to be searched.
       * @param delim The string to be split on.
       * @return An array of the strings.
       **/
      static std::vector<std::string> split(std::string str, std::string delim){
        std::vector<std::string> list;
        std::string token;
        for(;;){
          size_t first = str.find_first_of(delim);
          if(first == std::string::npos){
            /* Push back the final piece of the string */
            list.push_back(str);
            return list;
          }
          token = str.substr(0, str.find_first_of(delim));
          str = str.substr(str.find_first_of(delim) + 1);
          list.push_back(token);
        }
        return list;
      }

      /**
       * intToHexStr()
       *
       * Convert an integer to a hexadecimal string.
       *
       * @param i The integer to be converted.
       * @return The resulting string.
       **/
      static std::string intToHexStr(int i){
        std::stringstream ss;
        ss << "0x" << std::hex << i;
        return std::string(ss.str());
      }

      /**
       * strToInt()
       *
       * Convert a string to an integer safely.
       *
       * @param str The string to be converted.
       * @param base The integer conversion base. If less than zero, assume
       * base 10.
       * @return The converted value, otherwise 0.
       **/
      static int strToInt(std::string str, int base){
        try{
          if(base <= 0){
            return std::stoi(str);
          }else{
            return std::stoi(str, NULL, base);
          }
        }catch(...){
          return 0;
        }
      }
  };
#endif
