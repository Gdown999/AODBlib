#ifndef INCLUDED_MOUSECODE_h_
#define INCLUDED_MOUSECODE_h_
#include <Mouse.h>
#include "defKey.h"
void mouseCase_press(byte temp);
void mouseCase_release(byte temp);
const byte mouseCode_Num = 32;
const char mouseCode[mouseCode_Num][5] PROGMEM = {//MC
  //0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
  "LC"  ,"RC"  ,"MC"  ,"HU"  ,"HD"  ,"P"   ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,//0
  "U1"  ,"U10" ,"U100","D1"  ,"D10" ,"D100","L1"  ,"L10" ,"L100","R1"  ,"R10" ,"R100",""    ,""    ,""    ,""    ,//1
};
#define MC_____  0
#define MC_LC  0x0100
#define MC_RC  0x0101
#define MC_MC  0x0102
#define MC_HU  0x0103
#define MC_HD  0x0104
#define MC_P   0x0105

#define MC_U1    0x0110
#define MC_U10   0x0111
#define MC_U100  0x0112
#define MC_D1    0x0113
#define MC_D10   0x0114
#define MC_D100  0x0115
#define MC_L1    0x0116
#define MC_L10   0x0117
#define MC_L100  0x0118
#define MC_R1    0x0119
#define MC_R10   0x011A
#define MC_R100  0x011B

#define MC_RET  0x011C
#define MC_OUT  0x011D
#endif
