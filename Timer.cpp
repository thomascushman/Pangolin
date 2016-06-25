#include "Timer.hpp"
#include <math.h>
#include <stdio.h>
#include <iostream>

using namespace std::chrono;

void Timer::Start(long duration)
{
  active_ = true;
  currentTime_ = startTime_ = high_resolution_clock::now();
  durationInMicro_ = duration;
}

bool Timer::Update()
{
  if(active_)
  {
    //update clock
    currentTime_ = high_resolution_clock::now();
    if(duration_cast<microseconds>(currentTime_ - startTime_).count() >= durationInMicro_)
    {
      active_ = false;
    }
  }
  return active_;
}

void Timer::debug()
{
  printf("%ld\n", duration_cast<microseconds>(currentTime_ - startTime_).count());
}

bool Timer::IsActive()
{
  return active_;
}
