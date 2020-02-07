/**
 * pt-draw.h
 *
 * A simple scalable vector library for the pine time.
 **/
#ifndef PT_DRAW_H
#define PT_DRAW_H
  #define UINT8 unsigned char

  #define SHAPE_MASK (0b11 << 0)
  #define LIN_SIMP   (0)
  #define LIN_CURV   (1)
  #define SEQ_SIMP   (2)
  #define SEQ_CURV   (3)
  #define LINE_MASK  (0b1 << 0)
  #define SEQ_MASK   (0b1 << 1)
  #define FILL_MASK  (0b1 << 2)
  #define RES_MASK   (0b1 << 3)
  #define LEN_MASK   (0b1111 << 4)

  /**
   * pt_draw_simple_line()
   *
   * Draw a simple linear line to the binary bitmap from the given parameters.
   *
   * @param xy1 The (X1,Y1) pair in a single byte.
   * @param xy2 The (X2,Y2) pair in a single byte.
   * @param buff A pointer to the binary buffer to be set. The buffer must have
   * adequate space for storing the resulting data.
   * @param size The size of the width and height (size = width = height). The
   * number of pixels in total is size x size, total number of bytes is (size x
   * size) / 8 rounded up to the nearest byte.
   **/
  void pt_draw_simple_line(UINT8 xy1, UINT8 xy2, UINT8* buff, unsigned int size);

  /**
   * pt_draw_create_bitmap()
   *
   * This method is used for creating a binary bitmap from the scalable vector
   * image description.
   *
   * @param desc A pointer to the description array of the object to be created
   * as a sequence of bytes.
   * @param len The length of the description sequence.
   * @param buff A pointer to the binary buffer to be set. The buffer must have
   * adequate space for storing the resulting data.
   * @param size The size of the width and height (size = width = height). The
   * number of pixels in total is size x size, total number of bytes is (size x
   * size) / 8 rounded up to the nearest byte.
   **/
  void pt_draw_create_bitmap(UINT8* desc, unsigned int len, UINT8* buff, unsigned int size);
#endif
