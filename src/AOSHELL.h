#ifndef INCLUDED_AOSHELL_h_
#define INCLUDED_AOSHELL_h_
class AOSHELL{
private:
  String serialStr;//シリアル受信文字
  String serialStrUpper;//シリアル受信文字(上位)
  String signStr;//符号文字

  char buf;
  int signLength;//signStrの長さ
  bool isRunScript;//scriptを実行してよいか
  bool isClipSign;//符号切り取りを実行してよいか
  bool signYetExists;//符号がまだあるか

  bool escapeValue;//ループを脱出するか
  bool onlyOnce;//一回だけ実行
public:
  AOSHELL(void);
  void update(void);
  void end(void);

  bool script(const char* temp);
  bool script(const __FlashStringHelper* temp);

  int getInt(bool isClip_temp = 0);
  float getFloat(bool isClip_temp = 0);
  const char* getChar(bool isClip_temp = 0);

  bool isContinue(void);
  bool search(const char temp, bool isDelete = 1);
  bool escape(const char temp, bool isDelete = 1);

  String getSerStr(void);
  String* pgetSerStr(void);

private:
  void userArrow(void);
  void escProcess(void);
  void signClip(void);
};
#endif
