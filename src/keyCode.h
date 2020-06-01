#ifndef INCLUDED_KEYCODE_h_
#define INCLUDED_KEYCODE_h_
#include "defKey.h"
const char keyCode[105][5] PROGMEM = {//KC
  //0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
  "SPC" ,"EXLM","DQUO","HASH","DLR" ,"PERC","AMPR","QUOT","LPRN","RPRN","ASTR","PLUS","COMM","MINS","DOT" ,"SLSH",//2
  "0"   ,"1"   ,"2"   ,"3"   ,"4"   ,"5"   ,"6"   ,"7"   ,"8"   ,"9"   ,"COLN","SCLN","LABK","EQL" ,"RABK","QUES",//3
  "AT",                                                                                                           //4
                                                                               "LBRC","BSLS","RBRC","CIRC","ANBR",//5
  "GRV" ,"A"   ,"B"   ,"C"   ,"D"   ,"E"   ,"F"   ,"G"   ,"H"   ,"I"   ,"J"   ,"K"   ,"L"   ,"M"   ,"N"   ,"O"   ,//6
  "P"   ,"Q"   ,"R"   ,"S"   ,"T"   ,"U"   ,"V"   ,"W"   ,"X"   ,"Y"   ,"Z"   ,"LCBR","PIPE","RCBR",""    ,"DEL" ,//7
  "LCTL","LSFT","LALT","LGUI","RCTL","RSFT","RALT","RGUI",                                                        //8
  "ENT" ,"CAPS","F1"  ,"F2"  ,"F3"  ,"F4"  ,"F5"  ,"F6"  ,"F7"  ,"F8"  ,"F9"  ,"F10" ,"F11" ,"F12" ,"ESC" ,"BSPC",//C
  "TAB" ,"INS" ,"HOME","PGUP","DEL" ,"END" ,"PGDN","RGHT","LEFT","DOWN","UP"                                      //D
};
const byte layerCode_Num = 32;
const char layerCode[layerCode_Num][4] PROGMEM = {//LAY
  //0     1      2      3      4      5      6      7      8      9     A      B      C      D      E      F
  "0"    ,"1"   ,"2"   ,"3"   ,"4"   ,"5"   ,"6"   ,"7"   ,"8"   ,"9"  ,"10"  ,"11"  ,"12"  ,"13"  ,"14"  ,"15",//0
  "S0"   ,"S1"  ,"S2"  ,"S3"  ,"S4"  ,"S5"  ,"S6"  ,"S7"  ,"S8"  ,"S9" ,"S10" ,"S11" ,"S12" ,"S13" ,"S14" ,"S15"//1
};
byte interpolationProcess(byte temp);
#endif
