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
    //initial velocity of note (set in init only)
    float velocity_;
    float currentVolume_;
    
    //A
    long attackDuration_;
    float attackScaling_;
    //D
    long decayDuration_;
    float decayScaling_;
    //S
    long sustainDuration_;
    float sustainScaling_;
    //R
    long releaseDuration_;
    float releaseScaling_;
    
    Timer timer_;
};

#endif
