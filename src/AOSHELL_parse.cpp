#include "Arduino.h"
#include "AOSHELL.h"
bool AOSHELL::isContinue(void){
  if (onlyOnce) {
    signStr.remove(0);
    serialStr.remove(0);
    onlyOnce = 0;
  }
  if (escapeValue) {//whileループを続けるか
    while((buf = Serial.read()) == -1);
    serialStr += buf;
    isRunScript = 1;
    return 1;
  }else{
    signStr.remove(0);
    serialStr.remove(0);
    escapeValue = 1;
    onlyOnce = 1;
    return 0;
  }
}

bool AOSHELL::search(const char temp, bool isDelete = 1){
  if (isRunScript) {
    if (buf == temp) {
      if(isDelete)serialStr.remove(serialStr.length() - 1);
      isRunScript = 0;
      return 1;
    }
  }
  return 0;
}

bool AOSHELL::escape(const char temp, bool isDelete = 1){
  if (isRunScript) {
    if (buf == temp) {
      if(isDelete)serialStr.remove(serialStr.length() - 1);
      isRunScript = 0;
      escapeValue = 0;
      return 1;
    }
  }
  return 0;
}

String AOSHELL::getSerStr(void){
  return serialStr;
}

String* AOSHELL::pgetSerStr(void){
  return &serialStr;
}
