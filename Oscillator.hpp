#ifndef OSCILLATOR_HPP
#define OSCILLATOR_HPP

#include <stdio.h>
#include "portaudio.h"
#include "Note.hpp"

#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (500)
#define TABLE_SIZE   (1600) //remember to update this define in Note.cpp if changed

class Oscillator
{
  public:
    Oscillator();
    ~Oscillator();
    void PlayNote(int noteNum);
    void StopAll();
  
  private:
    PaStream *stream_;
    float sine_[TABLE_SIZE];
    Note notes_[32];
    
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
