#include "Note.hpp"
#include <math.h>
#include <cstdlib>

#define TABLE_SIZE (1600)

Note::Note()
  : active_(false), 
    noteNum_(69), phase_(0), samplingIncrement_(0), waveform_(0), 
    velocity_(1.0f), state_(ATTACK), envelopeVolume_(velocity_)
{
  //this constructor intentionally left blank
}

void Note::Init(float *waveform)
{
  waveform_ = waveform;
}

void Note::Play(int noteNum, int velocity)
{
  active_ = true;
  state_ = NOTE_ON;
  velocity_ = velocity;
  noteNum_ = noteNum;
  samplingIncrement_ = powf(2, (noteNum_ - 21) / 12.0f);
}

void Note::Stop()
{
  state_ = RELEASE;
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
        GetEnvelope();
        phase_ -= TABLE_SIZE;
      }
      sample = waveform_[(int)phase_];
    }
  }
  
  return sample * envelopeVolume_;
}

bool Note::IsPlaying()
{
  return active_;
}

bool Note::IsNote(int noteNum)
{
  return noteNum_ == noteNum;
}

float Note::GetEnvelope()
{
  switch(state_)
  {
    case NOTE_ON:
    {
      active_ = true;
      envelopeVolume_ = velocity_ * 0.8f;
      state_ = ATTACK;
    }
    case ATTACK:
    {
      if(envelopeVolume_ > velocity_ * 1.5)
      {
        state_ = DECAY;
      }
      else
      {
        envelopeVolume_ *= 1.075;
      }
      break;
    }
    case DECAY:
    {
      if(envelopeVolume_ < velocity_ * 0.9)
      {
        state_ = SUSTAIN;
      }
      else
      {
        envelopeVolume_ *= 0.995;
      }
      break;
    }
    case SUSTAIN:
    {
      break;
    }
    case RELEASE:
    {
      if(envelopeVolume_ < velocity_ * 0.1)
      {
        state_ = NOTE_OFF;
      }
      else
      {
        envelopeVolume_ *= 0.7;
      }
      break;
    }
    case NOTE_OFF:
    {
      envelopeVolume_ = 0.01f;
      active_ = false;
    }
  }
  return envelopeVolume_;
}
