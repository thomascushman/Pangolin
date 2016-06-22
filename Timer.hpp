#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

class Timer
{
  public:
    Timer();
    bool IsItThatTime(double time);
    void Start();
    bool IsActive();
    
  private:
    clock_t startTime_;
    clock_t currentTime_;
    bool active_;
};

#endif
