#ifndef INCLUDED_AOFS_H_
#define INCLUDED_AOFS_H_
#include <Arduino.h>
#include <I2CEEPROM.h>

#define __FIRST_ADDRESS__ 12

class AOFS : public I2CEEPROM {
private:
  String findStr;
  String romReadStr;
  unsigned long eepromCapacity;

  unsigned long rootFileAddress;
  unsigned long mostBackFileAddress;

  word fileDataLength;
  byte fileNameLength;
  unsigned long upperFolderAddress;

  unsigned long nextFileAddress;
  unsigned long currentFileAddress;
  unsigned long prevFileAddress;

  word folderNum;
  unsigned long rootFolderAddress;
  unsigned long mostBackFolderAddress;
  unsigned long nextFolderAddress;
  unsigned long currentFolderAddress;
  unsigned long prevFolderAddress;

public:
  AOFS(byte eepromAddress_temp ,unsigned long eepromCapacity_temp);
  void format(void);

  byte write(char* fileName_temp, byte data_temp, word i_temp = 0, bool isdDataLength = 0);
  void write(char* fileName_temp, String& data_temp);
  int read(char* fileName_temp, word i_temp = 0);
  char* read(char* fileName_temp, char c_temp, word i_temp = 0);
  using I2CEEPROM::read;
  using I2CEEPROM::write;

  bool find(char* temp);
  void list(void);

  byte mkFile(char* temp);
  bool rmFile(char* temp);

  void mkFolder(char* temp);
  void rmFolder(char* temp);

  void removeGap(void);
private:
  void loadRootData(void);
  void updateNextFileAddress(void);
  void updateNextFolderAddress(void);

  unsigned long read_next_file_address(unsigned long adr);
  unsigned long read_upper_folder_address(unsigned long adr);
  unsigned long read_file_data_length(unsigned long adr);
  unsigned long read_file_name_length(unsigned long adr);

  unsigned long read_file_end_address(unsigned long adr);

  void write_root_file_address(unsigned long temp);
  void write_most_back_file_address(unsigned long temp);

  void write_next_file_address(unsigned long adr,unsigned long temp);
  void write_upper_folder_address(unsigned long adr,unsigned long temp);
  void write_file_data_length(unsigned long adr,word temp);
  void write_file_name_length(unsigned long adr,byte temp);
};
#endif
