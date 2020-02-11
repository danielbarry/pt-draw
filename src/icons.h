#include "pt-draw.h"

/**
 * icons.h
 *
 * The definitions for a series of icons that are useful for embedded devices.
 **/
#ifndef ICONS_H
#define ICONS_H
  #ifndef ICONS_NO_BLUETOOTH
    #define ICON_BLUETOOTH_LEN 7
    UINT8 ICON_BLUETOOTH[ICON_BLUETOOTH_LEN] = {LINE | (5 - 1), 0x44, 0xCC, 0x8F, 0x80, 0xC4, 0x4C};
  #endif
  #ifndef ICONS_NO_MESSAGE
    #define ICON_MESSAGE_LEN 8
    UINT8 ICON_MESSAGE[ICON_MESSAGE_LEN] = {LINE | (6 - 1), 0x00, 0x86, 0xF0, 0x00, 0x0F, 0xFF, 0xF0};
  #endif
#endif
