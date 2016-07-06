#include "ADSR.hpp"
#include "Debug.hpp"

void ADSR::Init(long durationInMicro, float velocity)
{
  state_ = NOTE_ON;
  currentVolume_ = velocity_ = velocity;
  
  attackDuration_ = 1000; //short, static attack duration
  attackScaling_ = 1.00001f;
  decayDuration_ = durationInMicro / 16 * 3; //variable decay duration (relatively small)
  decayScaling_ = 0.995f;
  sustainDuration_ = durationInMicro - attackDuration_ - decayDuration_ - releaseDuration_; //everything besides ADR is left for sustain
  sustainScaling_ = 1.0f;
  releaseDuration_ = durationInMicro / 4; //1/4th of note is release time
  releaseScaling_ = 0.99f;
}

float ADSR::GetEnvelope()
{
  switch(state_)
  {
    case NOTE_ON:
    {
      //initial volume at velocity (volume will change in other cases)
      currentVolume_ = velocity_;
      //start attack
      state_ = ATTACK;
      timer_.Start(attackDuration_);
      //fall through into attack
    }
    case ATTACK:
    {
      //if timer still going
      if(timer_.Update())
      {
        //increase volume
        currentVolume_ *= attackScaling_;
        if(currentVolume_ > velocity_ * 2.0f)
        {
          currentVolume_ = velocity_ * 2.0f;
        }
      }
      else
      {
        //start our decay
        state_ = DECAY;
        timer_.Start(decayDuration_);
      }
      break;
    }
    case DECAY:
    {
      //if timer still going
      if(timer_.Update())
      {
        //decrease volume
        currentVolume_ *= decayScaling_;
        if(currentVolume_ < velocity_ * 0.5f)
        {
          currentVolume_ = velocity_ * 0.5f;
        }
      }
      else
      {
        //start sustain
        state_ = SUSTAIN;
        timer_.Start(sustainDuration_);
      }
      break;
    }
    case SUSTAIN:
    {
      //if timer still going
      if(timer_.Update())
      {
        //do nothing (sustainScaling_ set to 1.0f as of the time of this comment)
        currentVolume_ *= sustainScaling_;
      }
      else
      {
        //start release
        state_ = RELEASE;
        timer_.Start(releaseDuration_);
      }
      break;
    }
    case RELEASE:
    {
      //if timer still going
      if(timer_.Update())
      {
        //decrease volume
        currentVolume_ *= releaseScaling_;
        break;
      }
      else
      {
        //NOTE OFF
        state_ = NOTE_OFF;
      }
      //fall through into note off
    }
    case NOTE_OFF:
    {
      currentVolume_ = 0.0f;
    }
  }
  return currentVolume_;
}
