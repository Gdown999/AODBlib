#ifndef INCLUDED_MOUSERULER_h_
#define INCLUDED_MOUSERULER_h_
class mouseRuler{
private:
  int mouseXCount;
  int mouseYCount;
public:
  mouseRuler(void);
  void move(int xtemp, int ytemp);
  void reset(void);
  int getXCount(void);
  int getYCount(void);
};
#endif
