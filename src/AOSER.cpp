#include <Arduino.h>
#include "AOSER.h"

#define __HEAD_SERIAL__ 1
#define __SOFT_SERIAL__ 2
#define __USB_SERIAL__  3

#define __KEY_PRESS__ 0
#define __KEY_RELEASE__ 1
#define __KEY_RELEASE_ALL__ 2
#define __SWITCH_KEY_MAP__ 3
#define __WRITE_KEY_MAP__ 4

//↓コンストラクタ
AOSER::AOSER(HardwareSerial* hardSerial_temp){
  hardSerial = hardSerial_temp;
  serialType = __HEAD_SERIAL__;
  indexNum = 0;
  arrayData = 0;
  receiveDelay = 0;
}

#ifndef SOFTWARE_SERIAL_UNSUPPORTED
AOSER::AOSER(SoftwareSerial* softSerial_temp){
  softSerial = softSerial_temp;
  serialType = __SOFT_SERIAL__;
  indexNum = 0;
  arrayData = 0;
  receiveDelay = 0;
}

AOSER::AOSER(byte rx, byte tx){
  softSerial = new SoftwareSerial(rx, tx);
  serialType = __SOFT_SERIAL__;
  indexNum = 0;
  arrayData = 0;
  receiveDelay = 0;
}
#endif

#ifdef USBCON
AOSER::AOSER(Serial_* usbSerial_temp){
  usbSerial = usbSerial_temp;
  serialType = __USB_SERIAL__;
  indexNum = 0;
  arrayData = 0;
  receiveDelay = 0;
}
#endif


void AOSER::begin(unsigned long speed) {
  switch (serialType) {
#ifndef SOFTWARE_SERIAL_UNSUPPORTED
  case __SOFT_SERIAL__:softSerial->begin(speed);break;
#endif
#ifdef USBCON
  case __USB_SERIAL__:usbSerial->begin(speed);break;
#endif
  default:hardSerial->begin(speed);
  }
  receiveDelay = 1000000 / speed * 12;
}

void AOSER::end(void) {
  switch (serialType) {
#ifndef SOFTWARE_SERIAL_UNSUPPORTED
  case __SOFT_SERIAL__:softSerial->end();break;
#endif
#ifdef USBCON
  case __USB_SERIAL__:usbSerial->end();break;
#endif
  default:hardSerial->end();
  }
}

int AOSER::peek(void) {
  switch (serialType) {
#ifndef SOFTWARE_SERIAL_UNSUPPORTED
  case __SOFT_SERIAL__:return softSerial->peek();
#endif
#ifdef USBCON
  case __USB_SERIAL__:return usbSerial->peek();
#endif
  default:return hardSerial->peek();
  }
}

size_t AOSER::write(uint8_t byte) {
  switch (serialType) {
#ifndef SOFTWARE_SERIAL_UNSUPPORTED
  case __SOFT_SERIAL__:return softSerial->write(byte);
#endif
#ifdef USBCON
  case __USB_SERIAL__:return usbSerial->write(byte);
#endif
  default:return hardSerial->write(byte);
  }
}

int AOSER::read(void) {
  switch (serialType) {
#ifndef SOFTWARE_SERIAL_UNSUPPORTED
  case __SOFT_SERIAL__:return softSerial->read();
#endif
#ifdef USBCON
  case __USB_SERIAL__:return usbSerial->read();
#endif
  default:return hardSerial->read();
  }
}

int AOSER::available(void) {
  switch (serialType) {
#ifndef SOFTWARE_SERIAL_UNSUPPORTED
  case __SOFT_SERIAL__:return softSerial->available();
#endif
#ifdef USBCON
  case __USB_SERIAL__:return usbSerial->available();
#endif
  default:return hardSerial->available();
  }
}

void AOSER::flush(void) {
  switch (serialType) {
#ifndef SOFTWARE_SERIAL_UNSUPPORTED
  case __SOFT_SERIAL__:softSerial->flush();break;
#endif
#ifdef USBCON
  case __USB_SERIAL__:usbSerial->flush();break;
#endif
  default:hardSerial->flush();
  }
}

#ifndef SOFTWARE_SERIAL_UNSUPPORTED
bool AOSER::listen(void){
  if(serialType == __SOFT_SERIAL__){
    softSerial->listen();
    return 1;
  }else{
    return 0;
  }
}
#endif
//Serial.println(F("::2-1"));
//Serial.println(F("::3-1"));
//Serial.println(F("::4-1"));
void AOSER::receive(void){
  if((buf = AOSER::read()) != -1){
    switch (buf) {
      case __KEY_PRESS__://keypress
      delayMicroseconds(receiveDelay);
      while((buf = AOSER::read()) == -1);upper = buf;
      delayMicroseconds(receiveDelay);
      while((buf = AOSER::read()) == -1);AOKEY::keyPress(upper << 8 | buf);
      //Serial.print(F("PRESS:"));Serial.print(upper,HEX);Serial.println(buf,HEX);
      break;

      case __KEY_RELEASE__://keyRelease
      delayMicroseconds(receiveDelay);
      while((buf = AOSER::read()) == -1);upper = buf;
      delayMicroseconds(receiveDelay);
      while((buf = AOSER::read()) == -1);AOKEY::keyRelease(upper << 8 | buf);
      //Serial.print(F("RELEASE:"));Serial.print(upper,HEX);Serial.println(buf,HEX);
      break;

      case __KEY_RELEASE_ALL__://keyMap切り替え
      Keyboard.releaseAll();
      break;

      case __SWITCH_KEY_MAP__://keyMap切り替え
      delayMicroseconds(receiveDelay);
      while((buf = AOSER::read()) == -1);
      break;

      case __WRITE_KEY_MAP__://keyMap書き込み
      byte arrayNum;
      //配列番号を受信
      delayMicroseconds(receiveDelay);
      while((buf = AOSER::read()) == -1);arrayNum = buf;
      //配列要素番号を受信
      delayMicroseconds(receiveDelay);
      while((buf = AOSER::read()) == -1);indexNum = buf << 8;
      delayMicroseconds(receiveDelay);
      while((buf = AOSER::read()) == -1);indexNum = indexNum | buf;
      //2byteデータを受信
      delayMicroseconds(receiveDelay);
      while((buf = AOSER::read()) == -1);arrayData = buf << 8;
      delayMicroseconds(receiveDelay);
      while((buf = AOSER::read()) == -1);arrayData = arrayData | buf;
    }
  }
}

void AOSER::sendPress(word temp){
  //Serial.println(F("SEND_PRESS"));
  AOSER::write(__KEY_PRESS__);AOSER::flush();
  AOSER::write(temp >> 8);AOSER::flush();
  AOSER::write(temp & 0xFF);AOSER::flush();
}

void AOSER::sendRelease(word temp){
  //Serial.println(F("SEND_RELEASE"));
  AOSER::write(__KEY_RELEASE__);AOSER::flush();
  AOSER::write(temp >> 8);AOSER::flush();
  AOSER::write(temp & 0xFF);AOSER::flush();
}

void AOSER::sendReleaseAll(void){
  AOSER::write(__KEY_RELEASE_ALL__);AOSER::flush();
}
