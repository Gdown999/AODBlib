#include <Arduino.h>
#include <Wire.h>
#include "AOROM.h"

// コンストラクタ
AOROM::AOROM(byte eepAdrTmp,word dataBlockLength_temp):
eepromAdress(eepAdrTmp),dataBlockLength(dataBlockLength_temp){
  dataAddress_write = 0;
  dataAddress_read = 0;
}

byte AOROM::read(word dataAdress){
  byte data;
  Wire.beginTransmission(eepromAdress);               // i2cアドレス指定
  Wire.write((int)(dataAdress >> 8));                // EEPROM内アドレス指定 MSB
  Wire.write((int)(dataAdress & 0xFF));              // LSB
  Wire.endTransmission();
  Wire.requestFrom(eepromAdress, 1);                  // 1バイトデータリクエスト
  while (Wire.available()) {                    //
    data = Wire.read();                         // データ受信
  }
  return data;
}

bool AOROM::write(word dataAdress, byte dataWrite){
  byte dataRead;
  Wire.beginTransmission(eepromAdress);               // i2cアドレス指定
  Wire.write((int)(dataAdress >> 8));                // EEPROM内アドレス指定 MSB
  Wire.write((int)(dataAdress & 0xFF));              // LSB
  Wire.endTransmission();
  Wire.requestFrom(eepromAdress, 1);                  // 1バイトデータリクエスト
  while (Wire.available()) {                    //
    dataRead = Wire.read();                         // データ受信
  }

  if(dataWrite != dataRead){
    Wire.beginTransmission(eepromAdress);               // i2cアドレス指定
    Wire.write((int)(dataAdress >> 8));                // EEPROM内アドレス指定 MSB
    Wire.write((int)(dataAdress & 0xFF));              // LSB
    Wire.write(dataWrite);
    Wire.endTransmission();
    delay(5);
    return 1;
  }else{
    return 0;
  }
}
void AOROM::setAddress(word dataBlockAddress, word dataAdress_temp = 0){
  dataAddress_write = dataBlockAddress * dataBlockLength + dataAdress_temp;
  dataAddress_read = dataBlockAddress * dataBlockLength + dataAdress_temp;
}

bool AOROM::arrayWrite(byte* array, word length){
  if (dataAddress_write < dataBlockLength) {
    for (word i = 0; i < length; i++) {
      AOROM::write(dataAddress_write, array[i]);
      ++dataAddress_write;
    }
    return 1;
  }else{
    return 0;
  }
}

bool AOROM::arrayWrite(word* array, word length){
  if (dataAddress_write < dataBlockLength) {
    for (word i = 0; i < length; i++) {
      AOROM::write(dataAddress_write, (array[i] >> 8));
      ++dataAddress_write;
      AOROM::write(dataAddress_write, (array[i] & 0xFF));
      ++dataAddress_write;
    }
    return 1;
  }else{
    return 0;
  }
}

bool AOROM::arrayRead(byte *array, word length){
  if (dataAddress_read < dataBlockLength) {
    for (word i = 0; i < length; i++) {
      array[i] = AOROM::read(dataAddress_read);
      ++dataAddress_read;
    }
    return 1;
  }else{
    return 0;
  }
}

bool AOROM::arrayRead(word *array, word length){
  if (dataAddress_read < dataBlockLength) {
    for (word i = 0; i < length; i++) {
      array[i] = AOROM::read(dataAddress_read) << 8 | AOROM::read(dataAddress_read + 1);
      dataAddress_read += 2;
    }
    return 1;
  }else{
    return 0;
  }
}


void AOROM::Write8bit(byte temp){
  if (dataAddress_write < dataBlockLength) {
    AOROM::write(dataAddress_write, temp);
    ++dataAddress_write;
  }
}

void AOROM::Write16bit(word temp){
  if (dataAddress_write < dataBlockLength) {
    AOROM::write(dataAddress_write, (temp >> 8));
    ++dataAddress_write;
    AOROM::write(dataAddress_write, (temp & 0xFF));
    ++dataAddress_write;
  }
}

byte AOROM::Read8bit(void){
  if (dataAddress_read < dataBlockLength) {
    byte temp = AOROM::read(dataAddress_read);
    ++dataAddress_read;
    return temp;
  }
}

int AOROM::Read16bit(void){
  if (dataAddress_read < dataBlockLength) {
    int temp = AOROM::read(dataAddress_read) << 8 | AOROM::read(dataAddress_read + 1);
    dataAddress_read += 2;
    return temp;
  }
}
