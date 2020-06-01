#include <Arduino.h>
#include <AOFS.h>
unsigned long AOFS::read_next_file_address(unsigned long adr){
  return (I2CEEPROM::read( adr ) << 16 | I2CEEPROM::read( adr + 1) << 8 | I2CEEPROM::read( adr + 2));
}
unsigned long AOFS::read_upper_folder_address(unsigned long adr){
  return (I2CEEPROM::read( adr + 3) << 16 | I2CEEPROM::read( adr + 4) << 8 | I2CEEPROM::read( adr + 5));
}
unsigned long AOFS::read_file_data_length(unsigned long adr){
  return (I2CEEPROM::read( adr + 6) << 8 | I2CEEPROM::read( adr + 7));
}
unsigned long AOFS::read_file_name_length(unsigned long adr){
  return (I2CEEPROM::read( adr + 8));
}

unsigned long AOFS::read_file_end_address(unsigned long adr){
  return  (adr + 9 + read_file_data_length(adr) + read_file_name_length(adr));
}

void AOFS::write_root_file_address(unsigned long temp){
  I2CEEPROM::write(0, temp >> 16 & 0xFF);
  I2CEEPROM::write(1, temp >> 8 & 0xFF);
  I2CEEPROM::write(2, temp & 0xFF);
}
void AOFS::write_most_back_file_address(unsigned long temp){
  I2CEEPROM::write(3, temp >> 16 & 0xFF);
  I2CEEPROM::write(4, temp >> 8 & 0xFF);
  I2CEEPROM::write(5, temp & 0xFF);
}

void AOFS::write_next_file_address(unsigned long adr,unsigned long temp){
  I2CEEPROM::write(adr, temp >> 16 & 0xFF);
  I2CEEPROM::write(adr + 1, temp >> 8 & 0xFF);
  I2CEEPROM::write(adr + 2, temp & 0xFF);
}
void AOFS::write_upper_folder_address(unsigned long adr,unsigned long temp){
  I2CEEPROM::write(adr + 3, temp >> 16 & 0xFF);
  I2CEEPROM::write(adr + 4, temp >> 8 & 0xFF);
  I2CEEPROM::write(adr + 5, temp & 0xFF);
}
void AOFS::write_file_data_length(unsigned long adr,word temp){
  I2CEEPROM::write(adr + 6, temp >> 8 & 0xFF);
  I2CEEPROM::write(adr + 7, temp & 0xFF);
}
void AOFS::write_file_name_length(unsigned long adr,byte temp){
  I2CEEPROM::write(adr + 8, temp & 0xFF);
}
