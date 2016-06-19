#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <stdio.h>
#include "portaudio.h"
#include "Note.hpp"

#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (500)
#define TABLE_SIZE   (1600) //remember to update this define in Note.cpp if changed

class AudioManager
{
  public:
    AudioManager();
    bool open(PaDeviceIndex index);
    bool close();
    bool start();
    bool stop();
  
  private:
    PaStream *stream_;
    float sine[TABLE_SIZE];
    Note notes[32];
    
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
