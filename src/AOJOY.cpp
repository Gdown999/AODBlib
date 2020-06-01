#include <Arduino.h>
#include <math.h>
#include <Keyboard.h>
#include <Mouse.h>
#include "AOJOY.h"
AOJOY::AOJOY(byte xPin, byte yPin, byte overlap_temp = 0, byte halfLine_temp = 0):
analogPin{xPin,yPin}{
  resolution = 1023 * 0.5;
  idleRange = 80;
  upperLimit = 600;
  overlapZone = 0;
  loadingNum = 0;
  halfLine = 0;
  overlapZone = 0;
  halfLine = 0;
  overlapZone = overlap_temp * 0.5;
  halfLine = halfLine_temp;
  keyMap = new word[AOKEY::layerNum * 5];
}


void AOJOY::begin(void){
  for (byte i = 0 ; i < 2 ; i++){
    pinMode(analogPin[i], INPUT);
  }
  //ADCSRB = ADCSRB & 127;
  //ADCSRB = ADCSRB | 128;
  ADCSRB = ADCSRB | B10000000;
  ADCSRA = ADCSRA & B11111000;
  ADCSRA = ADCSRA | B00000101;
}


void AOJOY::update(void){
  //アナログ値を直交座標に変換
  for (byte i = 0 ; i < 2 ; i++) {
    char is_plus_or_minus;
    analogValue[i] = analogValue[i] * 0.9 + (analogRead(analogPin[i]) - resolution) * 0.1;
    is_plus_or_minus = (analogValue[i] > 0) ? 1 : -1;
    if (abs(analogValue[i]) > idleRange) {
      corrValue[i] = (abs(analogValue[i]) - idleRange) * is_plus_or_minus;
      corrValue[i] = constrain(corrValue[i], (upperLimit - idleRange) * -1, (upperLimit - idleRange));
    }else{
      corrValue[i] = 0;
    }
    corrValue[i] = map(corrValue[i], 0, 420, 0, 100);
  }
  //ステータス初期化
  beforeState = currentState;
  currentState = 0;
  //対角線演算
  polarValue[1] = sqrt((sq(corrValue[0]) + sq(corrValue[1])));
  //半押し処理
  if(polarValue[1] < halfLine && polarValue[1])currentState = currentState | 1 << 4;


  if (abs(corrValue[0]) && abs(corrValue[1])) {
    //直交座標を極座標に変換
    polarValue[0] = _atan2(corrValue[1],corrValue[0]) * 0.01;
    //LEFT or RIGHT
    if (abs(polarValue[0]) < (45 + overlapZone)) {//LEFT
      currentState = currentState | 1 << 1;
    }else if (abs(polarValue[0]) > (135 - overlapZone)) {//RIGHT
      currentState = currentState | 1 << 3;
    }
    //UP or DOWN
    if ((45 - overlapZone) < abs(polarValue[0]) && abs(polarValue[0]) < (135 + overlapZone)) {
      if (polarValue[0] > 0) {//UP
        currentState = currentState | 1;
      }else{//DOWN
        currentState = currentState | 1 << 2;
      }
    }


  }else if (abs(corrValue[0])) {
    //LEFT or RIGHT
    if (corrValue[0] > 0) {//LEFT
      currentState = currentState | 1 << 1;
    }else{//RIGHT
      currentState = currentState | 1 << 3;
    }
    //UP or DOWN
  }else if(abs(corrValue[1])){
    if (corrValue[1] > 0) {//UP
      currentState = currentState | 1;
    }else{//DOWN
      currentState = currentState | 1 << 2;
    }
  }
}

void AOJOY::loadKeyMap(word* temp){
  for (word i = 0; i < 5; i++) {
    keyMap[i] = pgm_read_word(temp + i);
  }
}

void AOJOY::test(void){
  Serial.print(polarValue[0]);
  Serial.print(F(":"));
  Serial.print(polarValue[1]);
  Serial.print(F(" : "));
  Serial.print(analogValue[0]);
  Serial.print(F(":"));
  Serial.print(analogValue[1]);
  Serial.print(F(" : "));
  Serial.print(currentState,BIN);
  Serial.println(F(" "));
}

bool AOJOY::isLoading(void){//読み込み中か
  if (loadingNum < 5 - 1) {
    loadingNum++;
    return 1;
  }else{
    loadingNum = 0;
    return 0;
  }
}

bool AOJOY::isPressed(void){//押されたか
  if ((currentState >> loadingNum & 1) && !(beforeState >> loadingNum & 1)) {
    return 1;
  }else{
    return 0;
  }
}

bool AOJOY::isReleased(void){//離されたか
  if (!(currentState >> loadingNum & 1) && (beforeState >> loadingNum & 1)) {
    return 1;
  }else{
    return 0;
  }
}

bool AOJOY::isChanged(void){//変化があったか
  if ((currentState >> loadingNum & 1) != (currentState >> loadingNum & 1)) {
    return 1;
  }else{
    return 0;
  }
}

bool AOJOY::isPressing(void){//押しているか
  return (currentState >> loadingNum & 1) ? 1 : 0;
}

void AOJOY::keyPress(void){//押す
  AOKEY::keyPress(keyMap[loadingNum]);
}

void AOJOY::keyRelease(void){//離す
  AOKEY::keyRelease(keyMap[loadingNum]);
}

word AOJOY::getKeyCode(void){
  return keyMap[loadingNum];
}
