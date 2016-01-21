#ifndef InterruptTimer_h
#define InterruptTimer_h

namespace InterruptTimer{
  enum Prescaler {PS_1 = 0,
                  PS_8 = 1,
                  PS_64 = 2,
                  PS_256 = 3,
                  PS_1024 = 4};
  enum Timer {TIMER_0 = 0,
              TIMER_1 = 1,
              TIMER_2 = 2};

  void configure(Timer timer, int count, Prescaler prescaler);
  void start();
}

#endif
