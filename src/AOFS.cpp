#include <Arduino.h>
#include <AOFS.h>

AOFS::AOFS(byte eepromAddress_temp ,unsigned long eepromCapacity_temp):
I2CEEPROM(eepromAddress_temp){
  eepromCapacity = eepromCapacity_temp;
}

void AOFS::format(void){//rootDataのみ削除
  Serial.println(F("|------------------|"));
  unsigned long printCount_temp = eepromCapacity * 0.05;
  for (unsigned long i = 0; i < eepromCapacity; i++) {
    if (i < __FIRST_ADDRESS__) {
      if (i == 2) {
        I2CEEPROM::write(i,__FIRST_ADDRESS__);
      }else{
        I2CEEPROM::write(i,0x00);
      }
    }else{
      I2CEEPROM::write(i,0xFF);
    }
    if (!(--printCount_temp)) {
      Serial.print(F("#"));
      printCount_temp = eepromCapacity * 0.05;
    }
  }
  Serial.write("\x1b[2K\r");
  Serial.println(F("format complete"));
}

bool AOFS::find(char* temp){
//|nextFileAddress,3byte|upperFolderAddress,3byte|fileDataLength,2byte
//|1byte(isCluster,1bit<<7|fileNameLength,7bit)|fileName,Nbyte|FileData,Nbyte|nextCluster,3byte
  romReadStr.remove(0);
  findStr = String(temp);
  AOFS::loadRootData();
  while (nextFileAddress && nextFileAddress < 0xFFFFFF) {
    AOFS::updateNextFileAddress();//チェーンaddressを更新
    fileNameLength = read_file_name_length(currentFileAddress);//ファイル名の長さを取得
    if (fileNameLength == findStr.length()) {//ファイル名の長さを比較
      for (byte i = 0; i < fileNameLength; i++) {//ファイル名を取得
        romReadStr += char(I2CEEPROM::read(currentFileAddress + 9 + i));
      }
      if (romReadStr == findStr) {//ファイル名が一致した場合
        findStr.remove(0);
        romReadStr.remove(0);
        return 1;
      }else{
        romReadStr.remove(0);
      }
    }
  }
  findStr.remove(0);
  return 0;
}

byte AOFS::mkFile(char* temp){
  unsigned long newFileAddress;
  if (!AOFS::find(temp)) {//同じファイルが見つからなかった場合
    findStr = String(temp);
    AOFS::loadRootData();
    if (!mostBackFileAddress) {
      newFileAddress = __FIRST_ADDRESS__;
    }else{
      newFileAddress = read_file_end_address(mostBackFileAddress);
      if ((newFileAddress + 8 + findStr.length()) >= eepromCapacity) {//最後尾に空き領域がない場合
        AOFS::removeGap();
        newFileAddress = read_file_end_address(mostBackFileAddress);
      }
      if ((newFileAddress + 8 + findStr.length()) >= eepromCapacity) {//defrag後に空き領域がない場合
        findStr.remove(0);
        return 0;
      }
    }
    write_next_file_address(mostBackFileAddress, newFileAddress);
    write_next_file_address(newFileAddress, 0);
    write_upper_folder_address(newFileAddress, 0);
    write_file_data_length(newFileAddress,0);
    write_file_name_length(newFileAddress, findStr.length());
    for (byte i = 0; i < findStr.length(); i++) {
      I2CEEPROM::write(newFileAddress + 9 + i, findStr.c_str()[i]);
    }
    write_most_back_file_address(newFileAddress);
    findStr.remove(0);
    return 1;
  }else{//同じファイルが見つかった場合
    return 2;
  }
}

bool AOFS::rmFile(char* temp){
  if (AOFS::find(temp)) {
    if (currentFileAddress == rootFileAddress && currentFileAddress == mostBackFileAddress) {
      write_root_file_address(0x0C);
      write_most_back_file_address(0x0C);
    }else if (currentFileAddress == rootFileAddress) {
      write_root_file_address(nextFileAddress);
    }else if (currentFileAddress == mostBackFileAddress){
      write_next_file_address(prevFileAddress, 0);
      write_most_back_file_address(prevFileAddress);
    }else{
      write_next_file_address(prevFileAddress, nextFileAddress);
    }
    return 1;
  }
  return 0;
}

void AOFS::list(void){
  AOFS::loadRootData();
  while (nextFileAddress && nextFileAddress < 0xFFFFFF) {
    AOFS::updateNextFileAddress();//チェーンaddressを更新
    fileNameLength = read_file_name_length(currentFileAddress);//ファイル名の長さを取得
    if (!(upperFolderAddress = read_upper_folder_address(currentFileAddress))) {
      Serial.print(F("root-"));
    }
    for (byte i = 0; i < fileNameLength; i++) {//ファイル名を取得
      Serial.print(char(I2CEEPROM::read(currentFileAddress + 9 + i)));
    }
    Serial.println(F(" "));
  }
}

byte AOFS::write(char* fileName_temp, byte data_temp, word i_temp = 0, bool isdDataLength = 0){
  unsigned long copyFileAddress;
  if (AOFS::find(fileName_temp)) {
    AOFS::loadRootData();
    if (currentFileAddress < mostBackFileAddress) {
      unsigned long copyLoopCount = 8;
      copyLoopCount += read_file_data_length(currentFileAddress);
      copyLoopCount += read_file_name_length(currentFileAddress);
      copyFileAddress = read_file_end_address(mostBackFileAddress);
      write_next_file_address(mostBackFileAddress, copyFileAddress);
      for (unsigned long i = 3; i < copyLoopCount; i++) {
        I2CEEPROM::write(copyFileAddress + i, I2CEEPROM::read(currentFileAddress + i));
      }
      AOFS::rmFile(fileName_temp);
      write_next_file_address(copyFileAddress, 0);
      write_most_back_file_address(copyFileAddress);
    }
    AOFS::loadRootData();
    if ((mostBackFileAddress + 1) >= eepromCapacity) {//最後尾に空き領域がない場合
      AOFS::removeGap();
    }
    AOFS::loadRootData();
    Serial.println(F(" "));
    Serial.println(mostBackFileAddress);
    Serial.println(eepromCapacity);
    if ((mostBackFileAddress + 1) >= eepromCapacity) {
      return 2;//容量不足
    }
    AOFS::loadRootData();
    I2CEEPROM::write(mostBackFileAddress + 9 + read_file_name_length(mostBackFileAddress) + i_temp, data_temp);
    if (isdDataLength) {
      write_file_data_length(mostBackFileAddress,max(read_file_data_length(mostBackFileAddress),i_temp));
    }
    return 1;//書き込み成功
  }
  return 0;//ファイル見つからず
}

void AOFS::write(char* fileName_temp, String& data_temp){
  for (word i = 0; i < data_temp.length(); i++) {
    switch (AOFS::write(fileName_temp,data_temp.charAt(i),i)) {
      case 0:Serial.print(F("no file"));goto bailout;
      case 1:Serial.print(data_temp.charAt(i));
      case 2:Serial.print(F("no capacity"));goto bailout;
    }
  }
  Serial.println(F(" "));
  Serial.println(F("completed"));
  bailout:
  AOFS::find(fileName_temp);
  write_file_data_length(currentFileAddress,max(read_file_data_length(currentFileAddress),data_temp.length()));
}

int AOFS::read(char* fileName_temp, word i_temp = 0){
  if(AOFS::find(fileName_temp)){
    return I2CEEPROM::read(currentFileAddress + 9 + read_file_name_length(currentFileAddress) + i_temp);
  }else{
    return -1;
  }
}

char* AOFS::read(char* fileName_temp, char c_temp, word i_temp = 0){
  if(AOFS::find(fileName_temp)){
    char buf = 0;
    byte endCharCount = 0;
    unsigned long endAddress = read_file_end_address(currentFileAddress);
    currentFileAddress += read_file_name_length(currentFileAddress);
    currentFileAddress += 9;
    while(1) {
      if (currentFileAddress < endAddress) {
        if (endCharCount == i_temp) {
          romReadStr.remove(0);
          while(1){
            if (buf == c_temp || currentFileAddress == endAddress) {
              return romReadStr.c_str();
            }else{
              buf = char(I2CEEPROM::read(currentFileAddress++));
              romReadStr += buf;
            }
          }
        }
        buf = char(I2CEEPROM::read(currentFileAddress));
        if (buf == c_temp) {
          ++endCharCount;
        }
        ++currentFileAddress;
      }else{
        break;
      }
    }
  }
}
