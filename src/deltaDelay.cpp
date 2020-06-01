#include "Arduino.h"
#include "deltaDelay.h"
deltaDelay::deltaDelay(void){
  time = 0;
}

bool deltaDelay::is(unsigned long temp, bool repeat){
  if (time < 0xFFFFFFFF && millis() > (time + temp)) {
    if (repeat) {
      time = millis();
    }else{
      time = 0xFFFFFFFF;
    }
    return 1;
  }else{
    if (repeat && (time + temp) > 0xFFFFFFFF) {
      time = 0;
    }
    return 0;
  }
}

void deltaDelay::reset(void){
  time = millis();
}

bool deltaDelay::isLoaded(void){
  return (time == 0xFFFFFFFF) ? 1 : 0;
}

///////////////////////////////////////////////////////////////////////////////
deltaDelayMicro::deltaDelayMicro(void){
  time = 0;
}

bool deltaDelayMicro::is(unsigned long temp, bool repeat){
  if (time < 0xFFFFFFFF && micros() > (time + temp)) {
    if (repeat) {
      time = micros();
    }else{
      time = 0xFFFFFFFF;
    }
    return 1;
  }else{
    if (repeat && (time + temp) > 0xFFFFFFFF) {
      time = 0;
    }
    return 0;
  }
}

void deltaDelayMicro::reset(void){
  time = micros();
}

bool deltaDelayMicro::isLoaded(void){
  return (time == 0xFFFFFFFF) ? 1 : 0;
}
