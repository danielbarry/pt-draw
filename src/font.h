#include "pt-draw.h"

/**
 * font.h
 *
 * The definitions for a series of font definitions that are useful for
 * embedded devices.
 **/
#ifndef FONT_H
#define FONT_H
  #ifndef FONT_NO_UPPERCASE
    #define FONT_A_LEN 6
    UINT8 FONT_A[FONT_A_LEN] = {LINE | (4 - 1), 0x2F, 0x80, 0xDF, 0xB9, 0x69};
    #define FONT_B_LEN 8
    UINT8 FONT_B[FONT_B_LEN] = {CURV | (3 - 1), 0x5F, 0x58, 0x50, 0xF4, 0x57, 0xFB, 0x5F};
    #define FONT_C_LEN 6
    UINT8 FONT_C[FONT_C_LEN] = {CURV | (2 - 1), 0xD0, 0x20, 0x28, 0x2F, 0xDF};
  #endif
#endif
