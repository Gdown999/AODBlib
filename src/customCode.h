#ifndef INCLUDED_CUSTOMCODE_h_
#define INCLUDED_CUSTOMCODE_h_
#include <Keyboard.h>
#include <Mouse.h>
#include "defKey.h"
const byte customCode_Num = 1;
const char customCode[customCode_Num][5] PROGMEM = {//CC
  //0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
  "OSU" ,//0
};

//0x300↓
#define CC_CTLZ 0x300
#define CC_CTLX 0x301
#define CC_CTLC 0x302
#define CC_CTLV 0x303
#define CC_CTLY 0x304
#define CC_CTLD 0x305
#define CC_CTLF 0x306
#define CC_CAP  0x307

inline void customCase_press(byte temp){
  switch (temp) {
    case SFT8(CC_CTLZ):Keyboard.press(KC_LCTL);Keyboard.press(KC_Z);break;
    case SFT8(CC_CTLX):Keyboard.press(KC_LCTL);Keyboard.press(KC_X);break;
    case SFT8(CC_CTLC):Keyboard.press(KC_LCTL);Keyboard.press(KC_C);break;
    case SFT8(CC_CTLV):Keyboard.press(KC_LCTL);Keyboard.press(KC_V);break;
    case SFT8(CC_CTLY):Keyboard.press(KC_LCTL);Keyboard.press(KC_Y);break;
    case SFT8(CC_CTLD):Keyboard.press(KC_LCTL);Keyboard.press(KC_D);break;
    case SFT8(CC_CTLF):Keyboard.press(KC_LCTL);Keyboard.press(KC_F);break;
    case SFT8(CC_CAP):Keyboard.press(KC_GUI);Keyboard.press(KC_SFT);Keyboard.press(KC_S);break;
  }
}

inline void customCase_release(byte temp){
  switch (temp) {
    case SFT8(CC_CTLZ):Keyboard.release(KC_Z);Keyboard.release(KC_LCTL);break;
    case SFT8(CC_CTLX):Keyboard.release(KC_X);Keyboard.release(KC_LCTL);break;
    case SFT8(CC_CTLC):Keyboard.release(KC_C);Keyboard.release(KC_LCTL);break;
    case SFT8(CC_CTLV):Keyboard.release(KC_V);Keyboard.release(KC_LCTL);break;
    case SFT8(CC_CTLY):Keyboard.release(KC_Y);Keyboard.release(KC_LCTL);break;
    case SFT8(CC_CTLD):Keyboard.release(KC_D);Keyboard.release(KC_LCTL);break;
    case SFT8(CC_CTLF):Keyboard.release(KC_F);Keyboard.release(KC_LCTL);break;
    case SFT8(CC_CAP):Keyboard.release(KC_S);Keyboard.release(KC_SFT);Keyboard.release(KC_GUI);break;
  }
}
#endif
