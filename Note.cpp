#include "Note.hpp"
#include <math.h>

#define TABLE_SIZE (1600)

Note::Note()
  : noteNum_(69), active_(false), phase_(0), sine_(0)
{
  //this constructor intentionally left blank
}

void Note::Init(float *sine)
{
  sine_ = sine;
}

void Note::Play(int noteNum)
{
  noteNum_ = noteNum;
  samplingIncrement_ = powf(2, (noteNum_ - 21) / 12.0f);
  active_ = true;
}

void Note::Stop()
{
  active_ = false;
}

float Note::GetSample()
{
  if(active_)
  {
    phase_ += samplingIncrement_;
    if(phase_ >= TABLE_SIZE)
    {
      phase_ -= TABLE_SIZE;
    }
    return sine_[(int)phase_];
  }
  else return 0;
}

bool Note::IsPlaying()
{
  return active_;
}
