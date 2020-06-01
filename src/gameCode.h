#ifndef INCLUDED_GAMECODE_h_
#define INCLUDED_GAMECODE_h_
#include <Keyboard.h>
#include <Mouse.h>
#include "defKey.h"
const byte gameCode_Num = 1;
const char gameCode[gameCode_Num][5] PROGMEM = {//CC
  //0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
  "OSU" ,//0
};

//0x300↓
#define GC_ALTW 0x400
#define GC_ALTA 0x401
#define GC_ALTS 0x402
#define GC_ALTD 0x403

inline void gameCase_press(byte temp){
  switch (temp) {
    case SFT8(GC_ALTW):Keyboard.press(KC_ALT);Keyboard.press(KC_W);break;
    case SFT8(GC_ALTA):Keyboard.press(KC_ALT);Keyboard.press(KC_A);break;
    case SFT8(GC_ALTS):Keyboard.press(KC_ALT);Keyboard.press(KC_S);break;
    case SFT8(GC_ALTD):Keyboard.press(KC_ALT);Keyboard.press(KC_D);break;
  }
}

inline void gameCase_release(byte temp){
  switch (temp) {
    case SFT8(GC_ALTW):Keyboard.release(KC_ALT);Keyboard.release(KC_W);break;
    case SFT8(GC_ALTA):Keyboard.release(KC_ALT);Keyboard.release(KC_A);break;
    case SFT8(GC_ALTS):Keyboard.release(KC_ALT);Keyboard.release(KC_S);break;
    case SFT8(GC_ALTD):Keyboard.release(KC_ALT);Keyboard.release(KC_D);break;
  }
}
#endif
