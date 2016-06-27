#include "Note.hpp"
#include <math.h>

#define TABLE_SIZE (1600)

Note::Note()
  : noteNum_(69), velocity_(1.0f), active_(false), phase_(0), waveform_(0)
{
  //this constructor intentionally left blank
}

void Note::Init(float *waveform)
{
  waveform_ = waveform;
}

void Note::Play(int noteNum, int velocity)
{
  velocity_ = velocity;
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
  float sample = 0;
  if(active_)
  {
    phase_ += samplingIncrement_;
    if(phase_ >= TABLE_SIZE)
    {
      phase_ -= TABLE_SIZE;
    }
    sample = waveform_[(int)phase_];
  }
  else if(waveform_[(int)phase_] <= TABLE_SIZE)
  {
    phase_ += samplingIncrement_;
    if(phase_ >= TABLE_SIZE)
    {
      phase_ -= TABLE_SIZE;
    }
    sample = waveform_[(int)phase_] / 2;
  }
  
  return sample * velocity_;
}

bool Note::IsPlaying()
{
  return active_;
}

bool Note::IsNote(int noteNum)
{
  return noteNum_ == noteNum;
}
