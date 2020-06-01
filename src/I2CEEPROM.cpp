#include <Arduino.h>
#include <Wire.h>
#include "I2CEEPROM.h"

// コンストラクタ
I2CEEPROM::I2CEEPROM(byte eepAdrTmp){
  eepromAdress = eepAdrTmp;
  Wire.begin();
}

byte I2CEEPROM::read(unsigned int readDataAdress){
  Wire.beginTransmission(eepromAdress);               // i2cアドレス指定
  Wire.write((int)(readDataAdress >> 8));                // EEPROM内アドレス指定 MSB
  Wire.write((int)(readDataAdress & 0xFF));              // LSB
  Wire.endTransmission();
  Wire.requestFrom(eepromAdress, 1);                  // 1バイトデータリクエスト
  while (Wire.available()) {                    //
    readData = Wire.read();                         // データ受信
  }
  return readData;
}

bool I2CEEPROM::write(unsigned int writeDataAdress, byte writeData){
  I2CEEPROM::read(writeDataAdress);

  if(writeData != readData){
    for (size_t i = 0; i < 10; i++) {
      Wire.beginTransmission(eepromAdress);               // i2cアドレス指定
      Wire.write((int)(writeDataAdress >> 8));                // EEPROM内アドレス指定 MSB
      Wire.write((int)(writeDataAdress & 0xFF));              // LSB
      Wire.write(writeData);
      Wire.endTransmission();
      delay(5);
      I2CEEPROM::read(writeDataAdress);
      if (writeData == readData)return 1;
    }
    return 0;
  }else{
    return 0;
  }
}
