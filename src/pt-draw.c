#include "pt-draw.h"

#include <stdlib.h>

#ifndef NUM_SEGS
  #define NUM_SEGS 8
#endif

#define SEG_SIZE ( 1.0f / NUM_SEGS )
#define GET_POINT(i,j,p) ( i + ((j - i) * p) )
#define GET_NIBBLE_HIGH(i) ( (i & 0b11110000) >> 4 )
#define GET_NIBBLE_LOW(i) ( i & 0b1111 )

void pt_draw_raw_line(int x1, int y1, int x2, int y2, UINT8* buff, unsigned int size){
  int dx, dy, sx, sy, err, e2;
  /* Deltas and stepping */
  dx = abs(x2 - x1);
  dy = abs(y2 - y1);
  sx = x1 < x2 ? 1 : -1;
  sy = y1 < y2 ? 1 : -1;
  /* Draw line into buffer */
  err = (dx > dy ? dx : -dy) / 2;
  for(;;){
    /* Set pixel */
    int p = x1 + (y1 * size);
    buff[p / 8] |= 0b1 << (7 - (p % 8));
    /* Check if line drawn */
    if(x1 == x2 && y1 == y2){
      break;
    }
    /* Advance pixels */
    e2 = err;
    if(e2 > -dx){
      err -= dy;
      x1 += sx;
    }
    if(e2 < dy){
      err += dx;
      y1 += sy;
    }
  }
}

void pt_draw_simple_line(UINT8 xy1, UINT8 xy2, UINT8* buff, unsigned int size){
  int x1, y1, x2, y2;
  /* Get line variables */
  x1 = GET_NIBBLE_HIGH(xy1);
  y1 = GET_NIBBLE_LOW(xy1);
  x2 = GET_NIBBLE_HIGH(xy2);
  y2 = GET_NIBBLE_LOW(xy2);
  /* Scale the points up if needed */
  if(size > 15){
    int scale = size / 15;
    x1 = x1 * scale;
    y1 = y1 * scale;
    x2 = x2 * scale;
    y2 = y2 * scale;
  }
  /* Scale the points down if needed */
  if(size < 15){
    int scale = 15 / size;
    x1 = x1 / scale;
    y1 = y1 / scale;
    x2 = x2 / scale;
    y2 = y2 / scale;
  }
  /* Draw raw line */
  pt_draw_raw_line(x1, y1, x2, y2, buff, size);
}

void pt_draw_curved_line(UINT8 xy1, UINT8 cxy, UINT8 xy2, UINT8* buff, unsigned int size){
  int x1, y1, x2, y2, cx, cy, xa, ya, xb, yb, px, py, x, y;
  /* Get line variables */
  x1 = GET_NIBBLE_HIGH(xy1);
  y1 = GET_NIBBLE_LOW(xy1);
  x2 = GET_NIBBLE_HIGH(xy2);
  y2 = GET_NIBBLE_LOW(xy2);
  cx = GET_NIBBLE_HIGH(cxy);
  cy = GET_NIBBLE_LOW(cxy);
  /* Scale the points up if needed */
  if(size > 15){
    int scale = size / 15;
    x1 = x1 * scale;
    y1 = y1 * scale;
    x2 = x2 * scale;
    y2 = y2 * scale;
    cx = cx * scale;
    cy = cy * scale;
  }
  /* Scale the points down if needed */
  if(size < 15){
    int scale = 15 / size;
    x1 = x1 / scale;
    y1 = y1 / scale;
    x2 = x2 / scale;
    y2 = y2 / scale;
    cx = cx / scale;
    cy = cy / scale;
  }
  /* Draw quadratic curve */
  px = x1;
  py = y1;
  for(float i = SEG_SIZE; i <= 1.0f; i += SEG_SIZE){
    /* Support points */
    xa = GET_POINT(x1, cx, i);
    ya = GET_POINT(y1, cy, i);
    xb = GET_POINT(cx, x2, i);
    yb = GET_POINT(cy, y2, i);
    /* Draw points */
    x = GET_POINT(xa, xb, i);
    y = GET_POINT(ya, yb, i);
    /* Draw segment */
    pt_draw_raw_line(px, py, x, y, buff, size);
    /* Save current segment */
    px = x;
    py = y;
  }
}

void pt_draw_create_bitmap(UINT8* desc, unsigned int len, UINT8* buff, unsigned int size){
  /* TODO: Basic sanity checks before starting. */
  /* Loop over the description */
  for(unsigned int z = 0; z < len; z++){
    /* Get line properties */
    UINT8 shape = desc[z] & SHAPE_MASK;
    UINT8 shapeLen = (desc[z] & LEN_MASK) + 1;
    /* Generate shape */
    switch(shape){
      case LINE:
        /* TODO: Test if line is closed. */
        /* TODO: Handle fill condition. */
        for(unsigned int i = 0; i < shapeLen; i++){
          ++z;
          pt_draw_simple_line(desc[z], desc[z + 1], buff, size);
        }
        ++z;
        break;
      case CURV:
        /* TODO: Test if line is closed. */
        /* TODO: Handle fill condition. */
        pt_draw_curved_line(desc[z + 1], desc[z + 2], desc[z + 3], buff, size);
        for(unsigned int i = 1; i < shapeLen; i++){
          z += 2;
          pt_draw_curved_line(desc[z + 1], desc[z + 2], desc[z + 3], buff, size);
        }
        z += 3;
        break;
    }
  }
}
