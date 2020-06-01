#include "Arduino.h"
byte interpolationProcess(byte temp){
  temp += 32;
  if (temp > 0x40) {
    temp += 26;
    if (temp > 0x87) {
      temp += 56;
      switch (temp) {
        case 0xC0:temp = 0xB0;break;//ENT
        case 0xCE:temp = 0xB1;break;//ESC
        case 0xCF:temp = 0xB2;break;//BSPC
        case 0xD0:temp = 0xB3;break;//TAB
      }
    }
  }
  return temp;
}
