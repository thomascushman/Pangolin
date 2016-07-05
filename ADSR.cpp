#include "ADSR.hpp"
#include "Debug.hpp"

void ADSR::Init(long durationInMicro, float velocity)
{
  state_ = NOTE_ON;
  velocity_ = velocity;
  attackDuration_ = durationInMicro / 16 * 1;
  printf("%ld", attackDuration_);
  attackScaling_ = 1.2f;
  decayDuration_ = durationInMicro / 16 * 1;
  decayScaling_ = 0.995f;
  sustainDuration_ = durationInMicro / 16 * 10;
  releaseDuration_ = durationInMicro / 16 * 4;
  releaseScaling_ = 1.0f;
}

float ADSR::GetEnvelope()
{
  switch(state_)
  {
    case NOTE_ON:
    {
      currentVolume_ = velocity_;
      state_ = ATTACK;
      timer_.Start(attackDuration_);
    }
    case ATTACK:
    {
      if(timer_.Update())
      {
        currentVolume_ *= attackScaling_;
        if(currentVolume_ > velocity_ * 2.0f)
        {
          currentVolume_ = velocity_ * 2.0f;
        }
      }
      else
      {
        state_ = DECAY;
        timer_.Start(decayDuration_);
      }
      break;
    }
    case DECAY:
    {
      if(timer_.Update())
      {
        currentVolume_ *= decayScaling_;
        if(currentVolume_ < velocity_ * 0.9f)
        {
          currentVolume_ = velocity_ * 0.9f;
        }
      }
      else
      {
        state_ = SUSTAIN;
        timer_.Start(sustainDuration_);
      }
      break;
    }
    case SUSTAIN:
    {
      if(!timer_.Update())
      {
        state_ = RELEASE;
        timer_.Start(releaseDuration_);
      }
      break;
    }
    case RELEASE:
    {
      if(timer_.Update())
      {
        currentVolume_ *= releaseScaling_;
      }
      else
      {
        state_ = NOTE_OFF;
      }
      break;
    }
    case NOTE_OFF:
    {
      //currentVolume_ = 0.0f;
    }
  }
  return currentVolume_;
}
