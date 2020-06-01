#include "Arduino.h"
#include "AOSHELL.h"

AOSHELL::AOSHELL(void){
  isRunScript = 0;//scriptを実行してよいか
  isClipSign = 0;//符号切り取りを実行してよいか
  signYetExists = 0;//符号がまだあるか
  signLength = 0;//符号文字の長さ

  escapeValue = 1;//ループを脱出するか
  onlyOnce = 1;//一回だけ実行
}

void AOSHELL::userArrow(void){
  Serial.write("\x1b[38;2;33;160;219m");
  Serial.print(F("AOshell>"));
  Serial.write("\x1b[39m");
}

void AOSHELL::update(void){
  if((buf = Serial.read()) != -1){

    if (String(buf) == String("\n")){//enter
      Serial.print(buf);
      serialStr.trim();
      serialStr += serialStrUpper;
      serialStrUpper.remove(0);
      if (serialStr.length()) {
        isRunScript = 1;//スクリプトの実行を許可
        isClipSign = 1;//符号切り取りの実行を許可
      }

    }else if (buf == 0x1b) {
      AOSHELL::escProcess();

    }else{
      if (String(buf) == String("\b")) {
        serialStr.remove(serialStr.length() - 1);
      }else{
        serialStr += buf;
      }
      Serial.write("\x1b[2K\r");
      AOSHELL::userArrow();
      Serial.print(serialStr);
      Serial.print(serialStrUpper);
      for (size_t i = 0; i < serialStrUpper.length(); i++)Serial.write("\x1b[D");

    }
  }
}

void AOSHELL::escProcess(void){
  while((buf = Serial.read()) == -1);
  if(buf == 0x5B){//"["
    while((buf = Serial.read()) == -1);

    if (buf == 0x44) {//left
      serialStrUpper = serialStr.substring(serialStr.length() - 1) + serialStrUpper;
      serialStr.remove(serialStr.length() - 1);
      Serial.write("\x1b[D");

    }else if (buf == 0x43) {//right
      serialStr += serialStrUpper.substring(0,1);
      serialStrUpper.remove(0,1);
      Serial.write("\x1b[C");

    }else if (buf == 0x41) {
      /* code */
    }else if (buf == 0x42) {
      /* code */
    }
  }
}

void AOSHELL::end(void){
  if (isRunScript || signYetExists) {//どの符号とも合致しなかった場合
    Serial.write("\x1b[38;2;198;112;37m");
    Serial.print(F("Error:"));
    Serial.write("\x1b[39m");
    Serial.println(signStr);
    signStr.remove(0);
    serialStr.remove(0);
    serialStrUpper.remove(0);
    signYetExists = 0;
    isRunScript = 0;
  }
}

void AOSHELL::signClip(void){
  signLength = serialStr.indexOf(" ");//符号文字列の長さを調べる

  if(signLength != -1){//符号終末に空白が見つかった場合
    signStr = serialStr.substring(0,signLength);//符号文字をコピー
    serialStr.remove(0,signLength + 1);//元の文字列から符号文字を削除
    serialStr.trim();//もしまだ空白があればすべて取り除く
    signYetExists = 1;

  }else{//最後の符号だった場合実行
    signLength = serialStr.length();//符号文字列の長さを調べる
    signStr = serialStr.substring(0,signLength);//符号文字をコピー
    serialStr.remove(0);//最後の符号なのですべて削除
    signYetExists = 0;
  }
}

bool AOSHELL::script(const char* temp){
  if (isRunScript) {
    if(isClipSign){
      AOSHELL::signClip();
      isClipSign = 0;
    }
    if (signStr == String(temp)) {
      //Serial.print(signStr);Serial.print(F(":"));Serial.println(serialStr);

      if (signYetExists) {//符号がまだあるなら
        isClipSign = 1;//符号の切り取りを許可
      }else{//符号がもうないなら
        isRunScript = 0;//スクリプトの実行を停止
      }
      signStr.remove(0);//符号を使ったので削除
      return 1;

    }
  }
  return 0;
}

bool AOSHELL::script(const __FlashStringHelper* temp){
  if (isRunScript) {
    if(isClipSign){
      AOSHELL::signClip();
      isClipSign = 0;
    }
    if (signStr == String(temp)) {
      //Serial.print(signStr);Serial.print(F(":"));Serial.println(serialStr);

      if (signYetExists) {//符号がまだあるなら
        isClipSign = 1;//符号の切り取りを許可
      }else{//符号がもうないなら
        isRunScript = 0;//スクリプトの実行を停止
      }
      signStr.remove(0);//符号を使ったので削除
      return 1;

    }
  }
  return 0;
}

int AOSHELL::getInt(bool isClip_temp = 0){
  if(!isClip_temp)AOSHELL::signClip();
  if(!signYetExists)isRunScript = 0;
  return signStr.toInt();
}

float AOSHELL::getFloat(bool isClip_temp = 0){
  if(!isClip_temp)AOSHELL::signClip();
  if(!signYetExists)isRunScript = 0;
  return signStr.toFloat();
}

const char* AOSHELL::getChar(bool isClip_temp = 0){
  if(!isClip_temp)AOSHELL::signClip();
  if(!signYetExists)isRunScript = 0;
  return signStr.c_str();
}
