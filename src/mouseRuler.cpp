#include <Arduino.h>
#include <Mouse.h>
#include "mouseRuler.h"
mouseRuler::mouseRuler(void){
  mouseXCount = 0;
  mouseYCount = 0;
}

void mouseRuler::reset(void){
  mouseXCount = 0;
  mouseYCount = 0;
}

int mouseRuler::getXCount(void){
  return mouseXCount;
}
int mouseRuler::getYCount(void){
  return mouseYCount;
}

void mouseRuler::move(int xtemp, int ytemp){
  if (xtemp > 0) {
    for (word i = 0; i < (abs(xtemp) / 10); i++) {
      Mouse.move(10,0,0);
      mouseXCount +=10;
    }
    for (word i = 0; i < (abs(xtemp) % 10); i++) {
      Mouse.move(1,0,0);
      mouseXCount++;
    }
  }else if (xtemp < 0) {
    for (word i = 0; i < (abs(xtemp) / 10); i++) {
      Mouse.move(-10,0,0);
      mouseXCount -=10;
    }
    for (word i = 0; i < (abs(xtemp) % 10); i++) {
      Mouse.move(-1,0,0);
      mouseXCount--;
    }
  }

  if (ytemp > 0) {
    for (word i = 0; i < (abs(ytemp) / 10); i++) {
      Mouse.move(0,10,0);
      mouseYCount +=10;
    }
    for (word i = 0; i < (abs(ytemp) % 10); i++) {
      Mouse.move(0,1,0);
      mouseYCount++;
    }
  }else if (ytemp < 0) {
    for (word i = 0; i < (abs(ytemp) / 10); i++) {
      Mouse.move(0,-10,0);
      mouseYCount -=10;
    }
    for (word i = 0; i < (abs(ytemp) % 10); i++) {
      Mouse.move(0,-1,0);
      mouseYCount--;
    }
  }
}
