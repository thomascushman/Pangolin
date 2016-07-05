#include "Channel.hpp"
#include "Debug.hpp"

Channel::Channel()
  : volume_(1.0f), active_(false)
{
  //this constructor intentionally left blank
}

void Channel::SetWaveform(float *waveform)
{
  waveform_ = waveform;
  for(int i = 0; i < NUM_SLOTS; ++i)
  {
    slots_[i].Init(waveform_);
  }
}

void Channel::SetVolume(int volume)
{
  volume_ = (volume / 64.0f);
}

void Channel::PlayNote(int noteNum, int velocity, long durationInMicro)
{
  if(noteNum < 21 || noteNum > 108)
  {
    return;
  }
  
  active_ = true;
  
  for(int i = 0; i < NUM_SLOTS; ++i)
  {
    if(!slots_[i].IsPlaying())
    {
      slots_[i].Play(noteNum, velocity, durationInMicro);
      break;
    }
    else if(slots_[i].IsNote(noteNum))
    {
      return;
    }
    //for recording incident of errors. (shouldn't ever be triggered)
    if(i == NUM_SLOTS - 1)
    {
      printf("OUT OF SLOTS\n");
    }
  }
}

void Channel::StopNote(int noteNum)
{
  for(int i = 0; i < NUM_SLOTS; ++i)
  {
    if(slots_[i].IsPlaying() && slots_[i].IsNote(noteNum))
    {
      slots_[i].Stop();
      break;
    }
  }
}

float Channel::GetSample()
{
  if(!active_)
    return 0;
  
  float sample = 0;
  for(int i = 0; i < NUM_SLOTS; ++i)
  {
    sample += slots_[i].GetSample() * volume_;
  }
  return sample;
}
