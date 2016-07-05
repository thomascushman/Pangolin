#ifndef OSCILLATOR_HPP
#define OSCILLATOR_HPP

#include "portaudio.h"
#include "Channel.hpp"

#define NUM_CHANNELS       (16)
#define SAMPLE_RATE        (44100)
#define FRAMES_PER_BUFFER  (500)
#define TABLE_SIZE         (1600) //remember to update this define in Note.cpp if changed

enum WAVEFORM
{
  SINE,
  SAW,
  SQUARE,
  NUM_WAVES
};

class Oscillator
{
  public:
    Oscillator();
    ~Oscillator();
    void PlayNote(int noteNum, int channel, int velocity, long durationInMicro);
    void StopNote(int noteNum, int channel);
    void SetVolume(int volume, int channel);
    void StopAll();
    void ChangeWaveform(WAVEFORM wave);
  
  private:
    PaStream *stream_;
    float *waveform_;
    Channel channels_[NUM_CHANNELS];
    
    //waveforms
    float sine_[TABLE_SIZE];
    float square_[TABLE_SIZE];
    float saw_[TABLE_SIZE];
    
    bool Open(PaDeviceIndex index);
    bool Close();
    bool Start();
    bool Stop();
    
    int paCallbackMethod(const void *inputBuffer, 
                     void *outputBuffer,
                     unsigned long framesPerBuffer,
                     const PaStreamCallbackTimeInfo* timeInfo,
                     PaStreamCallbackFlags statusFlags);
                     
    static int paCallback(const void *inputBuffer, 
                          void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData);
                          
    void paStreamFinishedMethod();
    static void paStreamFinished(void* userData);
};

#endif
