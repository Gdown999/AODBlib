#ifndef INCLUDED_AOSER_h_
#define INCLUDED_AOSER_h_
#include <Arduino.h>
#include "AOKEY.h"

//ARMとESP32はソフトウェアシリアル(SS)に非対応
#if defined(__arm__) || defined(ESP32)
#define SOFTWARE_SERIAL_UNSUPPORTED
#endif

//ソフトウェアシリアルに対応しているならインクルード
#ifndef SOFTWARE_SERIAL_UNSUPPORTED
#include <SoftwareSerial.h>
#endif

//USBシリアルに対応しているか
#ifdef USBCON
#ifdef __arm__
#include <USB/USBAPI.h>
#else
#include <USBAPI.h>
#endif
#endif

class AOSER : public Stream , public AOKEY{
public:
  word indexNum;
  word arrayData;
private:
  byte serialType;
  word receiveDelay;
  byte buf;
  byte upper;

  HardwareSerial* hardSerial;
#ifndef SOFTWARE_SERIAL_UNSUPPORTED
  SoftwareSerial* softSerial;
#endif
#ifdef USBCON
  Serial_* usbSerial;
#endif

public:
  AOSER(HardwareSerial* hardSerial_temp);
#ifndef SOFTWARE_SERIAL_UNSUPPORTED
  AOSER(SoftwareSerial* softSerial_temp);
  AOSER(byte rx, byte tx);
#endif
#ifdef USBCON
  AOSER(Serial_* usbSerial_temp);
#endif

  void begin(unsigned long speed);
  void end(void);
  int peek(void);
  size_t write(uint8_t byte);
  int read(void);
  int available(void);
  void flush(void);
  bool listen(void);

  void receive(void);
  void sendPress(word temp);
  void sendRelease(word temp);
  void sendReleaseAll(void);
private:

};
#endif
