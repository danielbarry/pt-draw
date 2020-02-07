#include "pt-draw.h"

void pt_draw_create_bitmap(UINT8* desc, unsigned int len, UINT8* buff, unsigned int size){
  /* TODO: Basic sanity checks before starting. */
  /* Get line properties */
  UINT8 shape = desc[0] & SHAPE_MASK;
  UINT8 shapeLen = (desc[0] & LEN_MASK) >> 4;
  /* Generate shape */
  switch(shape){
    case LIN_SIMP:
      /* TODO: Process simple line. */
      printf("Simple line\n"); // TODO
      break;
    case LIN_CURV:
      /* TODO: Process simple curve. */
      printf("Simple curve\n"); // TODO
      break;
    case SEQ_SIMP:
      /* TODO: Process sequenced line. */
      printf("Sequenced line\n"); // TODO
      break;
    case SEQ_CURV:
      /* TODO: Process sequenced curve. */
      printf("Sequenced curve\n"); // TODO
      break;
  }
}
