#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <stdio.h>
#include "portaudio.h"

#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (500)
#define TABLE_SIZE   (2005)

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
    int phase_;
    float sine[32][TABLE_SIZE];
    
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
