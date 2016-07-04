#include "Note.hpp"
#include <math.h>
#include <cstdlib>

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
  if(waveform_)
  {
    if(active_)
    {
      phase_ += samplingIncrement_;
      if(phase_ >= TABLE_SIZE)
      {
        phase_ -= TABLE_SIZE;
      }
      sample = waveform_[(int)phase_];
    }
    else if((int)phase_ < TABLE_SIZE && (int)phase_ != 0)
    {
      phase_ += samplingIncrement_;
      if(phase_ >= TABLE_SIZE)
      {
        phase_ = 0;
      }
      else
      {
        sample = waveform_[(int)phase_];
      }
    }
  }
  //for drum channels only
  else
  {
    if(active_)
    {
      phase_ += samplingIncrement_;
      if(phase_ >= TABLE_SIZE)
      {
        phase_ -= TABLE_SIZE;
      }
      //sample = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 0.0002f;
    }
    else if((int)phase_ < TABLE_SIZE && (int)phase_ != 0)
    {
      phase_ += samplingIncrement_;
      if(phase_ >= TABLE_SIZE)
      {
        phase_ = 0;
      }
      else
      {
        //sample = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 0.0002f;
      }
    }
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
