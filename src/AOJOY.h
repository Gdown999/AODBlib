#ifndef INCLUDED_AOJOY_h_
#define INCLUDED_AOJOY_h_
#include "AOKEY.h"
class AOJOY : public AOKEY{
public:
  word* keyMap;
private:
  const byte analogPin[2];// 0:X 1:Y
  int resolution;//分解能
  byte idleRange;//無効域
  int upperLimit;//上限値
  int analogValue[2];//アナログ値
  int corrValue[2];//補正値

  int polarValue[2];//極座標値
  byte overlapZone;//重なり域

  byte loadingNum;//読み込み中のキーコード
  byte halfLine;//半押しの判定値
  byte currentState; //現在のキーの状態を保持する変数
  byte beforeState; //前回のキーの状態を保持する変数
public:
  AOJOY(byte xPin, byte yPin, byte overlap_temp = 0, byte halfLine_temp = 0);
  void begin(void);
  void update(void);//ピンの読み取り
  void loadKeyMap(word* temp);

  void test(void);

  bool isLoading(void);//読み込み中か

  bool isPressed(void);//押されたか
  bool isReleased(void);//離されたか
  bool isPressing(void);//押しているか
  bool isChanged(void);//変化があったか

  void keyPress(void);//キーを押す
  void keyRelease(void);//キーを離す

  word getKeyCode(void);//現在のキーコード
};

inline int16_t _atan2(int16_t _y, int16_t _x) {//by https://garchiving.com/approximation-atan2/
  int16_t x = abs(_x);
  int16_t y = abs(_y);
  float   z;
  bool    c;

  c = y < x;
  if (c)z = (float)y / x;
  else  z = (float)x / y;

  int16_t a;
  a = z * (-1556 * z + 6072);                     //2次曲線近似
  //a = z * (z * (-448 * z - 954) + 5894);          //3次曲線近似
  //a = z * (z * (z * (829 * z - 2011) - 58) + 5741); //4次曲線近似

  if (c) {
    if (_x > 0) {
      if (_y < 0)a *= -1;
    }
    if (_x < 0) {
      if (_y > 0)a = 18000 - a;
      if (_y < 0)a = a - 18000;
    }
  }

  if (!c) {
    if (_x > 0) {
      if (_y > 0) a = 9000 - a;
      if (_y < 0) a = a - 9000;
    }
    if (_x < 0) {
      if (_y > 0) a = a + 9000;
      if (_y < 0) a = -a - 9000;
    }
  }

  return a;
}
#endif
