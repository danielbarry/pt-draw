#include "pt-draw.h"

#include <stdlib.h>

#define GET_POINT(i,j,p) ( i + ((j - i) * p) )

void pt_draw_simple_line(UINT8 xy1, UINT8 xy2, UINT8* buff, unsigned int size){
  int x1, y1, x2, y2, dx, dy, sx, sy, err, e2;
  /* Get line variables */
  x1 = (xy1 & 0b11110000) >> 4;
  y1 = xy1 & 0b1111;
  x2 = (xy2 & 0b11110000) >> 4;
  y2 = xy2 & 0b1111;
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

void pt_draw_curved_line(UINT8 xy1, UINT8 xy2, UINT8 cxy, UINT8* buff, unsigned int size){
  int x1, y1, x2, y2, cx, cy, xa, ya, xb, yb, x, y;
  /* Get line variables */
  x1 = (xy1 & 0b11110000) >> 4;
  y1 = xy1 & 0b1111;
  x2 = (xy2 & 0b11110000) >> 4;
  y2 = xy2 & 0b1111;
  cx = (cxy & 0b11110000) >> 4;
  cy = cxy & 0b1111;
  printf("(%i,%i) (%i,%i) (%i,%i)", x1, y1, x2, y2, cx, cy); // TODO
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
  for(float i = 0; i < 1; i += 0.01f){
    /* Support points */
    xa = GET_POINT(x1, cx, i);
    ya = GET_POINT(y1, cy, i);
    xb = GET_POINT(cx, x2, i);
    yb = GET_POINT(cy, y2, i);
    /* Draw points */
    x = GET_POINT(xa, xb, i);
    y = GET_POINT(ya, yb, i);
    /* Set pixel */
    int p = x + (y * size);
    buff[p / 8] |= 0b1 << (7 - (p % 8));
  }
}

void pt_draw_create_bitmap(UINT8* desc, unsigned int len, UINT8* buff, unsigned int size){
  /* TODO: Basic sanity checks before starting. */
  /* Loop over the description */
  for(unsigned int z = 0; z < len; z++){
    /* Get line properties */
    UINT8 shape = desc[z] & SHAPE_MASK;
    UINT8 shapeLen = ((desc[z] & LEN_MASK) >> 4) + 1;
    /* Generate shape */
    switch(shape){
      case LIN_SIMP:
        pt_draw_simple_line(desc[z + 1], desc[z + 2], buff, size);
        z += 2;
        break;
      case LIN_CURV:
        pt_draw_curved_line(desc[z + 1], desc[z + 2], desc[z + 3], buff, size);
        z += 3;
        break;
      case SEQ_SIMP:
        /* TODO: Handle fill condition. */
        for(unsigned int i = 0; i < shapeLen; i++){
          ++z;
          pt_draw_simple_line(desc[z], desc[z + 1], buff, size);
        }
        break;
      case SEQ_CURV:
        /* TODO: Process sequenced curve. */
        /* TODO: Handle fill condition. */
        break;
    }
  }
}
