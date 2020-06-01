#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>
#include "AODB.h"


//コンストラクタ
AODB::AODB(byte layer, byte row, byte col, bool mirror_temp = 0):
rowNum(row),colNum(col),mirror(mirror_temp),
keyMap_volume(layer * row * col),state_volume(row * col){
  AOKEY::layerNum = layer;
  pressNum = 0;
  chatteringLimit = 8000;
  keyMap = new word[keyMap_volume];
  currentState = new int[state_volume];
  beforeState = new bool[state_volume];
  rowPin = new byte[rowNum];
  colPin = new byte[colNum];
}

void AODB::test(void){
}

void AODB::setPin(byte* rowTemp, byte* colTemp){
  if (mirror) {
    for (byte i = 0; i < rowNum; i++)rowPin[i] = rowTemp[i];
    for (byte i = 0; i < colNum; i++)colPin[colNum - i - 1] = colTemp[i];
  }else{
    for (byte i = 0; i < rowNum; i++)rowPin[i] = rowTemp[i];
    for (byte i = 0; i < colNum; i++)colPin[i] = colTemp[i];
  }
}

void AODB::loadKeyMap(word* temp, byte layerNum_temp = 0){
  if (layerNum_temp < AOKEY::layerNum) {
    for (word i = 0; i < state_volume; i++) {
      keyMap[i + (layerNum_temp * state_volume)] = pgm_read_word(temp + i);
    }
  }
}

void AODB::begin(void){//初期化
  for (byte i = 0; i < colNum; i++) { //行のピンをインプットに割り当て（プルアップ抵抗あり）INPUT_PULLUP
    pinMode(colPin[i], INPUT_PULLUP);
  }
  for (byte i = 0; i < rowNum; i++) { //列のピンをアウトプットに割り当てOUTPUT
    pinMode(rowPin[i], OUTPUT);
    digitalWrite(rowPin[i], HIGH);
  }
  for (int i = 0; i < state_volume; i++) {
    currentState[i] = 0;
    beforeState[i] = 0;
  }
  Keyboard.begin(); //キーボードHIDを開始
  Mouse.begin(); //マウスHIDを開始
}

void AODB::update(void){//ピンの読み取り
  LoopTime.loopTimeCheck();
  for (byte i = 0; i < rowNum; i++) {
    //fast_digitalWrite_LOW(rowPin[i]);
    digitalWrite(rowPin[i], LOW);

    for (byte j = 0; j < colNum; j++) {
      beforeState[i * colNum + j] = (currentState[i * colNum + j] > 0) ? 1 : 0;
      //if(!fast_digitalRead(colPin[j])){
      if(!digitalRead(colPin[j])){
        if(currentState[i * colNum + j] < 0){
          if (abs(currentState[i * colNum + j]) * LoopTime.getTime() < chatteringLimit) {
            currentState[i * colNum + j]--;
            continue;
          }else{
            currentState[i * colNum + j] = 0;
          }
        }
        if(currentState[i * colNum + j] < 32767)currentState[i * colNum + j]++;

      }else{
        if(currentState[i * colNum + j] > 0){
          if (abs(currentState[i * colNum + j]) * LoopTime.getTime() < chatteringLimit) {
            currentState[i * colNum + j]++;
            continue;
          }else{
            currentState[i * colNum + j] = 0;
          }
        }
        if(currentState[i * colNum + j] > -32767)currentState[i * colNum + j]--;
      }
    }
    //fast_digitalWrite_HIGH(rowPin[i]);
    digitalWrite(rowPin[i], HIGH);
  }
}


bool AODB::isLoading(void){//読み込み中か
  if (loadingNum < state_volume - 1) {
    loadingNum++;
    return 1;
  }else{
    loadingNum = 0;
    return 0;
  }
}


bool AODB::isPressed(void){//押されたか
  if (currentState[loadingNum] > 0 && !beforeState[loadingNum]) {
    return 1;
  }else{
    return 0;
  }
}

bool AODB::isReleased(void){//離されたか
  if (currentState[loadingNum] <= 0 && beforeState[loadingNum]) {
    return 1;
  }else{
    return 0;
  }
}

bool AODB::isPressing(void){//押しているか
  return (currentState[loadingNum] > 0) ? 1 : 0;
}

bool AODB::isChanged(void){//変化があったか
  if (((currentState[loadingNum] > 0) ? 1 : 0) != ((beforeState[loadingNum] > 0) ? 1 : 0)) {
    return 1;
  }else{
    return 0;
  }
}


int AODB::isPressedNum(void){
  for (word i = 0; i < state_volume; i++) {
    if(currentState[i] > 0)return i;
  }
  return -1;
}

bool AODB::isPressing(byte row_temp, byte col_temp){
  return (currentState[(colNum * row_temp) + col_temp] > 0) ? 1 : 0;
}


void AODB::keyPress(void){//押す
  AOKEY::keyPress(keyMap[AOKEY::currentLayer * state_volume + loadingNum]);
}

void AODB::keyRelease(void){//離す
  AOKEY::keyRelease(keyMap[AOKEY::currentLayer * state_volume + loadingNum]);
}

word AODB::getKeyCode(void){
  return keyMap[AOKEY::currentLayer * state_volume + loadingNum];
}
