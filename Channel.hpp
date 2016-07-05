#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Note.hpp"
#define NUM_SLOTS 16

class Channel
{
  public:
    Channel();
    void SetWaveform(float *waveform);
    void SetVolume(int volume);
    void PlayNote(int noteNum, int velocity, long durationInMicro);
    void StopNote(int noteNum);
    float GetSample();
  
  private:
    Note slots_[NUM_SLOTS];
    float *waveform_;
    float volume_;
    bool active_;
};

#endif
