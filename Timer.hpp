#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer
{
  public:
    void Start(long durationInMicro);
    bool Update();
    bool IsActive();
    void debug();
    
  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime_ = std::chrono::high_resolution_clock::now();
    std::chrono::time_point<std::chrono::high_resolution_clock> currentTime_ = std::chrono::high_resolution_clock::now();
    long durationInMicro_ = 0;
    bool active_ = false;
};

#endif
