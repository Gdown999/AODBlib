#ifndef INCLUDED_DELTADELAY_h_
#define INCLUDED_DELTADELAY_h_
class deltaDelay{
private:
  unsigned long time;
public:
  deltaDelay(void);
  bool is(unsigned long temp, bool repeat);
  void reset(void);
  bool isLoaded(void);
};

class deltaDelayMicro{
private:
  unsigned long time;
public:
  deltaDelayMicro(void);
  bool is(unsigned long temp, bool repeat);
  void reset(void);
  bool isLoaded(void);
};

#endif
