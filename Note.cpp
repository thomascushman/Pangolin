#include "Note.hpp"
#include <math.h>
#include <stdio.h>
#define TABLE_SIZE (1600)

Note::Note()
  : noteNum_(69), active_(false), phase_(0), sine_(0)
{
  //this constructor intentionally left blank
}

void Note::init(float *sine)
{
  sine_ = sine;
}

void Note::play(int noteNum)
{
  noteNum_ = noteNum;
  samplingIncrement_ = powf(2, (noteNum_ - 21) / 12.0f);
  active_ = true;
}

void Note::stop()
{
  active_ = false;
}

float Note::getSample()
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
