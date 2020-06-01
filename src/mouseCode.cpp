#include <Mouse.h>
#include "mouseCode.h"
#include "mouseRuler.h"
mouseRuler MoR;
void mouseCase_press(byte temp){
  switch (temp) {
    case SFT8(MC_LC):Mouse.press(MOUSE_LEFT); break;
    case SFT8(MC_RC):Mouse.press(MOUSE_RIGHT); break;
    case SFT8(MC_MC):Mouse.press(MOUSE_MIDDLE); break;
    case SFT8(MC_HU):Mouse.move(0, 0, +1);break;
    case SFT8(MC_HD):Mouse.move(0, 0, -1);break;
    case SFT8(MC_P):break;
    case SFT8(MC_U1):MoR.move(0,-1);break;
    case SFT8(MC_U10):MoR.move(0,-20);break;
    case SFT8(MC_U100):MoR.move(0,-200);break;
    case SFT8(MC_D1):MoR.move(0,1);break;
    case SFT8(MC_D10):MoR.move(0,20);break;
    case SFT8(MC_D100):MoR.move(0,200);break;
    case SFT8(MC_L1):MoR.move(-1,0);break;
    case SFT8(MC_L10):MoR.move(-20,0);break;
    case SFT8(MC_L100):MoR.move(-200,0);break;
    case SFT8(MC_R1):MoR.move(1,0);break;
    case SFT8(MC_R10):MoR.move(20,0);break;
    case SFT8(MC_R100):MoR.move(200,0);break;
    case SFT8(MC_RET):MoR.reset();break;
    case SFT8(MC_OUT):Serial.print(F("X:"));Serial.println(MoR.getXCount());
                      Serial.print(F("Y:"));Serial.println(MoR.getYCount());break;
  }
}

void mouseCase_release(byte temp){
  switch (temp) {
    case SFT8(MC_LC):Mouse.release(MOUSE_LEFT); break;
    case SFT8(MC_RC):Mouse.release(MOUSE_RIGHT); break;
    case SFT8(MC_MC):Mouse.release(MOUSE_MIDDLE); break;
    case SFT8(MC_HU):break;
    case SFT8(MC_HD):break;
    case SFT8(MC_P):break;
    case SFT8(MC_U1):break;
    case SFT8(MC_U10):break;
    case SFT8(MC_U100):break;
    case SFT8(MC_D1):break;
    case SFT8(MC_D10):break;
    case SFT8(MC_D100):break;
    case SFT8(MC_L1):break;
    case SFT8(MC_L10):break;
    case SFT8(MC_L100):break;
    case SFT8(MC_R1):break;
    case SFT8(MC_R10):break;
    case SFT8(MC_R100):break;
  }
}
