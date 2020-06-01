#ifndef INCLUDED_AOKEY_h_
#define INCLUDED_AOKEY_h_
#include "mouseCode.h"
#include "customCode.h"
#include "gameCode.h"
class AOKEY{
public:
  void keyPress(word temp);//キーを押す(マニュアル)
  void keyRelease(word temp);//キーを離す(マニュアル)
protected:
  AOKEY(void);
  static byte currentLayer; //現在のレイヤー
  static byte layerNum; //レイヤーの数
private:
  static byte instanceNum;//インスタンスの数
  static byte updateCycleNum;//update実行回数
  static word modiState[2];
  void update(void);
  void soloKeyPress(word temp);//キーを押す(キーコードのみ)(内部処理)(マニュアル)
  void soloKeyRelease(word temp);//キーを離す(キーコードのみ)(内部処理)(マニュアル)
};
//////////////////////////////////////////////////////////////
//↓同時押し
#define LSFT(KC) ((1 << 11) + KC)
#define S(KC) ((1 << 11) + KC)
#define RSFT(KC) ((2 << 11) + KC)
#define LCTL(KC) ((3 << 11) + KC)
#define C(KC) ((3 << 11) + KC)
#define RCTL(KC) ((4 << 11) + KC)
#define LALT(KC) ((5 << 11) + KC)
#define A(KC) ((5 << 11) + KC)
#define RALT(KC) ((6 << 11) + KC)
#define LGUI(KC) ((7 << 11) + KC)
#define G(KC) ((7 << 11) + KC)
#define RGUI(KC) ((8 << 11) + KC)
#define HYPR(KC) ((9 << 11) + KC)
#define MEH(KC) ((10 << 11) + KC)
#define LCAG(KC) ((11 << 11) + KC)
//タップでKC、同時押しでmodi
#define CTL_T(KC)((12 << 11) + KC)
#define C_T(KC)((12 << 11) + KC)
#define SFT_T(KC)((13 << 11) + KC)
#define S_T(KC)((13 << 11) + KC)
#define ALT_T(KC)((14 << 11) + KC)
#define A_T(KC)((14 << 11) + KC)
#define GUI_T(KC)((15 << 11) + KC)
#define G_T(KC)((15 << 11) + KC)
#define ALL_T(KC)((16 << 11) + KC)
#define MEH_T(KC)((17 << 11) + KC)
#define LCAG_T(KC)((18 << 11) + KC)
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
inline byte layerCase_press(byte temp){
  switch (temp) {
    case SFT8(LAY_0):return 0;
    case SFT8(LAY_1):return 1;
    case SFT8(LAY_2):return 2;
    case SFT8(LAY_3):return 3;
    case SFT8(LAY_4):return 4;
    case SFT8(LAY_5):return 5;
    case SFT8(LAY_6):return 6;
    case SFT8(LAY_7):return 7;
    case SFT8(LAY_8):return 8;
    case SFT8(LAY_9):return 9;
    case SFT8(LAY_10):return 10;
    case SFT8(LAY_11):return 11;
    case SFT8(LAY_12):return 12;
    case SFT8(LAY_13):return 13;
    case SFT8(LAY_14):return 14;
    case SFT8(LAY_15):return 15;

    case SFT8(LAY_S1):return 1;
    case SFT8(LAY_S2):return 2;
    case SFT8(LAY_S3):return 3;
    case SFT8(LAY_S4):return 4;
    case SFT8(LAY_S5):return 5;
    case SFT8(LAY_S6):return 6;
    case SFT8(LAY_S7):return 7;
    case SFT8(LAY_S8):return 8;
    case SFT8(LAY_S9):return 9;
    case SFT8(LAY_S10):return 10;
    case SFT8(LAY_S11):return 11;
    case SFT8(LAY_S12):return 12;
    case SFT8(LAY_S13):return 13;
    case SFT8(LAY_S14):return 14;
    case SFT8(LAY_S15):return 15;
  }
}
inline byte layerCase_release(byte temp){
  switch (temp) {
    case SFT8(LAY_S1):return 1;
    case SFT8(LAY_S2):return 2;
    case SFT8(LAY_S3):return 3;
    case SFT8(LAY_S4):return 4;
    case SFT8(LAY_S5):return 5;
    case SFT8(LAY_S6):return 6;
    case SFT8(LAY_S7):return 7;
    case SFT8(LAY_S8):return 8;
    case SFT8(LAY_S9):return 9;
    case SFT8(LAY_S10):return 10;
    case SFT8(LAY_S11):return 11;
    case SFT8(LAY_S12):return 12;
    case SFT8(LAY_S13):return 13;
    case SFT8(LAY_S14):return 14;
    case SFT8(LAY_S15):return 15;
    default: return 0;
  }
}
#endif
