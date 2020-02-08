#include "pt-draw.c"

#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define ASSERT(x,s) {x ? ++pass : ++fail; printf("  %s %s::%i %s\n", (x ? "[ OK ]  " : "  [FAIL]"), __FUNCTION__, __LINE__, s);}

#define BUFFER_SIZE 65536

int pass;
int fail;

/**
 * ppm()
 *
 * Print a binary array to disk.
 *
 * @param fn The filename to be saved to disk.
 * @param data The pointer to the buffer array.
 * @param size The size (width and height) of the data in the buffer.
 **/
void ppm(char* fn, UINT8* data, unsigned int size){
  FILE* f = fopen(fn, "w");
  fprintf(f, "P1\n%i %i\n", size, size);
  for(unsigned int i = 0; i < size * size; i++){
    UINT8 r = data[i / 8] & (0b1 << (7 - (i % 8)));
    char c[1] = { r ? '1' : '0' };
    fwrite(c, 1, 1, f);
  }
  fclose(f);
}

/**
 * main()
 *
 * The main entry method for the tests.
 *
 * @return The exit code of the tests.
 **/
int main(){
  /* Setup global variables */
  pass = fail = 0;
  /* Create test data */
  UINT8 buff[BUFFER_SIZE];
  UINT8 diagLineA[3] = {LIN_SIMP, 0x00, 0xFF};
  UINT8 diagLineB[3] = {LIN_SIMP, 0xF0, 0x0F};
  UINT8 cross[6] = {LIN_SIMP, 0x22, 0xDD, LIN_SIMP, 0xD2, 0x2D};
  UINT8 square[6] = {SEQ_SIMP | ((4 - 1) << 4), 0x22, 0xD2, 0xDD, 0x2D, 0x22};
  UINT8 squareCross[12] = {LIN_SIMP, 0x22, 0xDD, LIN_SIMP, 0xD2, 0x2D, SEQ_SIMP | ((4 - 1) << 4), 0x22, 0xD2, 0xDD, 0x2D, 0x22};
  UINT8 curve[4] = {LIN_CURV, 0x00, 0xF0, 0xFF};
  UINT8 letterS[8] = {SEQ_CURV | ((3 - 1) << 4), 0xD2, 0x00, 0x26, 0x77, 0xD8, 0xFF, 0x2D};
  UINT8 dollar[14] = {SEQ_CURV | ((3 - 1) << 4), 0xD2, 0x00, 0x26, 0x77, 0xD8, 0xFF, 0x2D, LIN_SIMP, 0x60, 0x6F, LIN_SIMP, 0x90, 0x9F};
  /* -- Draw small simple line (a) -- */
  memset(buff, 0, BUFFER_SIZE);
  pt_draw_create_bitmap(diagLineA, 3, buff, 4);
  ppm("diag-line-a-4.ppm", buff, 4);
  /* -- Draw simple line (a) -- */
  memset(buff, 0, BUFFER_SIZE);
  pt_draw_create_bitmap(diagLineA, 3, buff, 16);
  ppm("diag-line-a-16.ppm", buff, 16);
  /* -- Draw large simple line (a) -- */
  memset(buff, 0, BUFFER_SIZE);
  pt_draw_create_bitmap(diagLineA, 3, buff, 256);
  ppm("diag-line-a-256.ppm", buff, 256);
  /* -- Draw large simple line (b) -- */
  memset(buff, 0, BUFFER_SIZE);
  pt_draw_create_bitmap(diagLineB, 3, buff, 256);
  ppm("diag-line-b-256.ppm", buff, 256);
  /* -- Draw cross -- */
  memset(buff, 0, BUFFER_SIZE);
  pt_draw_create_bitmap(cross, 6, buff, 256);
  ppm("cross.ppm", buff, 256);
  /* -- Draw square -- */
  memset(buff, 0, BUFFER_SIZE);
  pt_draw_create_bitmap(square, 6, buff, 256);
  ppm("square.ppm", buff, 256);
  /* -- Draw square cross -- */
  memset(buff, 0, BUFFER_SIZE);
  pt_draw_create_bitmap(squareCross, 12, buff, 256);
  ppm("square-cross.ppm", buff, 256);
  /* -- Draw simple curve -- */
  memset(buff, 0, BUFFER_SIZE);
  pt_draw_create_bitmap(curve, 4, buff, 256);
  ppm("curve.ppm", buff, 256);
  /* -- Draw letter S -- */
  memset(buff, 0, BUFFER_SIZE);
  pt_draw_create_bitmap(letterS, 8, buff, 256);
  ppm("letter-s.ppm", buff, 256);
  /* -- Draw dollar -- */
  memset(buff, 0, BUFFER_SIZE);
  pt_draw_create_bitmap(dollar, 14, buff, 256);
  ppm("dollar.ppm", buff, 256);
  /* Print result */
  printf("%i / %i PASS\n", pass, pass + fail);
  printf("%i / %i FAIL\n", fail, pass + fail);
  /* Test was successful */
  return fail <= 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
