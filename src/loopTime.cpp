#include <Arduino.h>
#include "loopTime.h"
//コンストラクタ
loopTime::loopTime(void){
  if (!instanceNum) {
    time = 0;
    loopTimeCount = 0;
    hz = 0;
    count = 0;
    boolSerialOut = 0;
  }
  instanceNum += 1;
}

//シリアル出力回数設定
void loopTime::setCount(int countTemp){
  count = countTemp;
}

//1周のタイムを出力
unsigned long loopTime::getTime(void){
  return loopTimeCount;
}

//hzを出力
unsigned int loopTime::getHz(void){
  return hz;
}
