#ifndef INCLUDED_AOROM_h_
#define INCLUDED_AOROM_h_
class AOROM {
private:
  const byte eepromAdress;
  const word dataBlockLength;
  word dataAddress_write;
  word dataAddress_read;
public:
  // コンストラクタ
  AOROM(byte eepAdrTmp,word dataBlockLength_temp);
  //アドレスブロックセット
  void setAddress(word dataBlockAddress, word dataAdress_temp = 0);
  //配列書き込み
  bool arrayWrite(byte* array, word length);
  bool arrayWrite(word* array, word length);
  //配列読み取り
  bool arrayRead(byte* array, word length);
  bool arrayRead(word* array, word length);
  //値書き込み
  void Write8bit(byte temp);
  void Write16bit(word temp);
  //値読み取り
  byte Read8bit(void);
  int Read16bit(void);
protected:
  // 読み込み
  byte read(word dataAdress);
  // 書き込み
  bool write(word dataAdress, byte data);
};
#endif
