#include "Timer.hpp"
#include <math.h>
#include <stdio.h>

#define EPSILON 0.0001

Timer::Timer()
  : startTime_(std::clock()), currentTime_(startTime_), active_(false)
{
  
}

bool Timer::IsItThatTime(double time)
{
  if(active_)
  {
    currentTime_ = std::clock();
    if(fabs(time - ( (currentTime_ - startTime_) / (double) CLOCKS_PER_SEC)) <= EPSILON)
    {
      printf("HERE\n");
      return true;
    }
  }
  return false;
}

void Timer::Start()
{
  active_ = true;
}

bool Timer::IsActive()
{
  return active_;
}
