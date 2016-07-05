#ifndef ADSR_HPP
#define ADSR_HPP

#include "Timer.hpp"

enum ENVELOPE_STATE
{
  NOTE_ON,
  ATTACK,
  DECAY,
  SUSTAIN,
  RELEASE,
  NOTE_OFF,
};

class ADSR
{
  public:
    void Init(long durationInMicro, float velocity);
    float GetEnvelope();
  private:
    ENVELOPE_STATE state_;
    float velocity_;
    float currentVolume_;
    
    long attackDuration_;
    float attackScaling_;
    long decayDuration_;
    float decayScaling_;
    long sustainDuration_;
    long releaseDuration_;
    float releaseScaling_;
    
    Timer timer_;
};

#endif
