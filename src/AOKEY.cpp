#include <Arduino.h>
#include <Keyboard.h>
#include "AOKEY.h"

byte AOKEY::currentLayer;
byte AOKEY::layerNum;
byte AOKEY::instanceNum;
byte AOKEY::updateCycleNum;;
word AOKEY::modiState[2];

AOKEY::AOKEY(void){
  modiState[0] = 0;
  modiState[1] = 0;
  currentLayer = 0;
  instanceNum++;
}

// void AOKEY::update(void){
//   if (!updateCycleNum) {
//     LoopTime.loopTimeCheck();
//   }
//   updateCycleNum++;
//   if (!(updateCycleNum < instanceNum)) {
//     updateCycleNum = 0;
//   }
// }

void AOKEY::soloKeyPress(word temp){
  switch (temp >> 8 & 0b00000111) {

    case 0: Keyboard.press(temp & 0xFF);break;
    case 1: mouseCase_press(temp & 0xFF);break;
    case 2: currentLayer = layerCase_press(temp & 0xFF);break;
    case 3: customCase_press(temp & 0xFF);break;
    case 4: gameCase_press(temp & 0xFF);break;
  }
}
void AOKEY::soloKeyRelease(word temp){
  switch (temp >> 8 & 0b00000111) {

    case 0: Keyboard.release(temp & 0xFF);break;
    case 1: mouseCase_release(temp & 0xFF);break;
    case 2: currentLayer = layerCase_release(temp & 0xFF);break;
    case 3: customCase_release(temp & 0xFF);break;
    case 4: gameCase_release(temp & 0xFF);break;
  }
}

void AOKEY::keyPress(word temp){//押す
  if(modiState[0] & 0b0000000000000001){
    modiState[1] = modiState[1] | 0b0000000000000001;
    Keyboard.press(KC_LCTL);
  }
  if(modiState[0] & 0b0000000000000010){
    modiState[1] = modiState[1] | 0b0000000000000010;
    Keyboard.press(KC_LSFT);
  }
  if(modiState[0] & 0b0000000000000100){
    modiState[1] = modiState[1] | 0b0000000000000100;
    Keyboard.press(KC_LALT);
  }
  if(modiState[0] & 0b0000000000001000){
    modiState[1] = modiState[1] | 0b0000000000001000;
    Keyboard.press(KC_LGUI);
  }
  if(modiState[0] & 0b0000000000010000){
    modiState[1] = modiState[1] | 0b0000000000010000;
    Keyboard.press(KC_LCTL);
    Keyboard.press(KC_LSFT);
    Keyboard.press(KC_LALT);
    Keyboard.press(KC_LGUI);
  }
  if(modiState[0] & 0b0000000000100000){
    modiState[1] = modiState[1] | 0b0000000000100000;
    Keyboard.press(KC_LCTL);
    Keyboard.press(KC_LSFT);
    Keyboard.press(KC_LALT);
  }
  if(modiState[0] & 0b0000000001000000){
    modiState[1] = modiState[1] | 0b0000000001000000;
    Keyboard.press(KC_LCTL);
    Keyboard.press(KC_LALT);
    Keyboard.press(KC_LGUI);
  }
  switch (temp >> 11 & 0b00011111) {
    case 1:Keyboard.press(KC_LSFT);break;
    case 2:Keyboard.press(KC_RSFT);break;
    case 3:Keyboard.press(KC_LCTL);break;
    case 4:Keyboard.press(KC_RCTL);break;
    case 5:Keyboard.press(KC_LALT);break;
    case 6:Keyboard.press(KC_RALT);break;
    case 7:Keyboard.press(KC_LGUI);break;
    case 8:Keyboard.press(KC_RGUI);break;
    case 9:Keyboard.press(KC_LCTL);Keyboard.press(KC_LSFT);
            Keyboard.press(KC_LALT);Keyboard.press(KC_LGUI);break;
    case 10:Keyboard.press(KC_LCTL);Keyboard.press(KC_LSFT);Keyboard.press(KC_LALT);break;
    case 11:Keyboard.press(KC_LCTL);Keyboard.press(KC_LALT);Keyboard.press(KC_LGUI);break;
    case 12:modiState[0] = modiState[0] | 0b0000000000000001;break;//CTL
    case 13:modiState[0] = modiState[0] | 0b0000000000000010;break;//SFT
    case 14:modiState[0] = modiState[0] | 0b0000000000000100;break;//ALT
    case 15:modiState[0] = modiState[0] | 0b0000000000001000;break;//GUI
    case 16:modiState[0] = modiState[0] | 0b0000000000010000;break;//ALL
    case 17:modiState[0] = modiState[0] | 0b0000000000100000;break;//MEH
    case 18:modiState[0] = modiState[0] | 0b0000000001000000;break;//LCAG
  }
  if((temp >> 11 & 0b00011111) < 12){
    AOKEY::soloKeyPress(temp);
  }
}

void AOKEY::keyRelease(word temp){//離す
  if((temp >> 11 & 0b00011111) < 12){
    AOKEY::soloKeyRelease(temp);
  }
  switch (temp >> 11 & 0b00011111) {
    case 1:Keyboard.release(KC_LSFT);break;
    case 2:Keyboard.release(KC_RSFT);break;
    case 3:Keyboard.release(KC_LCTL);break;
    case 4:Keyboard.release(KC_RCTL);break;
    case 5:Keyboard.release(KC_LALT);break;
    case 6:Keyboard.release(KC_RALT);break;
    case 7:Keyboard.release(KC_LGUI);break;
    case 8:Keyboard.release(KC_RGUI);break;
    case 9:Keyboard.release(KC_LCTL);Keyboard.release(KC_LSFT);break;
            Keyboard.release(KC_LALT);Keyboard.release(KC_LGUI);break;
    case 10:Keyboard.release(KC_LCTL);Keyboard.release(KC_LSFT);Keyboard.release(KC_LALT);break;
    case 11:Keyboard.release(KC_LCTL);Keyboard.release(KC_LALT);Keyboard.release(KC_LGUI);break;
    case 12:if (modiState[1] & 0b0000000000000001) {//CTL
      modiState[0] = modiState[0] ^ 0b0000000000000001;
      modiState[1] = modiState[1] ^ 0b0000000000000001;
      Keyboard.release(KC_LCTL);
    }else if(modiState[0] & 0b0000000000000001){
      modiState[0] = modiState[0] ^ 0b0000000000000001;
      AOKEY::soloKeyPress(temp);
      AOKEY::soloKeyRelease(temp);
    }break;//CTL
    case 13:if (modiState[1] & 0b0000000000000010) {//SFT
      modiState[0] = modiState[0] ^ 0b0000000000000010;
      modiState[1] = modiState[1] ^ 0b0000000000000010;
      Keyboard.release(KC_LSFT);
    }else if(modiState[0] & 0b0000000000000010){
      modiState[0] = modiState[0] ^ 0b0000000000000010;
      AOKEY::soloKeyPress(temp);
      AOKEY::soloKeyRelease(temp);
    }break;//SFT
    case 14:if (modiState[1] & 0b0000000000000100) {//ALT
      modiState[0] = modiState[0] ^ 0b0000000000000100;
      modiState[1] = modiState[1] ^ 0b0000000000000100;
      Keyboard.release(KC_LALT);
    }else if(modiState[0] & 0b0000000000000100){
      modiState[0] = modiState[0] ^ 0b0000000000000100;
      AOKEY::soloKeyPress(temp);
      AOKEY::soloKeyRelease(temp);
    }break;//ALT
    case 15:if (modiState[1] & 0b0000000000001000) {//GUI
      modiState[0] = modiState[0] ^ 0b0000000000001000;
      modiState[1] = modiState[1] ^ 0b0000000000001000;
      Keyboard.release(KC_LGUI);
    }else if(modiState[0] & 0b0000000000001000){
      modiState[0] = modiState[0] ^ 0b0000000000001000;
      AOKEY::soloKeyPress(temp);
      AOKEY::soloKeyRelease(temp);
    }break;//GUI
    case 16:if (modiState[1] & 0b0000000000010000) {//ALL
      modiState[0] = modiState[0] ^ 0b0000000000010000;
      modiState[1] = modiState[1] ^ 0b0000000000010000;
      Keyboard.release(KC_LCTL);
      Keyboard.release(KC_LSFT);
      Keyboard.release(KC_LALT);
      Keyboard.release(KC_LGUI);
    }else if(modiState[0] & 0b0000000000010000){
      modiState[0] = modiState[0] ^ 0b0000000000010000;
      AOKEY::soloKeyPress(temp);
      AOKEY::soloKeyRelease(temp);
    }break;//ALL
    case 17:if (modiState[1] & 0b0000000000100000) {//MEH
      modiState[0] = modiState[0] ^ 0b0000000000100000;
      modiState[1] = modiState[1] ^ 0b0000000000100000;
      Keyboard.release(KC_LCTL);
      Keyboard.release(KC_LSFT);
      Keyboard.release(KC_LALT);
    }else if(modiState[0] & 0b0000000000100000){
      modiState[0] = modiState[0] ^ 0b0000000000100000;
      AOKEY::soloKeyPress(temp);
      AOKEY::soloKeyRelease(temp);
    }break;//MEH
    case 18:if (modiState[1] & 0b0000000001000000) {//LCAG
      modiState[0] = modiState[0] ^ 0b0000000001000000;
      modiState[1] = modiState[1] ^ 0b0000000001000000;
      Keyboard.release(KC_LCTL);
      Keyboard.release(KC_LALT);
      Keyboard.release(KC_LGUI);
    }else if(modiState[0] & 0b0000000001000000){
      modiState[0] = modiState[0] ^ 0b0000000001000000;
      AOKEY::soloKeyPress(temp);
      AOKEY::soloKeyRelease(temp);
    }break;//LCAG
  }
}
