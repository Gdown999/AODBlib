#ifndef INCLUDED_AODB_h_
#define INCLUDED_AODB_h_
#include "AOKEY.h"
#include "loopTime.h"
class AODB : public AOKEY{
public:
  loopTime LoopTime;

  const byte rowNum; //縦列のピン数
  const byte colNum; //横列のピン数
  word* keyMap;
private:
  const bool mirror;
  byte* rowPin;//縦列のピン番号
  byte* colPin;//横列のピン番号

  word pressNum; //キースイッチを押してる数
  word chatteringLimit;//チャタリング制限値
  word loadingNum; //現在処理しているキースイッチ
  int* currentState; //現在のキーの状態を保持する変数
  bool* beforeState; //前回のキーの状態を保持する変数
  const word state_volume;
  const word keyMap_volume;
public:
  AODB(byte layer, byte row, byte col, bool mirror_temp = 0);
  void setPin(byte* rowTemp, byte* colTemp);//ピンをセット
  void begin(void);//初期化

  void update(void);//ピンの読み取り
  void loadKeyMap(word* temp ,byte layerNum_temp = 0);//キーマップをレイヤー単位でロード

  void test(void);

  bool isLoading(void);//読み込み中か

  bool isPressed(void);//押されたか
  bool isReleased(void);//離されたか
  bool isPressing(void);//押しているか
  bool isChanged(void);//変化があったか

  int isPressedNum(void);//すべて押されているか
  bool isPressing(byte row_temp, byte col_temp);//座標のキーが押されているか

  void keyPress(void);//キーを押す
  void keyRelease(void);//キーを離す
  //using AOKEY::keyPress;
  //using AOKEY::keyRelease;

  word getKeyCode(void);//現在のキーコード
};
#endif
