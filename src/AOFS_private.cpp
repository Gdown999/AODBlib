#include <Arduino.h>
#include <AOFS.h>
void AOFS::loadRootData(void){
  //ファイル
  //|rootFileAddress,3byte|mostBackFileAddress,3byte
  rootFileAddress = I2CEEPROM::read(0) << 16 | I2CEEPROM::read(1) << 8 | I2CEEPROM::read(2);
  mostBackFileAddress = I2CEEPROM::read(3) << 16 | I2CEEPROM::read(4) << 8 | I2CEEPROM::read(5);
  prevFileAddress = __FIRST_ADDRESS__;
  currentFileAddress = __FIRST_ADDRESS__;
  nextFileAddress = rootFileAddress;
  //フォルダー
  //|rootFolderAddress,3byte|mostBackFolderAddress,3byte
  rootFolderAddress = I2CEEPROM::read(6) << 16 | I2CEEPROM::read(7) << 8 | I2CEEPROM::read(8);
  mostBackFolderAddress = I2CEEPROM::read(9) << 16 | I2CEEPROM::read(10) << 8 | I2CEEPROM::read(11);
}

//|nextFileAddress,3byte|upperFolderAddress,3byte|fileDataLength,2byte
//|fileNameLength,1byte|fileName,Nbyte|FileData,Nbyte>>>
void AOFS::updateNextFileAddress(void){
  prevFileAddress = currentFileAddress;
  currentFileAddress = nextFileAddress;
  nextFileAddress = read_next_file_address(currentFileAddress);
}

void AOFS::updateNextFolderAddress(void){
  prevFolderAddress = currentFolderAddress;
  currentFolderAddress = nextFolderAddress;
  nextFolderAddress = I2CEEPROM::read(currentFileAddress) << 16 | I2CEEPROM::read(currentFileAddress + 1) << 8 | I2CEEPROM::read(currentFileAddress + 2);
}

void AOFS::removeGap(void){
  AOFS::loadRootData();
  unsigned long unusedAreaAddress;
  unsigned long copyLoopCount;
  if (rootFileAddress > __FIRST_ADDRESS__) {
    unusedAreaAddress = __FIRST_ADDRESS__;
    copyLoopCount = 8;
    copyLoopCount += read_file_data_length(rootFileAddress);
    copyLoopCount += read_file_name_length(rootFileAddress);

    for (word i = 0; i < copyLoopCount; i++) {
      I2CEEPROM::write(unusedAreaAddress + i,I2CEEPROM::read(rootFileAddress + i));
    }
    rootFileAddress = __FIRST_ADDRESS__;
    nextFileAddress = __FIRST_ADDRESS__;
    write_root_file_address(__FIRST_ADDRESS__);
  }

  while (nextFileAddress && nextFileAddress < 0xFFFFFF) {
    AOFS::updateNextFileAddress();//チェーンaddressを更新
    unusedAreaAddress = read_file_end_address(prevFileAddress);

    if (unusedAreaAddress < currentFileAddress) {
      copyLoopCount = read_file_end_address(currentFileAddress);
      copyLoopCount -= currentFileAddress;

      for (word i = 0; i < copyLoopCount; i++) {
        I2CEEPROM::write(unusedAreaAddress + i,I2CEEPROM::read(currentFileAddress + i));
      }
      write_next_file_address(prevFileAddress, unusedAreaAddress);
    }
  }
  mostBackFileAddress = unusedAreaAddress;
  write_most_back_file_address(unusedAreaAddress);
}
