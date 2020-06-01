#ifndef INCLUDED_LOOPTIME_h_
#define INCLUDED_LOOPTIME_h_

class loopTime{
public:
  //コンストラクタ
  loopTime();
  //チェックポイント
  void loopTimeCheck(void);
  //シリアル出力回数設定
  void setCount(int countTemp);
  //1周のタイムを出力
  unsigned long getTime(void);
  //hzを出力
  unsigned int getHz(void);
private:
  byte instanceNum;
  byte checkCount;

  unsigned long time;
  unsigned long loopTimeCount;
  unsigned int hz;
  int count;

  bool boolSerialOut;
};

//チェックポイント
inline void loopTime::loopTimeCheck(void){
  checkCount++;
  if (instanceNum == checkCount) {
    if (boolSerialOut) {
      if (count > 0 || count == -1) {
        Serial.print(hz); Serial.print("Hz--"); Serial.print(loopTimeCount); Serial.println(F("ns"));
        if(count != -1)count -= 1;
      }
      boolSerialOut = 0;
      time = micros();

    }else{
      loopTimeCount = micros() - time;
      hz = abs(1000000/loopTimeCount);
      boolSerialOut = 1;
    }
  }
  checkCount = 0;
}

#endif
