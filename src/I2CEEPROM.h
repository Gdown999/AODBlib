#ifndef INCLUDED_I2CEEPROM_h_
#define INCLUDED_I2CEEPROM_h_

// クラスの定義
class I2CEEPROM {
public:
  // コンストラクタ
  I2CEEPROM(byte eepAdrTmp);

  // 読み込み
  byte read(unsigned int readDataAdress);

  // 書き込み
  bool write(unsigned int writeDataAdress, byte writeData);

protected:
  byte eepromAdress;
  byte readData;
};
#endif
